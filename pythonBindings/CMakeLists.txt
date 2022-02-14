cmake_minimum_required(VERSION 3.4)
project(pylibneurons)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${SOURCE_DIR})
add_subdirectory(pybind11)
file(GLOB CPPS "*/*.cpp")
pybind11_add_module(
    ${PROJECT_NAME}
    ${CPPS} PythonBindings.cpp
)

target_include_directories(
   ${PROJECT_NAME}
    PRIVATE "network"
    PRIVATE "neurons"
    PRIVATE "interfaces"
    PRIVATE "exceptions"
    PRIVATE "connection"
    PRIVATE "base"
)

