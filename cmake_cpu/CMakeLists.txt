cmake_minimum_required(VERSION 3.0)

project(tsp_cpu)

set(SOURCE_DIR "../src")

add_executable(tsp.out ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/tsp.cpp ${SOURCE_DIR}/tsp.h ${SOURCE_DIR}/brute_force.cpp ${SOURCE_DIR}/brute_force.h)