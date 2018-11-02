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

		class BinaryDecoder
		{
		public:
			static Instruction* decodeInstruction(uint32_t bin);

		private:
			static RInstruction* decodeRInstruction(uint32_t bin);
			static IInstruction* decodeIInstruction(uint32_t bin);
		};

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
        
        class ANDIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ORInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class ORIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class XORInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class XORIInstr : public IInstruction
        {
        public:
            using IInstruction::IInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
        
        class JRInstr : public RInstruction
        {
        public:
            using RInstruction::RInstruction;
            void execute(MemoryMap &mem, RegisterMap &reg) override;
        };
	}
}

#endif
