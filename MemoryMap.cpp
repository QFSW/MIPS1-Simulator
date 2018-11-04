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

uint32_t MemoryMap::readWord(size_t address)
{
    if (address % 4 > 0) { throw BadMemoryAccess(address, "read word address was word misaligned"); }
    else if (address == ADDR_GETC) { return std::getchar(); }//this allows the MIPS code to inset data, 1 char at time
    else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
    {
        byte* memLocation = memory + (address - ADDR_DATA);
        uint32_t data = *reinterpret_cast<uint32_t*>(memLocation);//converts byte pointer to wrod pointer.
        return data;
    }
    else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
}

byte MemoryMap::readByte(size_t address)
{
    if (address == ADDR_GETC + 3) { return std::getchar(); }
    else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
    {
        byte* memLocation = memory + (address - ADDR_DATA);
        byte data = *memLocation;
        return data;
    }
    else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
}

void MemoryMap::writeWord(size_t address, uint32_t data)
{
    if (address % 4 > 0) { throw BadMemoryAccess(address, "write word address was word misaligned"); }
    else if (address == ADDR_PUTC) { std::putchar(data); }
    else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
    {
        byte* memLocation = memory + (address - ADDR_DATA);
        *reinterpret_cast<uint32_t*>(memLocation) = data;//interpret as word and then change to the input data. written as big endian here: in order of most significant bytes: 3,2,1,0 per word aka stored normally per word
    }
    else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
}

void MemoryMap::writeByte(size_t address, byte data)
{
    if (address == ADDR_PUTC + 3) { std::putchar(data); }
    else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
    {
        byte* memLocation = memory + (address - ADDR_DATA);
        *memLocation = data;
    }
    else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
}
