#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "tsp.h"

namespace BruteForce
{
    void solveTSP(TSP &tsp);
    void solveTSPGPU(TSP &tsp);
};

#endif // BRUTE_FORCE_H