cmake_minimum_required(VERSION 3.16)
project(ASD2022-L1-Complexite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L1-example example.cpp tri.h
        op_counter.h)

set (
        L1-library
        tri.h
        tri_impl.h
        tools.h
        tools_impl.h
)

add_executable(L1-tri test_tri.cpp ${L1-library})
add_executable(L1-temps temps_calcul.cpp tri_impl.h ${L1-library})
add_executable(L1-operations_affectations compte_op_af.cpp ${L1-library})
add_executable(Test_tri test_tri.cpp ${L1-library})