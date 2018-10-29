#include <iostream>
#include "RegisterMap.hpp"
#include "ExceptionHandling.hpp"
#include "MemoryMap.hpp"
#include <stdint.h>
#include <vector>
#include <fstream>

// added readBinary and vector,fstream

void readBinary(std::string fileName, std::vector<int>& outVec);
int main(int argc, const char * argv[])
{
    using namespace Clarkitechture::MIPS;
    MemoryMap mem;
    
    
    try {
        mem.writeWord(0x0505A004, 'a');
    } catch (BadMemoryAccess e) {
        std::cout << e.what();
    }
    


	int b;
	std::cin >> b;
    
    return 0;
}

void readBinary(std::string fileName, std::vector<int>& outVec)
{
    std::ifstream binstream;
    binstream.open(fileName);
    std::cout << "loading...\n";
    int i = 0;
    char currChar = 0;
    uint32_t currWord = 0;
    while(binstream >> currChar)//can use myFunction as script to convert text to binary file.
    {
        currWord |= (currChar << 8 * (3 - i++));
        if (i == 4)
        {
            outVec.push_back(currWord);
            i = 0;
        }
    }
    
    if (i != 0) { throw "add expection plz"; }
}
