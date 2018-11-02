#include <iostream>
#include "RegisterMap.hpp"
#include "ExceptionHandling.hpp"
#include "MemoryMap.hpp"
#include "Simulator.hpp"
#include <stdint.h>
#include <vector>

using namespace Clarkitechture::MIPS;
int main(int argc, const char * argv[])
{
    std::string fileName = "hello.bin";
    Simulator sim;
    
    try
    {
        std::cout << "loading binary file '" << fileName << "'..." << std::endl;
        sim.loadMachineCode(fileName);
        std::cout << "load success\nsimulating CPU...\n";
        std::cout << "=====================" << std::endl;
        sim.simulate();
        std::cout << "\n=====================" << std::endl;
        std::cout << "simulation success\n";
    }
    catch (const MIPSException &e) { std::cout << "\n\n" << e.what() << std::endl; }
    return 0;
}
