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
    
    uint32_t currWord = 0;
    char* currWordPtr = reinterpret_cast<char*>(&currWord);
    for (size_t i = 0; i < instrCount; ++i)
    {
        binstream.read(currWordPtr, 4);
        currWord = __builtin_bswap32(currWord);
        instrs[i] = std::shared_ptr<Instruction>(BinaryDecoder::decodeInstruction(currWord));
    }
}

void Simulator::executeNext()
{
    reg.PC += 4;
    size_t index = currInstrIndex();
    std::shared_ptr<Instruction> currentInstr;
    
    if (index < instrCount)
    {
        currentInstr = instrs[index];
        currentInstr->execute(mem, reg);
    }
    else { currentInstr = nullptr; }
    if (previousInstr) { previousInstr->delayedExecute(mem, reg); }
    
    if (!currentInstr && !previousInstr)
    {
        throw BadProgramCounter(reg.PC - 4, "PC was outside of the instruction memory space.");
    }
    
    previousInstr = currentInstr;
}

size_t Simulator::currInstrIndex()
{
    if (reg.PC % 4 > 0) { throw BadProgramCounter(reg.PC, "word misaligned PC"); }
    return reg.PC / 4 - 1;
}

bool Simulator::isDone() const
{
    return reg.PC == 0x0;
}

void Simulator::simulate()
{
    do { executeNext(); }
    while (!isDone());
}

byte Simulator::getExitCode() const
{
    return (byte)reg.read(2);
}
