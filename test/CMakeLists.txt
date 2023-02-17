cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

enable_testing()

# adding googletest
set(GOOGLETEST_PATH ~/local/googletest)
set(GTEST_INCLUDE_DIR ~/local/include/)
set(GTEST_LIBRARY ~/local/lib/)
set(GTEST_MAIN_LIBRARY ~/local/lib/)
find_package(GTest REQUIRED)

set(SOURCE_DIR "../src")

add_executable(
  tsp_test
  temp_test.cpp
  tsp_test.cpp
  brute_force_test.cpp
  ${SOURCE_DIR}/tsp.cpp
  ${SOURCE_DIR}/brute_force.cpp
)
target_link_libraries(
  tsp_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tsp_test)