#include "Utils.hpp"
#include <stdint.h>

std::string Clarkitechture::Utils::toHexStr(size_t hex)
{
    std::stringstream hexStream;
    hexStream << std::hex << std::uppercase << hex;
    return "0x" + hexStream.str();
}
