#include <iostream>

#include "tsp.h"
#include "brute_force.h"

int main()
{
    TSP tsp(3);
    dist_t *distances = new dist_t[9];
    for (int i = 0; i < 9; ++i)
    {
        distances[i] = i + 1;
    }

    tsp.assignDists(distances);
    tsp.printDists();

    BruteForce::solveTSPGPU(tsp, 3);

    std::cout << "Travelling salesman path len: " << tsp.getOptimPathLength() << "\nHis path:\n 0 -> ";
    for (size_t i = 0; i < tsp.getTownsNumber() - 1; ++i)
    {
        std::cout << tsp.getOptimPathSteps()[i] << " -> ";
    }
    std::cout << "0" << std::endl;

    return 0;
}