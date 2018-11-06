#include "RegisterMap.hpp"
#include "ExceptionHandling.hpp"
#include <stdint.h>

using namespace Clarkitechture::MIPS;

RegisterMap::RegisterMap()
{
    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        registers[i] = 0;
    }
}

const uint32_t RegisterMap::read(size_t regIndex) const
{
    if (regIndex == 0) { return 0; }
    else if (regIndex >= REGISTER_COUNT) { throw BadRegisterRead(regIndex); }
    else { return registers[regIndex]; }
}

void RegisterMap::write(size_t regIndex, uint32_t regValue)
{
    if (regIndex >= REGISTER_COUNT) { throw "Add exception handling plz"; }
    else if (regIndex > 0) { registers[regIndex] = regValue; }
}
