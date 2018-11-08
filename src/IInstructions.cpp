#include "IInstructions.hpp"
#include "Instructions.hpp"
#include "ExceptionHandling.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

void ADDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = (int16_t)constant;
    int32_t result = left + right;
    
    bool overflow = sameSign(left, right) && !sameSign(left, result);
    if (overflow) { throw BadArithmeticOperation("ADDI encountered an overflow"); }
    
    reg.write(rt, result);
}

void ADDIUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left + constant;
    reg.write(rt, result);
}

void ANDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left & constant;
    reg.write(rt, result);
}

void ORIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left | constant;
    reg.write(rt, result);
}

void XORIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    uint32_t result = left ^ constant;
    reg.write(rt, result);
}

void SLTIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = (int16_t)constant;
    reg.write(rt, left < right ? 1 : 0);
}

void SLTIUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    reg.write(rt, left < constant ? 1 : 0);
}

void LUIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t value = constant << 16;
    reg.write(rt, value);
}

void LWInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    data = mem.read<uint32_t>(addr);
}

void LWInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rt, data);
}

void LBInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    data = mem.read<byte>(addr);
}

void LBInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rt, (int32_t)(char)data);
}

void LBUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    data = mem.read<byte>(addr);
}

void LBUInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rt, data);
}

void LHInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    data = mem.read<uint16_t>(addr);
}

void LHInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rt, (int32_t)(int16_t)data);
}

void LHUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    data = mem.read<uint16_t>(addr);
}

void LHUInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.write(rt, data);
}

void SWInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    uint32_t data = reg.read(rt);
    mem.write<uint32_t>(addr, data);
}

void SBInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    byte data = (byte)reg.read(rt);
    mem.write<byte>(addr, data);
}

void SHInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t addr = reg.read(rs) + constant;
    uint16_t data = (uint16_t)reg.read(rt);
    mem.write<uint16_t>(addr, data);
}

bool BEQInstr::evaluateCondition(const RegisterMap& reg) const
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    return left == right;
}

bool BGEZInstr::evaluateCondition(const RegisterMap& reg) const
{
    int32_t left = reg.read(rs);
    return left >= 0;
}

bool BGEZALInstr::requiresLink() const { return true; }

bool BGTZInstr::evaluateCondition(const RegisterMap& reg) const
{
    int32_t left = reg.read(rs);
    return left > 0;
}

bool BLEZInstr::evaluateCondition(const RegisterMap& reg) const
{
    int32_t left = reg.read(rs);
    return left <= 0;
}

bool BLTZInstr::evaluateCondition(const RegisterMap& reg) const
{
    int32_t left = reg.read(rs);
    return left < 0;
}

bool BLTZALInstr::requiresLink() const { return true; }

bool BNEInstr::evaluateCondition(const RegisterMap& reg) const
{
    uint32_t left = reg.read(rs);
    uint32_t right = reg.read(rt);
    return left != right;
}
