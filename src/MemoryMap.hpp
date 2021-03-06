#ifndef MemoryMap_hpp
#define MemoryMap_hpp

#include <unordered_map>
#include <stdio.h>
#include <exception>
#include <string>
#include <cstring>
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
            T read(size_t address)
            {
                if (address % sizeof(T) > 0) { throw BadMemoryAccess(address, "read data address was misaligned"); }
                else if (address >= ADDR_GETC && address <= ADDR_GETC + 4 - sizeof(T))
                {
                    int input = std::getchar();
                    if (input == EOF || feof(stdin))
                    {
                        int error = ferror(stdin);
                        if (error) { throw BadIO("stdin", error); }
                        else { return -1; }
                    }
                    else if (address == ADDR_GETC + 4 - sizeof(T)) { return input; }
                    else { return 0; }
                }
                else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
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
                else if (address >= ADDR_INSTR && address < ADDR_INSTR + instrMemorySize)
                {
                    byte* memLocation = instrMemory + (address - ADDR_INSTR);
                    T data = *reinterpret_cast<T*>(memLocation);
                    return bswap(data);
                }
                else if (address >= ADDR_INSTR && address < ADDR_INSTR + ADDR_INSTR_LENGTH) { return 0; }
                else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
            }
            
            template <typename T>
            void write(size_t address, T data)
            {
                if (address % sizeof(T) > 0) { throw BadMemoryAccess(address, "write data address was misaligned"); }
                else if (address >= ADDR_PUTC && address < ADDR_PUTC + 4)
                {
                    T val = address == ADDR_PUTC + 4 - sizeof(T) ? data : 0;
                    int ret = std::putchar(val);
                    if (ret == EOF)
                    {
                        int error = ferror(stdin);
                        if (error) { throw BadIO("stdout", error); }
                    }
                }
                else if (address >= ADDR_DATA && address < ADDR_DATA + ADDR_DATA_LENGTH)
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

            template <typename T>
            T bswap(T data)
            {
                byte* dataArray = reinterpret_cast<byte*>(&data);
                T newData = 0;
                for (int i = 0; i < sizeof(T); ++i)
                {
                    newData |= dataArray[i] << ((sizeof(T) - i - 1) * 8);
                }

                return newData;
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
