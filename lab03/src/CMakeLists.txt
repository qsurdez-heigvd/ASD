cmake_minimum_required(VERSION 3.16)
project(ASD-L3-Tris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L3-demo main_somebits_demo.cpp tri_rapide.h tri_par_base.h)
add_executable(L3-test sort_test.cpp tri_par_base.h)
add_executable(L3-time execution_time_test.cpp)