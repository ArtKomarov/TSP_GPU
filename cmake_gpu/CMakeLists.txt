cmake_minimum_required(VERSION 3.10)

project(tsp_gpu)

find_package(CUDA REQUIRED)

set(SOURCE_DIR "../src")

set(CPP_SRC_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/brute_force.cpp
    ${SOURCE_DIR}/brute_force.h
    ${SOURCE_DIR}/tsp.cpp
    ${SOURCE_DIR}/tsp.h
)

set(CUDA_SRC_FILES
    src/brute_force_gpu.cu
)

add_definitions(-DGPU_COMPUTING)

# Set CUDA architecture
set(CUDA_ARCH "sm_30" CACHE STRING "CUDA architecture")

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=${CUDA_ARCH} -Wno-deprecated-gpu-targets)

# Compile CUDA code
CUDA_COMPILE(cuda_obj ${CUDA_SRC_FILES})

# Compile C++ code
add_executable(my_executable ${CPP_SRC_FILES} ${cuda_obj})

# Link CUDA library
target_link_libraries(my_executable ${CUDA_LIBRARIES})