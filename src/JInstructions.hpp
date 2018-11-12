#ifndef JInstructions_hpp
#define JInstructions_hpp

#include <stdio.h>
#include "Instructions.hpp"

namespace Clarkitechture
{
    namespace MIPS
    {
        class JInstr : public JInstruction
        {
        public:
            using JInstruction::JInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;

        private:
            u_int32_t addr;
        };

        class JALInstr : public JInstr
        {
        public:
            using JInstr::JInstr;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
    }
}

#endif
