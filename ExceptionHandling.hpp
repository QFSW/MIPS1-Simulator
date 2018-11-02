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

		protected:
			virtual void createMessage() = 0;

			std::string message;
		};

        class BadRegisterRead : public MIPSException
        {
        public:
            BadRegisterRead(size_t badIndex);
            
		protected:
			void createMessage();

        private:
            size_t badIndex;
        };
        
        class BadMemoryAccess : public MIPSException
        {
        public:
            BadMemoryAccess(size_t badAddress, std::string innerException);
            
        protected:
            void createMessage();
            
        private:
            std::string innerException;
            size_t badAddress;
        };
        
        class BadInstructionDecode : public MIPSException
        {
        public:
            BadInstructionDecode(uint32_t badInstr, std::string innerException);
            
        protected:
            void createMessage();
            
        private:
            std::string innerException;
            uint32_t badInstr;
        };
        
        class BadBinaryIO : public MIPSException
        {
        public:
            BadBinaryIO(std::string innerException);
            
        protected:
            void createMessage();
            
        private:
            std::string innerException;
        };
        
        class BadProgramCounter : public MIPSException
        {
        public:
            BadProgramCounter(uint32_t badPC, std::string innerException);
            
        protected:
            void createMessage();
            
        private:
            std::string innerException;
            uint32_t badPC;  
        };
    }
}

#endif
