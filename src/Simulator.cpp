#include "Simulator.hpp"
#include "Instructions.hpp"
#include "ExceptionHandling.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <iostream>

#if !(__GCC__ || __llvm__)
#if _MSC_VER
#include "intrin.h"
inline uint32_t __builtin_bswap32(uint32_t val) { return _byteswap_ulong(val); }
#else
inline uint32_t __builtin_bswap32(uint32_t val)
{
	return (((val & 0x000000FF) << 24) |
		((val & 0x0000FF00) << 8) |
		((val & 0x00FF0000) >> 8) |
		((val & 0xFF000000) >> 24));
}
#endif
#endif

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
    
    uint32_t* words = new uint32_t[instrCount];
    binstream.read(reinterpret_cast<char*>(words), size);
    mem.memcpyInstrMemory(words, size);
    
    try
    {
        for (size_t i = 0; i < instrCount; ++i)
        {
            words[i] = __builtin_bswap32(words[i]);
            instrs[i] = std::shared_ptr<Instruction>(BinaryDecoder::decodeInstruction(words[i]));
        }
        delete[] words;
    }
    catch (const MIPSException&)
    {
        delete[] words;
        throw;
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
