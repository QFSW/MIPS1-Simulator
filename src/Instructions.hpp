#ifndef Instructions_hpp
#define Instructions_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "MemoryMap.hpp"
#include "RegisterMap.hpp"

typedef unsigned char byte;

namespace Clarkitechture
{
	namespace MIPS
	{
		class Instruction
		{
		public:
			virtual void execute(MemoryMap &mem, RegisterMap &reg) = 0;
            virtual void delayedExecute(MemoryMap &mem, RegisterMap &reg);
		};

		class RInstruction : public Instruction
		{
		public:
			RInstruction(byte rs, byte rt, byte rd, byte shamt);

		protected:
			byte rs;
			byte rt;
			byte rd;
			byte shamt;
		};

		class IInstruction : public Instruction
		{
		public:
			IInstruction(byte rs, byte rt, uint16_t constant);

		protected:
			byte rs;
			byte rt;
			uint16_t constant;
		};
        
        class JInstruction : public Instruction
        {
        public:
            JInstruction(uint32_t target);
            
        protected:
            uint32_t target;
        };

        class JumpRInstruction : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        protected:
            uint32_t jumpAddr;
        };
        
        class BranchIInstruction : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
            void delayedExecute(MemoryMap &mem, RegisterMap &reg) override;
            
        protected:
            virtual bool requiresLink() const;
            virtual bool evaluateCondition(const RegisterMap& reg) const = 0;
            
        private:
            bool conditionMet;
            uint32_t branchAddr;
        };
        
		class BinaryDecoder
		{
		public:
			static Instruction* decodeInstruction(uint32_t bin);

		private:
			static RInstruction* decodeRInstruction(uint32_t bin);
			static IInstruction* decodeIInstruction(uint32_t bin);
            static JInstruction* decodeJInstruction(uint32_t bin);
            static BranchIInstruction* decodeBranchInstruction(uint32_t bin);
		};
	}
}

#endif
