
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : test_tri.cpp
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:33
  -----------------------------------------------------------------------------------
 */

#include "tri.h"
#include <vector>
#include <random>
#include <functional>
#include <cassert>

using namespace std;

template<typename Fn, typename T>
void test_fonction_tri(Fn fonction, vector<T> a_tester) {
   vector<T> expected(a_tester);
   std::sort(expected.begin(), expected.end());
   fonction(a_tester.begin(), a_tester.end());
   assert(a_tester == expected);
}

int main() {
   size_t nombre_test = 10;
   size_t taille_vecteur = 15;
   vector<vector<int>> dataset(nombre_test, vector<int>(taille_vecteur));

   std::minstd_rand0 generator(std::random_device{}());
	for(auto& data : dataset) {
		 generator.seed(std::random_device{}());
		 generate(data.begin(), data.end(), generator);
	}

   for(const auto& data : dataset) {
      test_fonction_tri(tri_a_bulle<vector<int>::iterator> , data);
      test_fonction_tri(tri_par_insertion<vector<int>::iterator> , data);
      test_fonction_tri(tri_par_selection<vector<int>::iterator> , data);
   }
	 return 0;
}
