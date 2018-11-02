#ifndef RegisterMap_hpp
#define RegisterMap_hpp

#include <stdio.h>
#include <stdint.h>

namespace Clarkitechture
{
    namespace MIPS
    {
        class RegisterMap
        {
        public:
            uint32_t PC = 0;
            uint32_t LR = 0;
            
            uint32_t hi = 0;
            uint32_t lo = 0;
            
            RegisterMap();
            
            const uint32_t read(size_t regIndex) const;
            void write(size_t regIndex, uint32_t regValue);
            
            const static size_t REGISTER_COUNT = 32;
            
        private:
			uint32_t registers[REGISTER_COUNT];
        };
    }
}

#endif

