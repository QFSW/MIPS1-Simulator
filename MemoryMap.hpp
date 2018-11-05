#ifndef MemoryMap_hpp
#define MemoryMap_hpp

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
            T read(size_t address)
            {
                if (address % sizeof(T) > 0) { throw BadMemoryAccess(address, "read data address was misaligned"); }
                else if (address == ADDR_GETC + 4 - sizeof(T)) { return std::getchar(); }
                else if (address >= ADDR_GETC && address < ADDR_GETC + 4 - sizeof(T)) { return 0; }
                else if (address >= ADDR_DATA && address <= ADDR_DATA + ADDR_DATA_LENGTH - sizeof(T))
                {
                    byte* memLocation = memory + (address - ADDR_DATA);
                    T data = *reinterpret_cast<T*>(memLocation);
                    return data;
                }
                else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
            }
            
            template <typename T>
            void write(size_t address, T data)
            {
                if (address % sizeof(T) > 0) { throw BadMemoryAccess(address, "write data address was misaligned"); }
                else if (address == ADDR_PUTC + 4 - sizeof(T)) { std::putchar(data); }
                else if (address >= ADDR_PUTC && address < ADDR_PUTC + 4 - sizeof(T)) { std::putchar(0); }
                else if (address >= ADDR_DATA && address <= ADDR_DATA + ADDR_DATA_LENGTH - sizeof(T))
                {
                    byte* memLocation = memory + (address - ADDR_DATA);
                    *reinterpret_cast<T*>(memLocation) = data;
                }
                else { throw BadMemoryAccess(address, "address was outside of the valid R/W memory range."); }
            }

		private:
			static const size_t ADDR_DATA = 0x20000000;
			static const size_t ADDR_GETC = 0x30000000;
			static const size_t ADDR_PUTC = 0x30000004;

			static const size_t ADDR_DATA_LENGTH = 0x4000000;

			byte* memory;
		};
	}
}

#endif
