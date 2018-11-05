#ifndef ExceptionHandling_hpp
#define ExceptionHandling_hpp

#include <stdio.h>
#include <exception>
#include <string>

namespace Clarkitechture
{
    namespace MIPS
    {
		class MIPSException : public std::exception
		{
		public:
			const char * what() const throw();
            virtual int exitCode() const;

		protected:
			virtual void createMessage() = 0;
            
			std::string message;
		};
        
        class BadArithmeticOperation : public MIPSException
        {
        public:
            BadArithmeticOperation(std::string innerException);
            int exitCode() const override;
            
        protected:
            void createMessage() override;
            
        private:
            std::string innerException;
        };

        class BadRegisterRead : public MIPSException
        {
        public:
            BadRegisterRead(size_t badIndex);
            int exitCode() const override;
            
		protected:
			void createMessage() override;

        private:
            size_t badIndex;
        };
        
        class BadMemoryAccess : public MIPSException
        {
        public:
            BadMemoryAccess(size_t badAddress, std::string innerException);
            int exitCode() const override;
            
        protected:
            void createMessage() override;
            
        private:
            std::string innerException;
            size_t badAddress;
        };
        
        class BadInstructionDecode : public MIPSException
        {
        public:
            BadInstructionDecode(uint32_t badInstr, std::string innerException);
            int exitCode() const override;
            
        protected:
            void createMessage() override;
            
        private:
            std::string innerException;
            uint32_t badInstr;
        };
        
        class BadBinaryIO : public MIPSException
        {
        public:
            BadBinaryIO(std::string innerException);
            int exitCode() const override;
            
        protected:
            void createMessage() override;
            
        private:
            std::string innerException;
        };
        
        class BadProgramCounter : public MIPSException
        {
        public:
            BadProgramCounter(uint32_t badPC, std::string innerException);
            
        protected:
            void createMessage() override;
            
        private:
            std::string innerException;
            uint32_t badPC;  
        };
    }
}

#endif
