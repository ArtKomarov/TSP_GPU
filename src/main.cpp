#include <iostream>

#include "tsp.h"
#include "brute_force.h"

int main()
{
    std::cout << "Print 3x3 matrix:" << std::endl;
    TSP tsp(3);
    tsp.readDists();
    tsp.printDists();

    BruteForce::solveTSP(tsp);

    std::cout << "Travelling salesman path len: " << tsp.getOptimPathLength() << "\nHis path:\n 0 -> ";
    for (size_t i = 0; i < tsp.getTownsNumber() - 1; ++i)
    {
        std::cout << tsp.getOptimPathSteps()[i] << " -> ";
    }
    std::cout << "0" << std::endl;

    return 0;
}