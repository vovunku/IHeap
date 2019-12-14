cmake_minimum_required(VERSION 3.15)
project(IHeap)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(googletest-master)

set(IHeap_lib IHeap_lib/include/Heap_Interface.h)

include_directories(googletest-master/googletest/include)
include_directories(IHeap_lib/include)
add_executable(IHeap main.cpp IHeap_lib/src/Binomial_Heap.cpp IHeap_lib/src/Leftist_Heap.cpp IHeap_lib/src/Skew_Heap.cpp)
add_library(heap_lib STATIC IHeap_lib/src/Binomial_Heap.cpp)
target_link_libraries(IHeap gtest gtest_main)