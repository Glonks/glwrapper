cmake_minimum_required(VERSION 3.16)
project(glwrapper)

option(GLWRAPPER_BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(external)
add_subdirectory(source)