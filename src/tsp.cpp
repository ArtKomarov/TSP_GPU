#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "tsp.h"

// const char *PROJECT_PATH = "~/Main/Artem/TSP/";
// const char *DATA_PATH = (std::string(PROJECT_PATH) + "data/").c_str();

TSPSolution::TSPSolution() : optimPathLength(0),
                             optimPathSteps(nullptr),
                             solutionTime(0)
{
}

TSP::TSP(size_t townsNumber) : townsNumber(townsNumber),
                               dists(nullptr),
                               startTown(0) {}

void TSP::assignDists(const dist_t *dists)
{
    this->dists = new dist_t[townsNumber * townsNumber];

    for (size_t i = 0; i < townsNumber * townsNumber; ++i)
    {
        this->dists[i] = dists[i];
    }
}

void TSP::readDists(std::istream &in)
{
    dists = new dist_t[townsNumber * townsNumber];

    for (size_t i = 0; i < townsNumber * townsNumber; ++i)
    {
        in >> dists[i];
    }
}

void TSP::readDists(const char *filename)
{
    std::ifstream stream;
    stream.open(filename);

    if (!stream.is_open())
    {
        throw std::invalid_argument(std::string("open file '") + filename + "' failed!");
    }
    else
    {
        readDists(stream);
    }
}

void TSP::printDists(size_t indent) const
{
    if (dists == nullptr)
    {
        throw std::runtime_error("dists is nullptr");
    }

    for (size_t i = 0; i < townsNumber; ++i)
    {
        for (size_t j = 0; j < townsNumber; ++j)
        {
            std::cout << std::setw(indent) << dists[i * townsNumber + j];
        }
        std::cout << std::endl;
    }
}

dist_t &TSP::get(size_t row, size_t col)
{
    return dists[row * townsNumber + col];
}

dist_t TSP::get(size_t row, size_t col) const
{
    return dists[row * townsNumber + col];
}

dist_t TSP::get(size_t i) const
{
    return dists[i];
}

const dist_t *TSP::getDists() const
{
    return dists;
}

size_t TSP::getTownsNumber() const
{
    return townsNumber;
}

size_t TSP::getStartTown() const
{
    return startTown;
}

dist_t TSP::getOptimPathLength() const
{
    return solution->optimPathLength;
}

const int *TSP::getOptimPathSteps() const
{
    return solution->optimPathSteps;
}

float TSP::getSolutionTime() const
{
    return solution->solutionTime;
}

void TSP::setSolution(dist_t optimPathLength, const int *optimPathSteps, float solutionTime)
{
    solution = new TSPSolution();
    solution->optimPathSteps = new int[this->getTownsNumber() - 1];

    for (size_t i = 0; i < getTownsNumber() - 1; ++i)
    {
        solution->optimPathSteps[i] = optimPathSteps[i];
    }

    solution->optimPathLength = optimPathLength;
}

void TSP::setSolution(const TSPSolution &tspSolution)
{
    setSolution(tspSolution.optimPathLength, tspSolution.optimPathSteps, tspSolution.solutionTime);
}
