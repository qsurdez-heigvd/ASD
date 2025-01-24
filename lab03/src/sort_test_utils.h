/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : sort_test_utils.cpp
 * @date : 21.03.2023
 */
#ifndef ASD_LABOS_2021_TEST_FUNCTION_H
#define ASD_LABOS_2021_TEST_FUNCTION_H

#include <vector>

std::vector<std::vector<unsigned int>> test_vector = {
	{3,       847,       1234,  45,    65,   100, 12, 50},
	{2,       3,         4,     5,     5,    6,   5},
	{1234,    1234,      1234,  1234,  1234, 1234},
	{34,      567,       12,    135,   500},
	{0,       0,         0,     0,     0,    0},
	{1234567, 293847934, 66000, 34000, 34},
	{3,       2}
};

std::vector<std::vector<unsigned int>> after_one_partition = {
	{3,    12,        45,    50,    65,   100, 847, 1234},
	{2,    3,         4,     5,     5,    6,   5},
	{1234, 1234,      1234,  1234,  1234, 1234},
	{34,   135,       12,    500,   567},
	{0,    0,         0,     0,     0,    0},
	{34,   293847934, 66000, 34000, 1234567},
	{2,    3},
};

template<typename Fn>
void test_partition(Fn partition);

template<typename T>
void test_tri_comptage(std::vector<T> &toSort);

template<typename Fn>
void test_sort_function(Fn function, std::vector<unsigned int> set_to_be_sorted);

#include "sort_test_utils_impl.h"

#endif //ASD_LABOS_2021_TEST_FUNCTION_H
