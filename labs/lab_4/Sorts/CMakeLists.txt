cmake_minimum_required(VERSION 3.16)
project(SortingAlgorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/BinaryTreeSort)
include_directories(src/MSDRadixSort)

add_executable(SortingDemo
    app/main.cpp
    src/BinaryTreeSort/BinaryTreeSort.cpp
    src/MSDRadixSort/MSDRadixSort.cpp
)

set_target_properties(SortingDemo PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)