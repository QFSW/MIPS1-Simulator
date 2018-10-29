#ifndef BinaryIO_hpp
#define BinaryIO_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace Clarkitechture
{
	namespace MIPS
	{
		void readBinary(std::string fileName, std::vector<int>& outVec);
	}
}

#endif
