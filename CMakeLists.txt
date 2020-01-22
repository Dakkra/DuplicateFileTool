cmake_minimum_required(VERSION 3.15)
project(DuplicateFileTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(DuplicateFileTool hash-library/sha256.h hash-library/sha256.cpp main.cpp)