#include <gtest/gtest.h>
#include <sstream>
#include "../src/tsp.h"
#include "../src/brute_force.h"

// Note: Test is not stable
TEST(BruteForceTest, solveTSP)
{
    try
    {
        TSP tsp(5);
        tsp.readDists("../data/dists_5_towns.txt");

        // Debug print
        BruteForce::solveTSP(tsp);

        EXPECT_EQ(tsp.getOptimPathLength(), 19);
    }
    catch (const std::exception &e)
    {
        // std::cout << "exception" << std::endl;
        EXPECT_STREQ(e.what(), "");
    }
}
