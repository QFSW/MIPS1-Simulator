#ifndef IInstructions_hpp
#define IInstructions_hpp

#include <stdio.h>
#include "Instructions.hpp"

namespace Clarkitechture
{
    namespace MIPS
    {
        class ADDIUInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ADDIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ANDIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ORIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class XORIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SLTIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SLTIUInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class LWInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        private:
            uint32_t data;
        };
        
        class SWInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        private:
            uint32_t data;
            uint32_t addr;
        };
    }
}

#endif
