#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>
#include "Instructions.hpp"
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
	else { return decodeIInstruction(bin); }
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
    case 0b101001: return new SLTUInstr(rs, rt, rd, shamt);
    case 0b000000: return new SLLInstr(rs, rt, rd, shamt);
    case 0b000100: return new SLLVInstr(rs, rt, rd, shamt);
    case 0b000011: return new SRAInstr(rs, rt, rd, shamt);
    case 0b000111: return new SRAVInstr(rs, rt, rd, shamt);
    default:
        throw BadInstructionDecode(bin, "invalid or unsupported function code - " + toHexStr(funct));
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
	case 0b100100: return new ANDIInstr(rs, rt, constant);
    case 0b001101: return new ORIInstr(rs, rt, constant);
    case 0b001110: return new XORIInstr(rs, rt, constant);
    case 0b001010: return new SLTIInstr(rs, rt, constant);
    case 0b001011: return new SLTIUInstr(rs, rt, constant);
    default:
		throw BadInstructionDecode(bin, "invalid or unsupported opcode - " + toHexStr(opcode));
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

void ADDInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int left = reg.read(rs);
    int right = reg.read(rt);
    int result = left + right;
    
    bool overflow = sameSign(left, right) && !sameSign(left, result);
    if (overflow) { throw "overflow exception"; }
    
    reg.write(rd, result);
}

void ADDUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
	uint32_t left = reg.read(rs);
	uint32_t right = reg.read(rt);
	uint32_t result = left + right;
	reg.write(rd, result);
}

void ADDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
	int left = reg.read(rs);
    int right = constant;
	int result = left + right;
    
    bool overflow = sameSign(left, right) && !sameSign(left, result);
    if (overflow) { throw "overflow exception"; }
    
	reg.write(rt, result);
}

void ADDIUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left + constant;
    reg.write(rt, result);
}

void SUBInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
	int left = reg.read(rs);
	int right = reg.read(rt);
	int result = left - right;
    
    bool overflow = sameSign(left, -right) && !sameSign(left, result);
    if (overflow) { throw "overflow exception"; }
    
	reg.write(rd, result);
}

void SUBUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left - right;
    reg.write(rd, result);
}

void ANDInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left & right;
    reg.write(rd, result);
}

void ANDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left & constant;
    reg.write(rt, result);
}

void ORInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left | right;
    reg.write(rd, result);
}

void ORIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left | constant;
    reg.write(rt, result);
}

void XORInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left ^ right;
    reg.write(rd, result);
}

void XORIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left ^ constant;
    reg.write(rt, result);
}

void JRInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    jumpAddr = reg.read(rs);
}

void JRInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.PC = jumpAddr;
}

void JALRInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    jumpAddr = reg.read(rs);
    reg.write(reg.PC + 8, 31);
}

void JALRInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.PC = jumpAddr;
}

void MULTInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int64_t left = reg.read(rs);
    int64_t right = reg.read(rt);
    int64_t result = left * right;
    reg.lo = 0xFFFFFFFF & result;
    reg.hi = 0xFFFFFFFF & (result >> 32);
}

void MULTUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint64_t left = reg.read(rs);
    uint64_t right = reg.read(rt);
    uint64_t result = left * right;
    reg.lo = 0xFFFFFFFF & result;
    reg.hi = 0xFFFFFFFF & (result >> 32);
}

void DIVInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = reg.read(rt);
    
    if (right == 0) { throw "Division by 0"; }
    
    int32_t quotient = left / right;
    int32_t remainder = left % right;
    reg.lo = quotient;
    reg.hi = remainder;
}

void DIVUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    
    if (right == 0) { throw "Division by 0"; }
    
    uint32_t quotient = left / right;
    uint32_t remainder = left % right;
    reg.lo = quotient;
    reg.hi = remainder;
}

void MFHIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rd, reg.hi);
}

void MFLOInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rd, reg.lo);
}

void MTHIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    reg.hi = reg.read(rs);
}

void MTLOInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    reg.lo = reg.read(rs);
}

void SLTInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = reg.read(rt);
    reg.write(rd, left < right ? 1 : 0);
}

void SLTIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = constant;
    reg.write(rt, left < right ? 1 : 0);
}

void SLTIUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    reg.write(rt, left < constant ? 1 : 0);
}

void SLTUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    reg.write(rd, left < right ? 1 : 0);
}

void SLLInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t value = reg.read(rt);
    value = value << shamt;
    reg.write(rd, value);
}

void SLLVInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t value = reg.read(rt);
    uint32_t newShamt = reg.read(rs);
    value = value << newShamt;
    reg.write(rd, value);
}

void SRLInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t value = reg.read(rt);
    value = value >> shamt;
    reg.write(rd, value);
}

void SRLVInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t value = reg.read(rt);
    uint32_t newShamt = reg.read(rs);
    value = value >> newShamt;
    reg.write(rd, value);
}

void SRAInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t value = reg.read(rt);
    value = value >> shamt;
    reg.write(rd, value);
}

void SRAVInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t value = reg.read(rt);
    uint32_t newShamt = reg.read(rs);
    value = value >> newShamt;
    reg.write(rd, value);
}

