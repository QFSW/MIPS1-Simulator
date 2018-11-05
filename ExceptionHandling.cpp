#include "ExceptionHandling.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

const char * MIPSException::what() const throw()
{
    return message.c_str();
}

int MIPSException::exitCode() const { return 0; }

BadArithmeticOperation::BadArithmeticOperation(std::string innerException)
{
    this->innerException = innerException;
    createMessage();
}

void BadArithmeticOperation::createMessage()
{
    message = "Arithmetic error: " + innerException;
}

int BadArithmeticOperation::exitCode() const { return -10; }

BadRegisterRead::BadRegisterRead(size_t badIndex)
{
    this->badIndex = badIndex;
	createMessage();
}

void BadRegisterRead::createMessage()
{
	message = "Illegal Register Read: $" + std::to_string(badIndex) + " is not a valid register";
}

int BadRegisterRead::exitCode() const { return -20; }

BadMemoryAccess::BadMemoryAccess(size_t badAddress, std::string innerException)
{
    this->badAddress = badAddress;
    this->innerException = innerException;
    createMessage();
}

void BadMemoryAccess::createMessage()
{
    message = "Illegal Memory Operation at " + toHexStr(badAddress) + ": " + innerException;
}

int BadMemoryAccess::exitCode() const { return -11; }

BadInstructionDecode::BadInstructionDecode(uint32_t badInstr, std::string innerException)
{
    this->badInstr = badInstr;
    this->innerException = innerException;
    createMessage();
}

void BadInstructionDecode::createMessage()
{
    message = "Illegal instruction " + toHexStr(badInstr) + ": " + innerException;
}

int BadInstructionDecode::exitCode() const { return -12; }

BadBinaryIO::BadBinaryIO(std::string innerException)
{
    this->innerException = innerException;
    createMessage();
}

void BadBinaryIO::createMessage()
{
    message = "Binary IO error: " + innerException;
}

int BadBinaryIO::exitCode() const { return -21; }

BadProgramCounter::BadProgramCounter(uint32_t badPC, std::string innerException)
{
    this->badPC = badPC;
    this->innerException = innerException;
    createMessage();
}

void BadProgramCounter::createMessage()
{
    message = "Illegal PC " + toHexStr(badPC) + ": " + innerException;
}
