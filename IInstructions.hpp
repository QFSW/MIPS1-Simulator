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
        
        class LBInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        private:
            byte data;
        };
        
        class LBUInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        private:
            byte data;
        };
        
        class SWInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SBInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class BEQInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
        
        class BGEZInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
        
        class BGEZALInstr : public BGEZInstr
        {
        public:
            using BGEZInstr::BGEZInstr;
            bool requiresLink() const override;
        };
        
        class BGTZInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
        
        class BLEZInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
        
        class BLTZInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
        
        class BLTZALInstr : public BLTZInstr
        {
        public:
            using BLTZInstr::BLTZInstr;
            bool requiresLink() const override;
        };
        
        class BNEInstr : public BranchIInstruction
        {
        public:
            using BranchIInstruction::BranchIInstruction;
            
        protected:
            bool evaluateCondition(const RegisterMap& reg) const override;
        };
    }
}

#endif
