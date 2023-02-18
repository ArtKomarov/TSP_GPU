#ifndef TSP_H
#define TSP_H

#include <iostream>

#include "optim_problem.h"

extern const char *DATA_PATH;
typedef int dist_t;

struct TSPSolution
{
    dist_t optimPathLength;
    int *optimPathSteps;
    float solutionTime;

    TSPSolution();
};

class TSP : public OptimProblem
{
    /// @brief Distances matrix between towns
    dist_t *dists;
    /// @brief Number of towns
    size_t townsNumber;
    /// @brief Salesman starting town
    int startTown;

    TSPSolution *solution;

public:
    TSP(size_t townsNumber);

    void assignDists(const dist_t *dists);
    void readDists(const char *filename);
    void readDists(std::istream &in = std::cin);
    void printDists(size_t indent = 3) const;

    dist_t &get(size_t row, size_t col);

    dist_t get(size_t row, size_t col) const;
    dist_t get(size_t i) const;
    const dist_t *getDists() const;

    size_t getTownsNumber() const;
    size_t getStartTown() const;

    dist_t getOptimPathLength() const;
    const int *getOptimPathSteps() const;
    float getSolutionTime() const;

    void setSolution(const TSPSolution &tspSolution);
    void setSolution(dist_t optimPathLength, const int *optimPathSteps, float solutionTime);
};

#endif // TSP_H
