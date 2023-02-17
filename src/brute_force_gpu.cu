#include <vector>
#include <stack>
#include <cmath>
#include <cassert>
#include <algorithm>

#include <cuda_runtime.h>

#include "brute_force.h"
#include "tsp.h"

__global__ void solveTSPGPUKernel(dist_t *dists, int *optimPath, int *currentPath, dist_t *optimPathLen, size_t pathSize, size_t iterationsNumber, int lastTownNumber)
{
    // TODO: use shared memory

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int threadsNumber = blockDim.x * gridDim.x;
    size_t iters = iterationsNumber / threadsNumber;
    size_t startIter = idx * iters;
    if (idx == threadsNumber - 1)
    {
        // For last thread we take also the rest of iterations
        iters += iterationsNumber % threadsNumber;
    }

    size_t townsNumberToIterate = static_cast<size_t>(lastTownNumber);
    size_t currentIter = startIter;

    for (long i = pathSize - 1; i >= 0; --i)
    {
        // On the (currentIter == 1) current path should be 1 1 ... 1 2
        // On the (currentIter == townsNumberToIterate) it should be check of 1 1 ... 1 2 1
        currentPath[idx * pathSize + i] = static_cast<int>(currentIter % townsNumberToIterate + 1);
        currentIter = currentIter / townsNumberToIterate;
    }

    optimPathLen[idx] = 123456;

    for (size_t i = 0; i < iters; ++i)
    {
        // Check that current path is valid
        bool skip = false;
        for (size_t j1 = 0; j1 < pathSize; ++j1)
        {
            for (size_t j2 = 0; j2 < pathSize; ++j2)
            {
                if (j1 != j2 && currentPath[idx * pathSize + j1] == currentPath[idx * pathSize + j2])
                {
                    skip = true;
                    break;
                }
            }
            if (skip)
                break;
        }

        // Compute current path
        if (!skip)
        {
            int previousTown = 0;
            dist_t currentPathLen = 0;
            int townsTotalNumber = lastTownNumber + 1;

            for (size_t j = 0; j < pathSize; ++j)
            {
                int town = currentPath[idx * pathSize + j];
                currentPathLen += dists[previousTown * townsTotalNumber + town];
                previousTown = town;
            }
            currentPathLen += dists[previousTown * townsTotalNumber]; // plus distance to the first town (0)

            if (optimPathLen[idx] == 0 || optimPathLen[idx] > currentPathLen)
            {
                optimPathLen[idx] = currentPathLen;
                // std::copy(currentPath + idx * pathSize, currentPath + idx * pathSize + pathSize, optimPath + idx * pathSize);
                for (size_t k = 0; k < pathSize; ++k)
                {
                    (optimPath + idx * pathSize)[i] = (currentPath + idx * pathSize)[i];
                }
            }
        }

        // Set next path
        // lastNonLastIndex: Index of the last town in a path which is not equal to lastTownNumber (e.g. if lastTownNumber == 5, path == [2 1 5 3 2] => lastNonLastIndex == 2)
        size_t lastNonLastIndex = pathSize - 1;

        while (currentPath[idx * pathSize + lastNonLastIndex] == lastTownNumber)
        {
            currentPath[idx * pathSize + lastNonLastIndex] = 1;
            assert(lastNonLastIndex > 0 || (idx == threadsNumber - 1 && i == iters));
            lastNonLastIndex--;
        }

        currentPath[idx * pathSize + lastNonLastIndex]++;
    }
}

namespace BruteForce
{
    void solveTSPGPU(TSP &tsp, size_t threadsNumber)
    {
        const size_t townsNumber = tsp.getTownsNumber();
        size_t pathSize = townsNumber - 1; // not include last move to the start town
        int lastTownNumber = static_cast<int>(townsNumber - 1);

        // we will place towns with numbers [1-lastTownNumber] on pathSize places
        size_t iterationsNumber = std::pow(townsNumber - 1, pathSize);
        std::cout << "Consts: " << townsNumber << " " << pathSize << " " << lastTownNumber << " " << iterationsNumber << " " << std::endl;

        dist_t *d_optimPathLen;
        int *d_optimPath;
        int *d_currentPath;
        dist_t *d_dists;
        cudaMalloc((void **)&d_optimPathLen, threadsNumber * sizeof(dist_t));
        cudaMalloc((void **)&d_optimPath, threadsNumber * pathSize * sizeof(int));
        cudaMalloc((void **)&d_currentPath, threadsNumber * pathSize * sizeof(int));
        cudaMalloc((void **)&d_dists, townsNumber * townsNumber * sizeof(int));

        cudaMemcpy(d_dists, tsp.getDists(), townsNumber * townsNumber * sizeof(dist_t), cudaMemcpyHostToDevice);
        std::cout << "tsp.getDists()[2]: " << tsp.getDists()[2] << std::endl;

        solveTSPGPUKernel<<<1, threadsNumber>>>(d_dists, d_optimPath, d_currentPath, d_optimPathLen, pathSize, iterationsNumber, lastTownNumber);

        dist_t *h_optimPathLen = new dist_t[threadsNumber];
        cudaMemcpy(h_optimPathLen, d_optimPathLen, threadsNumber * sizeof(dist_t), cudaMemcpyDeviceToHost);
        std::cout << "h_optimPathLen: " << std::endl;
        for (int i = 0; i < threadsNumber; ++i)
        {
            std::cout << h_optimPathLen[i] << " ";
        }
        std::cout << std::endl;

        dist_t *argMinOptimPathLenIter = std::min_element(h_optimPathLen, h_optimPathLen + threadsNumber);
        size_t argMinOptimPathLen = argMinOptimPathLenIter - h_optimPathLen;
        assert(argMinOptimPathLen < threadsNumber);
        dist_t optimPathLen = h_optimPathLen[argMinOptimPathLen];

        int *optimPath = new int[pathSize];
        cudaMemcpy(optimPath, d_optimPath + argMinOptimPathLen * pathSize, pathSize * sizeof(int), cudaMemcpyDeviceToHost);
        std::cout << "Optim path before set: " << optimPathLen << std::endl;
        for (int i = 0; i < pathSize; ++i)
        {
            std::cout << optimPath[i] << " ";
        }
        std::cout << std::endl;

        tsp.setSolution(optimPath, optimPathLen);
    }
}