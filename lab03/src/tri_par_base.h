#ifndef TRI_PAR_BASE
#define TRI_PAR_BASE

#include <iterator>
#include <type_traits>
#include "some_bits.h"
#include <vector>
#include <iostream>
#include <limits>

/**
 * function to sort according to the counting sort algorithm
 * @tparam Iterator generic type for passing the iterator
 * @tparam Fn generic type for passing the sort function
 * @param first first iterator of the object
 * @param last last iterator of the object
 * @param output_first the first iterator of the output object
 * @param index_fn key function to sort the objects
 * @param N size of the object from first to last
 */
template<typename Iterator, typename Fn>
void tri_comptage(Iterator first, Iterator last, Iterator output_first, Fn index_fn,
						size_t N) {
	std::vector<size_t> compteur(N + 1, 0);
	for (auto it = first; it != last; ++it) {
		++compteur.at(index_fn(*it) + 1);
	}

	for (auto it = std::next(compteur.begin()); it != compteur.end(); ++it) {
		*it += size_t(*(std::prev(it)));
	}

	for (auto it = first; it != last; ++it) {
		*(std::next(output_first,
						std::vector<std::size_t>::difference_type(compteur.at
							(index_fn(*it))))) =
			*it;
		++compteur.at(index_fn(*it));
	}

}

/**
 * function to sort according to the radix sort algorithm
 * @tparam Iterator generic type for passing the iterator
 * @tparam NBITS number of bits
 * @param first first iterator of the object
 * @param last last iterator of the object
 */
template<typename Iterator, size_t NBITS>
void tri_par_base(Iterator first, Iterator last) {
	using T = typename Iterator::value_type;
	size_t part = std::numeric_limits<T>::digits / NBITS;
	static_assert(std::is_unsigned<T>::value);

	std::vector<std::vector<T>> result(part, std::vector<T>((size_t) (std::distance
		(first,
		 last))));

	for (size_t i = 0; i < part; i++) {
		tri_comptage(first, last, result.at(i).begin(), SomeBits<T>(NBITS, i),
						 1 << NBITS);
		copy(result.at(i).begin(), result.at(i).end(), first);
	}
	/*for (auto i : result) {
		for (auto j : i){
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}*/

}

#endif