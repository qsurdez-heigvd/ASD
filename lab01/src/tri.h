
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : tri.h
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:33
  -----------------------------------------------------------------------------------
 */

#ifndef ASD2022_L1_COMPLEXITE_TRI_H
#define ASD2022_L1_COMPLEXITE_TRI_H

template <typename RandomAccessIterator> void tri_a_bulle(
		  RandomAccessIterator debut, RandomAccessIterator fin);

template<typename RandomAccessIterator> void tri_par_insertion(RandomAccessIterator debut,
   RandomAccessIterator fin);

template <typename RandomAccessIterator> void tri_par_selection(RandomAccessIterator debut,
   RandomAccessIterator fin);

#include "tri_impl.h"
#endif //ASD2022_L1_COMPLEXITE_TRI_H
