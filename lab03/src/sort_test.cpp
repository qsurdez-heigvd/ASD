/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : test_tri.cpp
 * @date : 21.03.2023
 */
#include "tri_par_base.h"
#include "tri_rapide.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <random>
#include "some_bits.h"
#include "sort_test_utils.h"
#include "sort_test_utils_impl.h"
#include "creation_dataset.h"

using namespace std;

int main() {

	test_partition(partition<vector<unsigned>::iterator>);

	size_t number_of_tests = 10;
	size_t vector_size = 15;
	vector<vector<unsigned>> dataset(number_of_tests, vector<unsigned>
		(vector_size));


	for (auto &data: dataset) {
		data = creation_dataset<unsigned>(vector_size, std::random_device{}());
	}

	for (const auto &data: dataset) {
		test_sort_function(tri_par_base<vector<unsigned>::iterator, 1u>, data);
		test_sort_function(tri_par_base<vector<unsigned>::iterator, 2u>, data);
		test_sort_function(tri_par_base<vector<unsigned>::iterator, 4u>, data);
		test_sort_function(tri_par_base<vector<unsigned>::iterator, 8u>, data);
		test_sort_function(tri_par_base<vector<unsigned>::iterator, 16u>, data);
		test_sort_function(tri_rapide<vector<unsigned>::iterator>, data);
      test_counting_sort<unsigned>(data);

	}

   cout << "All functions have passed their tests" << endl;

	return 0;

}
