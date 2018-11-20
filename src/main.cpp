#include <iostream>
#include "RegisterMap.hpp"
#include "ExceptionHandling.hpp"
#include "MemoryMap.hpp"
#include "Simulator.hpp"
#include <stdint.h>
#include <vector>
#include <cstdlib>

using namespace Clarkitechture::MIPS;
int main(int argc, const char * argv[])
{
    std::string fileName;
    Simulator sim;
        
    try
    {
        if (argc <= 1) { throw BadBinaryIO("please add the file path to the binary code to simulate as the first argument."); }
        else { fileName = argv[1]; }

        std::cerr << "loading binary file '" << fileName << "'..." << std::endl;
        sim.loadMachineCode(fileName);
        std::cerr << "load success\nsimulating CPU...\n";
        std::cerr << "=====================" << std::endl;
        sim.simulate();
        std::cerr << "\n=====================" << std::endl;
        std::cerr << "simulation success\n";
        std::exit(sim.getExitCode());
    }
    catch (const MIPSException &e)
    {
        std::cerr << "\n\nsimulation failed\n" << e.what() << std::endl;
        std::exit(e.exitCode());
    }
    return 0;
}
