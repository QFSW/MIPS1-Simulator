#ifndef RInstructions_hpp
#define RInstructions_hpp

#include <stdio.h>
#include "Instructions.hpp"

namespace Clarkitechture
{
    namespace MIPS
    {
        class ADDInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ADDUInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SUBInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SUBUInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ANDInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ORInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class NORInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class XORInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MULTInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MULTUInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class DIVInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class DIVUInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MFHIInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MFLOInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MTHIInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class MTLOInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SLTInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class SLTUInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SLLInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SLLVInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SRLInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SRLVInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SRAInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };

        class SRAVInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class JRInstr : public JumpRInstruction
        {
        public:
            using JumpRInstruction::JumpRInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class JALRInstr : public JumpRInstruction
        {
        public:
            using JumpRInstruction::JumpRInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
    }
}

#endif
