cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)
project(my-ostis-system VERSION 0.10.0 LANGUAGES C CXX)

set(SC_EXTENSIONS_DIRECTORY "${CMAKE_BINARY_DIR}/Release/lib/extensions")

message(STATUS "Extensions will go to: ${SC_EXTENSIONS_DIRECTORY}")
include(GoogleTest)
find_package(GTest REQUIRED)

add_subdirectory(problem-solver)
