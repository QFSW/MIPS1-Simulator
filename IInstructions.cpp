#include "IInstructions.hpp"
#include "Instructions.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

void ADDIInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    int32_t left = reg.read(rs);
    int32_t right = constant;
    int32_t result = left + right;
    
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
    int32_t right = constant;
    reg.write(rt, left < right ? 1 : 0);
}

void SLTIUInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    uint32_t left = reg.read(rs);
    reg.write(rt, left < constant ? 1 : 0);
}
