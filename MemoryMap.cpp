#include "MemoryMap.hpp"
#include "ExceptionHandling.hpp"
#include <stdint.h>

using namespace Clarkitechture::MIPS;

MemoryMap::MemoryMap()
{
	memory = new byte[ADDR_DATA_LENGTH];
	memset(memory, 0, ADDR_DATA_LENGTH);//sets whole block of bytes to 0
}

MemoryMap::~MemoryMap()
{
    delete[] memory;
}

MemoryMap::MemoryMap(const MemoryMap &a)
{
    memory = new byte[ADDR_DATA_LENGTH];
    memcpy(memory, a.memory, ADDR_DATA_LENGTH);
}
