#ifndef MemoryMap_hpp
#define MemoryMap_hpp

#include <unordered_map>
#include <stdio.h>
#include <exception>
#include <string>
#include <stdint.h>
#include "ExceptionHandling.hpp"

typedef unsigned char byte;

namespace Clarkitechture
{
	namespace MIPS
	{
		class MemoryMap
		{
		public:
			MemoryMap();
			~MemoryMap();
            MemoryMap(const MemoryMap &a);

            template <typename T>
            T read(size_t address, bool aligned = true)
            {
                if (aligned && address % sizeof(T) > 0) { throw BadMemoryAccess(address, "read data address was misaligned"); }
                else if (address == ADDR_GETC + 4 - sizeof(T)) { return std::getchar(); }
                else if (address >= ADDR_GETC && address < ADDR_GETC + 4 - sizeof(T)) { std::getchar(); return 0; }
                else if (address >= ADDR_DATA && address <= ADDR_DATA + ADDR_DATA_LENGTH - sizeof(T))
                {
                    T data = 0;
                    size_t memLocation = address - ADDR_DATA;
                    for (int i = 0; i < sizeof(T); i++)
                    {
                        int shamt = 8 * (sizeof(T) - i - 1);
                        data |= (memory[memLocation + i] << shamt);
                    }   

                    return data;
                }
                else if (address >= ADDR_INSTR && address <= ADDR_INSTR + ADDR_INSTR_LENGTH - sizeof(T))
                {
                    if (address - ADDR_INSTR < instrMemorySize) { return 0; }
                    else
                    {
                        byte* memLocation = instrMemory + (address - ADDR_INSTR);
                        T data = *reinterpret_cast<T*>(memLocation);
                        return data;
                    }
                }
                else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
            }
            
            template <typename T>
            void write(size_t address, T data, bool aligned = true)
            {
                if (aligned && address % sizeof(T) > 0) { throw BadMemoryAccess(address, "write data address was misaligned"); }
                else if (address == ADDR_PUTC + 4 - sizeof(T)) { std::putchar(data); }
                else if (address >= ADDR_PUTC && address < ADDR_PUTC + 4 - sizeof(T)) { std::putchar(0); }
                else if (address >= ADDR_DATA && address <= ADDR_DATA + ADDR_DATA_LENGTH - sizeof(T))
                {
                    size_t memLocation = address - ADDR_DATA;
                    for (int i = 0; i < sizeof(T); i++)
                    {
                        int shamt = 8 * (sizeof(T) - i - 1);
                        memory[memLocation + i] = data >> shamt;
                    } 
                }
                else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
            }
            
            void initInstrMemory(byte* instrMem, size_t size);

            static const size_t ADDR_DATA = 0x20000000;
            static const size_t ADDR_INSTR = 0x10000000;
            static const size_t ADDR_GETC = 0x30000000;
            static const size_t ADDR_PUTC = 0x30000004;
            static const size_t ADDR_DATA_LENGTH = 0x4000000;
            static const size_t ADDR_INSTR_LENGTH = 0x1000000;
            
		private:
            std::unordered_map<uint32_t, byte> memory;
            byte* instrMemory;
            size_t instrMemorySize = 0;
		};
	}
}

#endif
