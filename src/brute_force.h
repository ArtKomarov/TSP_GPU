#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "tsp.h"

namespace BruteForce
{
    void solveTSP(TSP &tsp);
#ifdef GPU_COMPUTING
    void solveTSPGPU(TSP &tsp, size_t threadsNumber);
#endif
};

#endif // BRUTE_FORCE_H