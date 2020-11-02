cmake_minimum_required(VERSION 3.5)

project(hashmap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(HashmapLib hashmap.cpp hashmap.h)

target_link_libraries(HashmapLib)

set(ListLib list.cpp list.h)
#set(ListLib HEADER lish.h)

add_library(ListLib STATIC ${ListLib})


target_link_libraries(ListLib)
target_compile_features(ListLib PRIVATE cxx_std_17)

set(UnitLib unit.cpp unit.h)
#set(UnitLib HEADER unit.h)

add_library(UnitLib STATIC ${UnitLib})

target_link_libraries(UnitLib)
target_compile_features(UnitLib PRIVATE cxx_std_17)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)

target_link_libraries(main PRIVATE ListLib UnitLib)
