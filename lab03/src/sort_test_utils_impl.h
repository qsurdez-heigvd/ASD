/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : sort_test_utils_impl.h
 * @date : 21.03.2023
 */

#ifndef ASD_LABOS_2021_SORT_TEST_UTILS_IMPL_H
#define ASD_LABOS_2021_SORT_TEST_UTILS_IMPL_H

#include "sort_test_utils.h"
#include <vector>
#include <cassert>
#include <algorithm>

/**
 * trivial functor to be used in our counting sort test function
 * @tparam T generic type to return the type that is parsed
 */
template<typename T>
class TestComptage {
public:
	T operator()(T const &t) {
		return t;
	}
};

/**
 * function that will test if the first partition af some chosen vectors is as attended
 * @tparam Fn generic type for passing the sort function
 * @param partition Function that needs to be parsed
 */
template<typename Fn>
void test_partition(Fn partition) {
	for (size_t i = 0; i < test_vector.size(); ++i) {
		partition(test_vector.at(i).begin(), test_vector.at(i).end());
		assert(test_vector.at(i) == after_one_partition.at(i));
	}
}

/**
 * function to test the counting sort function
 * @tparam T generic type of the elements of the vector
 * @param toSort: vector to be sorted
 */
template<typename T>
void test_counting_sort(std::vector<T> toSort) {
	std::vector<T> output(toSort.size());
	tri_comptage(toSort.begin(), toSort.end(), output.begin(),
					 TestComptage<T>(), 1 << toSort.size());
	assert(is_sorted(output.begin(), output.end()));
}

/**
 * function to test the sorting functions
 * @tparam Fn generic type for passing the sort function
 * @param function function to be tested
 * @param set_to_be_sorted set of elements to be sorted
 */
template<typename Fn>
void test_sort_function(Fn function, std::vector<unsigned int> set_to_be_sorted) {
	function(set_to_be_sorted.begin(), set_to_be_sorted.end());
	assert(is_sorted(set_to_be_sorted.begin(), set_to_be_sorted.end()));
}

#endif //ASD_LABOS_2021_SORT_TEST_UTILS_IMPL_H
