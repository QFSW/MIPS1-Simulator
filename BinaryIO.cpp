#include <string>
#include <fstream>
#include <vector>
#include "BinaryIO.hpp"

using namespace Clarkitechture::MIPS;

void readBinary(std::string fileName, std::vector<int>& outVec)
{
	std::ifstream binstream;
	binstream.open(fileName, std::ios_base::binary | std::ios_base::in | std::ios_base::ate);
	if (!binstream.is_open()) { throw "implement plz"; }

	int size = binstream.tellg();
	if (size <= 0) { throw "implement plz"; }
	if (size % 4 > 0) { throw "implement plz"; }
	binstream.seekg(0, std::ios::beg);

	char currChar = 0;
	uint32_t currWord = 0;
	for (int i = 0; i < size; ++i)
	{
		int j = i % 4;
		binstream >> currChar;
		currWord |= (currChar << 8 * (3 - j++));

		if (j == 3) { outVec.push_back(currWord); }
	}
}