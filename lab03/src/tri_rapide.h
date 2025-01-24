#ifndef TRI_RAPIDE
#define TRI_RAPIDE

#include <algorithm>
#include <random>

/**
 * function to partition an object knowing the last position is the pivot
 * @tparam Iterator generic type for passing the iterator
 * @param first first iterator of the object
 * @param last last iterator of the object
 * @return the new position of the pivot
 */
template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {

	Iterator i = std::prev(first);
	Iterator j = std::prev(last);

	while (true) {
		do {
			++i;
		} while (*i < *std::prev(last));

		do {
			j--;
		} while (j > first && *std::prev(last) < *j);

		if (i >= j)
			break;

		std::iter_swap(i, j);
	}
	std::iter_swap(i, std::prev(last));
	return i;
}

/**
 * function to sort according to the half recursive quicksort algorithm
 * @tparam Iterator generic type for passing the iterator
 * @param first first iterator of the object
 * @param last last iterator of the object
 */
template<typename Iterator>
void tri_rapide(Iterator first, Iterator last) {

	while (distance(first, last) > 1) {


		std::random_device random;
		auto number_of_jumps = std::distance(last, first);
		auto pivot = first + random() % number_of_jumps;

		std::iter_swap(std::prev(last), pivot);

		auto new_pivot = partition(first, last);

		if (std::distance(first, new_pivot) < std::distance(new_pivot, last)) {
			tri_rapide(first, new_pivot);
			first = std::next(new_pivot);
		} else {
			tri_rapide(std::next(new_pivot), last);
			last = new_pivot;
		}
	}
}

#endif