#include "Utils.hpp"
#include <stdint.h>

std::string Clarkitechture::Utils::toHexStr(uint32_t hex)
{
    std::stringstream hexStream;
    hexStream << std::hex << std::uppercase << hex;
    return "0x" + hexStream.str();
}
