#include "ExceptionHandling.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace Clarkitechture::MIPS;

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
    std::stringstream hexStream;
    hexStream << std::hex << std::uppercase << badAddress;
    message = "Illegal Memory Operation at 0x" + hexStream.str() + ": " + innerException;
}
