#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>
#include "Instructions.hpp"
#include "MemoryMap.hpp"
#include "RegisterMap.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

Instruction* BinaryDecoder::decodeInstruction(uint32_t bin)
{
	byte opcode = 0b111111 & (bin >> (32 - 6));
	if (opcode == 0) { return decodeRInstruction(bin); }
	else { throw "rip"; }
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
    default:
		throw "rip";
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
    default:
		throw "rip";
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

