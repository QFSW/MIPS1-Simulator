#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>
#include "Instructions.hpp"
#include "RInstructions.hpp"
#include "IInstructions.hpp"
#include "JInstructions.hpp"
#include "MemoryMap.hpp"
#include "RegisterMap.hpp"
#include "ExceptionHandling.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

Instruction* BinaryDecoder::decodeInstruction(uint32_t bin)
{
	byte opcode = 0b111111 & (bin >> (32 - 6));
	if (opcode == 0) { return decodeRInstruction(bin); }
    else if (opcode == 0b10 || opcode == 0b11) { return decodeJInstruction(bin); }
	else { return decodeIInstruction(bin); }
}

JInstruction* BinaryDecoder::decodeJInstruction(uint32_t bin)
{
    byte opcode = 0b111111 & (bin >> (32 - 6));
    uint32_t target = 0x03FFFFFF & bin;
    
    switch (opcode)
    {
    default:
        case 0b000010: return new JInstr(target);
        case 0b000011: return new JALInstr(target);
        throw BadInstructionDecode(bin, "invalid or unsupported function code - " + toBinStr(opcode));
    }
}

RInstruction* BinaryDecoder::decodeRInstruction(uint32_t bin)
{
	byte rs = 0b11111 & (bin >> (32 - (6 + 5)));
	byte rt = 0b11111 & (bin >> (32 - (6 + 5 + 5)));
	byte rd = 0b11111 & (bin >> (32 - (6 + 5 + 5 + 5)));
	byte shamt = 0b11111 & (bin >> (32 - (6 + 5 + 5 + 5 + 5)));
	byte funct = 0b111111 & bin;

	switch (funct)
	{
    case 0b100000: return new ADDInstr(rs, rt, rd, shamt);
    case 0b100001: return new ADDUInstr(rs, rt, rd, shamt);
    case 0b100010: return new SUBInstr(rs, rt, rd, shamt);
    case 0b100011: return new SUBUInstr(rs, rt, rd, shamt);
    case 0b100100: return new ANDInstr(rs, rt, rd, shamt);
    case 0b100101: return new ORInstr(rs, rt, rd, shamt);
    case 0b100111: return new NORInstr(rs, rt, rd, shamt);
    case 0b100110: return new XORInstr(rs, rt, rd, shamt);
    case 0b001000: return new JRInstr(rs, rt, rd, shamt);
    case 0b001001: return new JALRInstr(rs, rt, rd, shamt);
    case 0b011000: return new MULTInstr(rs, rt, rd, shamt);
    case 0b011001: return new MULTUInstr(rs, rt, rd, shamt);
    case 0b011010: return new DIVInstr(rs, rt, rd, shamt);
    case 0b011011: return new DIVUInstr(rs, rt, rd, shamt);
    case 0b010000: return new MFHIInstr(rs, rt, rd, shamt);
    case 0b010010: return new MFLOInstr(rs, rt, rd, shamt);
    case 0b010001: return new MTHIInstr(rs, rt, rd, shamt);
    case 0b010011: return new MTLOInstr(rs, rt, rd, shamt);
    case 0b101010: return new SLTInstr(rs, rt, rd, shamt);
    case 0b101011: return new SLTUInstr(rs, rt, rd, shamt);
    case 0b000000: return new SLLInstr(rs, rt, rd, shamt);
    case 0b000100: return new SLLVInstr(rs, rt, rd, shamt);
    case 0b000011: return new SRAInstr(rs, rt, rd, shamt);
    case 0b000111: return new SRAVInstr(rs, rt, rd, shamt);
    case 0b000010: return new SRLInstr(rs, rt, rd, shamt);
    case 0b000110: return new SRLVInstr(rs, rt, rd, shamt);
    default:
        throw BadInstructionDecode(bin, "invalid or unsupported function code - " + toBinStr(funct));
	}
}

IInstruction* BinaryDecoder::decodeIInstruction(uint32_t bin)
{
	byte opcode = 0b111111 & (bin >> (32 - 6));
	byte rs = 0b11111 & (bin >> (32 - (6 + 5)));
	byte rt = 0b11111 & (bin >> (32 - (6 + 5 + 5)));
	uint16_t constant = 0xFFFF & bin;

	switch (opcode)
	{
	case 0b001000: return new ADDIInstr(rs, rt, constant);
    case 0b001001: return new ADDIUInstr(rs, rt, constant);
	case 0b001100: return new ANDIInstr(rs, rt, constant);
    case 0b001101: return new ORIInstr(rs, rt, constant);
    case 0b001110: return new XORIInstr(rs, rt, constant);
    case 0b001010: return new SLTIInstr(rs, rt, constant);
    case 0b001011: return new SLTIUInstr(rs, rt, constant);
    case 0b001111: return new LUIInstr(rs, rt, constant);
    case 0b100011: return new LWInstr(rs, rt, constant);
    case 0b100000: return new LBInstr(rs, rt, constant);
    case 0b100100: return new LBUInstr(rs, rt, constant);
    case 0b100001: return new LHInstr(rs, rt, constant);
    case 0b100101: return new LHUInstr(rs, rt, constant);
    case 0b101011: return new SWInstr(rs, rt, constant);
    case 0b101000: return new SBInstr(rs, rt, constant);
    case 0b101001: return new SHInstr(rs, rt, constant);
    case 0b000100: return new BEQInstr(rs, rt, constant);
    case 0b000111: return new BGTZInstr(rs, rt, constant);
    case 0b000110: return new BLEZInstr(rs, rt, constant);
    case 0b000101: return new BNEInstr(rs, rt, constant);
    case 0b100010: return new LWLInstr(rs, rt, constant);
    case 0b000001: return decodeBranchInstruction(bin);
    default:
		throw BadInstructionDecode(bin, "invalid or unsupported opcode - " + toBinStr(opcode));
	}
}

BranchIInstruction* BinaryDecoder::decodeBranchInstruction(uint32_t bin)
{
    byte rs = 0b11111 & (bin >> (32 - (6 + 5)));
    byte cond = 0b11111 & (bin >> (32 - (6 + 5 + 5)));
    uint16_t constant = 0xFFFF & bin;
    
    switch (cond)
    {
        case 0b00001: return new BGEZInstr(rs, cond, constant);
        case 0b10001: return new BGEZALInstr(rs, cond, constant);
        case 0b00000: return new BLTZInstr(rs, cond, constant);
        case 0b10000: return new BLTZALInstr(rs, cond, constant);
        default:
            throw BadInstructionDecode(bin, "invalid or unsupported branch condition - " + toBinStr(cond));
    }
}

void Instruction::delayedExecute(MemoryMap &mem, RegisterMap &reg) { }

RInstruction::RInstruction(byte rs, byte rt, byte rd, byte shamt)
{
	this->rs = rs;
	this->rt = rt;
	this->rd = rd;
	this->shamt = shamt;
}

IInstruction::IInstruction(byte rs, byte rt, uint16_t constant)
{
	this->rs = rs;
	this->rt = rt;
	this->constant = constant;
}

JInstruction::JInstruction(uint32_t target)
{
	this->target = target;
}

void JumpRInstruction::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.PC = jumpAddr;
}

void BranchIInstruction::execute(MemoryMap &mem, RegisterMap &reg)
{
    int32_t offset = ((int16_t)constant) << 2;
    branchAddr = reg.PC + offset;
    conditionMet = evaluateCondition(reg);
    if (requiresLink()) { reg.write(31, reg.PC + 4); }
}

void BranchIInstruction::delayedExecute(MemoryMap &mem, RegisterMap &reg)
{
    if (conditionMet)
    {
        reg.PC = branchAddr;
    }
}

bool BranchIInstruction::requiresLink() const { return false; }
