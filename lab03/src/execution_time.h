/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : execution_time.h
 * @date : 21.03.2023
 */
#ifndef ASD_LABOS_2021_EXECUTION_TIME_H
#define ASD_LABOS_2021_EXECUTION_TIME_H

#include <vector>
#include <chrono>

/**
* function that measures the execution time of a certain function
 * @tparam Fn: generic type for passing the sort function
 * @tparam T: generic type of the dataset content to be sorted
 * @param function: function whose execution time is specified
 * @param dataset: dataset to sort
 * @return execution time
 */
template<typename Fn, typename T>
double
measure_execution_time(Fn function, std::vector<T> dataset, size_t number_of_tests) {

	double final_time = 0;

	for (size_t i = 0; i < number_of_tests; ++i) {

		auto timer_start = std::chrono::high_resolution_clock::now();
		function(dataset.begin(), dataset.end());
		auto timer_end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> time_ms = timer_end - timer_start;
		final_time += (time_ms.count() / (double) (number_of_tests));
	}

	return final_time;

}

#endif //ASD_LABOS_2021_EXECUTION_TIME_H
