#include "MemoryMap.hpp"
#include "ExceptionHandling.hpp"
#include <stdint.h>

using namespace Clarkitechture::MIPS;

MemoryMap::MemoryMap()
{
}

MemoryMap::~MemoryMap()
{
    if (instrMemorySize > 0) { delete[] instrMemory; }
}

MemoryMap::MemoryMap(const MemoryMap &a)
{
    memory = a.memory;
    
    instrMemorySize = a.instrMemorySize;
    if (instrMemorySize > 0)
    {
        instrMemory = new byte[instrMemorySize];
        memcpy(instrMemory, a.instrMemory, a.instrMemorySize);
    }
}

void MemoryMap::initInstrMemory(byte* instrMem, size_t size)
{
    instrMemorySize = size;
    instrMemory = instrMem;
}
