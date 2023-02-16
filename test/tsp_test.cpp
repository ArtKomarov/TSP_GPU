#include <gtest/gtest.h>
#include <sstream>
#include "../src/tsp.h"

// Note: Test is not stable
TEST(TSPTest, ReadAndPrintDists)
{
    try
    {
        TSP tsp(3);
        tsp.readDists("../data/test_data/dists1.txt");

        // Debug print
        tsp.printDists(4);

        testing::internal::CaptureStdout();

        tsp.printDists(4);

        const char *out = testing::internal::GetCapturedStdout().c_str();

        EXPECT_STREQ(out, "   1   2   3\n   4  55  66\n  77   8  99\n");
    }
    catch (const std::exception &e)
    {
        // std::cout << "exception" << std::endl;
        EXPECT_STREQ(e.what(), "");
    }
}
