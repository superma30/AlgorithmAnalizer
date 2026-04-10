cmake_minimum_required(VERSION 3.28)
project(AlgorithmAnalizer)

set(CMAKE_CXX_STANDARD 20)

find_package(Python3 COMPONENTS Development)

execute_process(
        COMMAND python -c "import numpy; print(numpy.get_include())"
        RESULT_VARIABLE NUMPY_RESULT
        OUTPUT_VARIABLE NUMPY_INCLUDE
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NUMPY_RESULT EQUAL 0)
    set(HAS_NUMPY TRUE)
else()
    set(HAS_NUMPY FALSE)
endif()

add_executable(AlgorithmAnalizer main.cpp Algorithms.cpp)

if (Python3_FOUND AND HAS_NUMPY)
    target_compile_definitions(AlgorithmAnalizer PRIVATE USE_PYTHON)
    target_include_directories(AlgorithmAnalizer PRIVATE
            ${Python3_INCLUDE_DIRS}
            ${NUMPY_INCLUDE}
    )
    target_link_libraries(AlgorithmAnalizer PRIVATE ${Python3_LIBRARIES})
endif()