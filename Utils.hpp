#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <sstream>

namespace Clarkitechture
{
    namespace Utils
    {
        template <typename T>
        bool sameSign(T a, T b)
        {
            if (a < 0 & b < 0) { return true; }
            if (a >= 0 & b >= 0) { return true; }
            else { return false; }
        }
        
        std::string toHexStr(uint32_t hex);
    }
}

#endif
