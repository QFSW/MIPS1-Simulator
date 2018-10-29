#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>
#include "Instructions.hpp"
#include "MemoryMap.hpp"
#include "RegisterMap.hpp"

using namespace Clarkitechture::MIPS;

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
	case 0b100010: return new SUBInstr(rs, rt, rd, shamt);
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
	default:
		throw "rip";
	}
}

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
	uint32_t left = reg.read(rs);
	uint32_t right = reg.read(rt);
	uint32_t result = left + right;
	reg.write(rd, result);
}

void ADDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
	uint32_t left = reg.read(rs);
	uint32_t result = left + constant;
	reg.write(rt, result);
}

void SUBInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
	uint32_t left = reg.read(rs);
	uint32_t right = reg.read(rt);
	uint32_t result = left - right;
	reg.write(rd, result);
}