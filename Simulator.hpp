#ifndef Simulator_hpp
#define Simulator_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include "RegisterMap.hpp"
#include "MemoryMap.hpp"
#include "Instructions.hpp"

namespace Clarkitechture
{
    namespace MIPS
    {
        class Simulator
        {
        public:
            void loadMachineCode(std::string fileName);
            
        private:
            size_t instrCount = 0;
            std::vector<std::unique_ptr<Instruction>> instrs;
            RegisterMap reg;
            MemoryMap mem;
        };
    }
}
#endif
