#ifndef MemoryMap_hpp
#define MemoryMap_hpp

#include <stdio.h>
#include <exception>
#include <string>
#include <stdint.h>

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

			uint32_t readWord(size_t address);
			void writeWord(size_t address, uint32_t data);

			byte readByte(size_t address);
			void writeByte(size_t address, byte data);

		private:
			static const size_t ADDR_DATA = 0x20000000;
			static const size_t ADDR_GETC = 0x30000000;
			static const size_t ADDR_PUTC = 0x30000004;

			static const size_t ADDR_DATA_LENGTH = 0x4000000;

			byte* memory;
            int blah;
		};
	}
}

#endif
