#include <iostream>

#include "tsp.h"
#include "brute_force.h"

int main()
{
    TSP tsp(5);
    tsp.readDists("../data/dists_5_towns.txt");
    tsp.printDists(5);

#ifdef GPU_COMPUTING
    BruteForce::solveTSPGPU(tsp, 3);
#else
    BruteForce::solveTSP(tsp);
#endif

    std::cout << "Travelling salesman path len: " << tsp.getOptimPathLength() << "\nHis path:\n 0 -> ";
    for (size_t i = 0; i < tsp.getTownsNumber() - 1; ++i)
    {
        std::cout << tsp.getOptimPathSteps()[i] << " -> ";
    }
    std::cout << "0" << std::endl;

    return 0;
}