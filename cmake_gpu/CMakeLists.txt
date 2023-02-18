cmake_minimum_required(VERSION 3.10)

set(CMAKE_CUDA_HOST_COMPILER, NVIDIA)

set(ENV{PATH} /usr/local/cuda-12.0/bin:$ENV{PATH})

find_program(CUDA_NVCC_COMPILER nvcc)

project(tsp_gpu)

find_package(CUDA REQUIRED)

add_definitions(-DGPU_COMPUTING)

set(SOURCE_DIR "../src")

set(CPP_SRC_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/brute_force.h
    ${SOURCE_DIR}/tsp.cpp
    ${SOURCE_DIR}/tsp.h
)

set(CUDA_SRC_FILES
    ${SOURCE_DIR}/brute_force_gpu.cu
)

set(OBJECT_FILES
    main.o
    tsp.o
    brute_force_gpu.o
)

add_custom_target(my_executable ALL
    COMMAND nvcc -c ${CUDA_SRC_FILES} -DGPU_COMPUTING VERBATIM DEPENDS ${CUDA_SRC_FILES}
    COMMAND g++ -c ${CPP_SRC_FILES} -DGPU_COMPUTING VERBATIM DEPENDS ${CPP_SRC_FILES}
    COMMAND nvcc ${OBJECT_FILES} -o output
    )
