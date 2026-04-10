cmake_minimum_required(VERSION 3.28)
project(AlgorithmAnalizer)

set(CMAKE_CXX_STANDARD 20)

find_package(Python3 REQUIRED COMPONENTS Development)

execute_process(
        COMMAND python -c "import numpy; print(numpy.get_include())"
        OUTPUT_VARIABLE NUMPY_INCLUDE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_executable(AlgorithmAnalizer main.cpp
        Algorithms.cpp
)

target_include_directories(AlgorithmAnalizer PRIVATE ${Python3_INCLUDE_DIRS} ${NUMPY_INCLUDE})
target_link_libraries(AlgorithmAnalizer PRIVATE ${Python3_LIBRARIES})