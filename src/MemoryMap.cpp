#include "MemoryMap.hpp"
#include "ExceptionHandling.hpp"
#include <stdint.h>

using namespace Clarkitechture::MIPS;

MemoryMap::MemoryMap()
{
	memory = new byte[ADDR_DATA_LENGTH];
    instrMemory = new byte[ADDR_INSTR_LENGTH];
	memset(memory, 0, ADDR_DATA_LENGTH);
    memset(instrMemory, 0, ADDR_INSTR_LENGTH);
}

MemoryMap::~MemoryMap()
{
    delete[] memory;
    delete[] instrMemory;
}

MemoryMap::MemoryMap(const MemoryMap &a)
{
    memory = new byte[ADDR_DATA_LENGTH];
    instrMemory = new byte[ADDR_INSTR_LENGTH];
    memcpy(memory, a.memory, ADDR_DATA_LENGTH);
    memcpy(instrMemory, a.instrMemory, ADDR_INSTR_LENGTH);
}

void MemoryMap::memcpyInstrMemory(void* src, size_t size)
{
    memcpy(instrMemory, src, size);
}
