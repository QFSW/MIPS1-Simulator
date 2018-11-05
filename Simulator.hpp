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
            void simulate();
            byte getExitCode() const;
            
        private:
            bool isDone() const;
            void executeNext();
            size_t currInstrIndex();
            
            size_t instrCount = 0;
            std::vector<std::shared_ptr<Instruction>> instrs;
            std::shared_ptr<Instruction> previousInstr;
            
            RegisterMap reg;
            MemoryMap mem;
        };
    }
}
#endif
