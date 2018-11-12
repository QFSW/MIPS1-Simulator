#include "JInstructions.hpp"
#include "Instructions.hpp"
#include "Utils.hpp"

using namespace Clarkitechture::MIPS;

void JInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    u_int32_t PCAddr = 0xF0000000 & reg.PC;
    addr = 0x0FFFFFFF & (target << 2);
    addr |= PCAddr;
}

void JInstr::delayedExecute(MemoryMap &mem, RegisterMap& reg)
{
    reg.PC = addr;
}

void JALInstr::execute(MemoryMap &mem, RegisterMap& reg)
{
    JInstr::execute(mem, reg);
    reg.write(31, reg.PC + 4);
}
