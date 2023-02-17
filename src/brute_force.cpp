#include "brute_force.h"
#include "tsp.h"
#include <vector>
#include <stack>
#include <cmath>

void solveTSPGPUKernel(dist_t *dists)
{
}

namespace BruteForce
{
    void solveTSP(TSP &tsp)
    {
        dist_t optimPathLen = 0;
        size_t pathSize = tsp.getTownsNumber() - 1; // not include last move to the start town
        int *optimPath = new int[pathSize];
        int *currentPath = new int[pathSize];
        for (size_t i = 0; i < pathSize; ++i)
        {
            currentPath[i] = 1;
        }
        // std::stack<int> stack;
        // stack.push(tsp.getStartTown());

        int lastTownNumber = static_cast<int>(tsp.getTownsNumber() - 1);
        size_t depth = std::pow(tsp.getTownsNumber() - 1, pathSize) - 1;

        std::cout << "depth: " << depth << std::endl;
        for (size_t i = 0; i < depth; ++i)
        {
            if (i % 100000000 == 0)
            {
                std::cout << "i: " << i << std::endl;
            }
            // Check current path
            bool skip = false;
            for (size_t j1 = 0; j1 < pathSize; ++j1)
            {
                for (size_t j2 = 0; j2 < pathSize; ++j2)
                {
                    if (j1 != j2 && currentPath[j1] == currentPath[j2])
                    {
                        skip = true;
                        break;
                    }
                }
                if (skip)
                    break;
            }
            if (!skip)
            {
                std::cout << "currentPath check:          ";
                for (size_t i = 0; i < pathSize; ++i)
                {
                    std::cout << currentPath[i] << " " << std::flush;
                }
                std::cout << std::endl;
                //  Compute current path
                int previousTown = 0;
                dist_t currentPathLen = 0;

                for (size_t j = 0; j < pathSize; ++j)
                {
                    int town = currentPath[j];
                    currentPathLen += tsp.get(previousTown, town);
                    previousTown = town;
                }
                currentPathLen += tsp.get(previousTown, 0);

                if (optimPathLen == 0 || optimPathLen > currentPathLen)
                {
                    optimPathLen = currentPathLen;
                    std::copy(currentPath, currentPath + pathSize, optimPath);
                }
            }

            // Set next path
            size_t lastNonLastIndex = pathSize - 1;
            while (currentPath[lastNonLastIndex] == lastTownNumber)
            {
                currentPath[lastNonLastIndex] = 1;
                assert(lastNonLastIndex > 0);
                lastNonLastIndex--;
            }
            currentPath[lastNonLastIndex]++;
        }

        std::cout << "currentPath:" << std::endl;
        for (size_t i = 0; i < pathSize; ++i)
        {
            std::cout << currentPath[i] << " " << std::flush;
            // assert(currentPath[i] == static_cast<int>(lastTownNumber));
        }

        tsp.setSolution(optimPath, optimPathLen);

        delete[] optimPath;
        delete[] currentPath;
    }
}