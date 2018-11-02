#include "ExceptionHandling.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>

using namespace Clarkitechture::MIPS;
using namespace Clarkitechture::Utils;

BadRegisterRead::BadRegisterRead(size_t badIndex)
{
    this->badIndex = badIndex;
	createMessage();
}

void BadRegisterRead::createMessage()
{
	message = "Illegal Register Read: $" + std::to_string(badIndex) + " is not a valid register";
}

const char * MIPSException::what() const throw()
{
    return message.c_str();
}

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

BadBinaryIO::BadBinaryIO(std::string innerException)
{
    this->innerException = innerException;
    createMessage();
}

void BadBinaryIO::createMessage()
{
    message = "Binary IO error: " + innerException;
}

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
