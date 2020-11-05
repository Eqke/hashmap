cmake_minimum_required(VERSION 3.5)

project(hashmap LANGUAGES CXX)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

