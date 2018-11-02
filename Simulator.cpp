#include "Simulator.hpp"
#include "Instructions.hpp"
#include <fstream>
#include <vector>
#include <memory>

using namespace Clarkitechture::MIPS;

void Simulator::loadMachineCode(std::string fileName)
{
    std::ifstream binstream;
    binstream.open(fileName, std::ios_base::binary | std::ios_base::in | std::ios_base::ate);
    if (!binstream.is_open()) { throw "implement plz"; }
    
    instrCount = binstream.tellg();
    if (instrCount <= 0) { throw "implement plz"; }
    if (instrCount % 4 > 0) { throw "implement plz"; }
    binstream.seekg(0, std::ios::beg);
    
    instrs.resize(instrCount);
    char currChar = 0;
    uint32_t currWord = 0;
    for (size_t i = 0; i < instrCount; ++i)
    {
        int j = i % 4;
        size_t k = i / 4;
        binstream >> currChar;
        currWord |= (currChar << 8 * (3 - j++));
        
        if (j == 3) { instrs[k] = std::unique_ptr<Instruction>(BinaryDecoder::decodeInstruction(currWord)); }
    }
}
