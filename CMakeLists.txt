cmake_minimum_required (VERSION 3.15...3.22)

set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ version selection")  # or 11, 14, 17, 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # optional, ensure standard is supported
set(CMAKE_CXX_EXTENSIONS OFF)  # optional, keep compiler extensions off

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

project ("PyAES" LANGUAGES CXX)

include_directories(include)
add_subdirectory(pybind11)
pybind11_add_module(PyAES src/PyAES.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(PyAES
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
