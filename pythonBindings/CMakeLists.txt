cmake_minimum_required(VERSION 3.4)
project(pylibneurons)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${SOURCE_DIR}/../include)
add_subdirectory(pybind11)
file(GLOB CPPS "../src/*.cpp")
pybind11_add_module(
    ${PROJECT_NAME}
    ${CPPS} PythonBindings.cpp
)

target_include_directories(
   ${PROJECT_NAME}
    PRIVATE "../include"
)

