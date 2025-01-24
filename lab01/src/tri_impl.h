#ifndef ASD2022_L1_COMPLEXITE_TRI_IMPL_H
#define ASD2022_L1_COMPLEXITE_TRI_IMPL_H

#include <iostream>
#include <algorithm>

/**
 * fonction qui trie un dataset avec l'algorithme du tri à bulle
 * @tparam RandomAccessIterator: type générique de l'itérateur
 * @param debut: itérateur indiquant le début du dataset à trier
 * @param fin: itérateur indiquant la fin du dataset à trier
 */
template <typename RandomAccessIterator> void tri_a_bulle(
		  RandomAccessIterator debut, RandomAccessIterator fin) {
	 for(auto i = debut; i != fin; ++i) {
		  for(auto j = debut; j < i; ++j) {
				if(*i < *j) {
					 iter_swap(i, j);
				}
		  }
	 }
}

/**
 * fonction qui trie un dataset avec l'algorithme du tri par insertion
 * @tparam RandomAccessIterator: type générique de l'itérateur
 * @param debut: itérateur indiquant le début du dataset à trier
 * @param fin: itérateur indiquant la fin du dataset à trier
 */
template<typename RandomAccessIterator>
void tri_par_insertion(RandomAccessIterator debut, RandomAccessIterator fin) {
for (auto i = debut; i != fin; ++i) {
      rotate(upper_bound(debut, i, *i), i, i+1);
   }
}

/**
 * fonction qui trie un dataset avec l'algorithme du tri par sélection
 * @tparam RandomAccessIterator: type générique de l'itérateur
 * @param debut: itérateur indiquant le début du dataset à trier
 * @param fin: itérateur indiquant la fin du dataset à trier
 */
template <typename RandomAccessIterator> void tri_par_selection(
   RandomAccessIterator debut, RandomAccessIterator fin) {
   for(auto i = debut; i != fin; ++i) {
      iter_swap(i, min_element(i, fin));
   }
}

#endif //ASD2022_L1_COMPLEXITE_TRI_IMPL_H
