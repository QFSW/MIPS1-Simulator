#include "RInstructions.hpp"
#include "Instructions.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

void ADDInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = reg.read(rt);
    int32_t result = left + right;
    
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

void SUBInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = reg.read(rt);
    int32_t result = left - right;
    
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

void ORInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left | right;
    reg.write(rd, result);
}

void XORInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    uint32_t result = left ^ right;
    reg.write(rd, result);
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

void JRInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    jumpAddr = reg.read(rs);
}

void JALRInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    jumpAddr = reg.read(rs);
    reg.write(reg.PC + 8, 31);
}
