#include "Simulator.hpp"
#include "Instructions.hpp"
#include "ExceptionHandling.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>

using namespace Clarkitechture::MIPS;

void Simulator::loadMachineCode(std::string fileName)
{
    std::ifstream binstream;
    binstream.open(fileName, std::ios_base::binary | std::ios_base::in | std::ios_base::ate);
    if (!binstream.is_open()) { throw BadBinaryIO("could not open file " + fileName); }
    
    size_t size = binstream.tellg();
    if (size <= 0) { throw BadBinaryIO("file was empty"); }
    if (size % 4 > 0) { throw BadBinaryIO("file contained a non integral word count"); }
    binstream.seekg(0, std::ios::beg);
    
    instrCount = size / 4;
    instrs.resize(instrCount);
    
    char currChar = 0;
    uint32_t currWord = 0;
    for (size_t i = 0; i < size; ++i)
    {
        int j = i % 4;
        size_t k = i / 4;
        binstream.read(&currChar, sizeof(char));
        currWord |= (currChar << 8 * (3 - j));
        
        
        if (j == 3)
        {
            instrs[k] = std::shared_ptr<Instruction>(BinaryDecoder::decodeInstruction(currWord));
            currWord = 0;
        }
    }
}

void Simulator::executeNext()
{
    reg.PC += 4;
    size_t index = currInstrIndex();
    
    if (previousInstr) { previousInstr->delayedExecute(mem, reg); }
    instrs[index]->execute(mem, reg);
    previousInstr = instrs[index];
}

size_t Simulator::currInstrIndex()
{
    if (reg.PC % 4 > 0) { throw BadProgramCounter(reg.PC, "word misaligned PC"); }
    size_t index = reg.PC / 4 - 1;
    
    if (index >= instrCount) { throw BadProgramCounter(reg.PC - 4, "PC was outside of the instruction memory space."); }
    return index;
}

bool Simulator::isDone()
{
    return reg.PC == 0x0 && previousInstr != nullptr;
}

void Simulator::simulate()
{
    while (!isDone()) { executeNext(); }
}
