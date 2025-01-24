
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : tools_impl.h
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:37
  -----------------------------------------------------------------------------------
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include "tools.h"
#include "op_counter.h"
#include "tri.h"

/**
 * fonction qui génère un dataset
 * @tparam T: type générique des éléments du dataset à trier
 * @param N: taille du dataset
 * @param seed: seed utilisée dans la cas du dataset aléatoire ou presque trié
 * @param type: type du dataset généré (croissant, décroissant, aléatoire, presque trié)
 * @return: vector contenant le dataset généré
 */
template <typename T>
std::vector<T> creation_dataset(size_t N, uint32_t seed, TYPE_DATASET type) {

   std::vector<T> dataset(N);
   std::minstd_rand0 generator(seed);
   std::iota(dataset.begin(), dataset.end(), 0);
   switch(type) {
      case TYPE_DATASET::CROISSANT:
         return dataset;
      case TYPE_DATASET::DECROISSANT:
         std::reverse(dataset.begin(), dataset.end());
         return dataset;
      case TYPE_DATASET::ALEATOIRE:
         shuffle(dataset.begin(), dataset.end(), generator);
         return dataset;
      case TYPE_DATASET::PRESQUE_TRIEE:
         std::vector<T> aleatoire = creation_dataset<T>(N, seed, TYPE_DATASET::ALEATOIRE);
         std::transform(dataset.begin(), dataset.end(), aleatoire.begin(), dataset.begin(),
                        [&generator](T a, T b) { return (generator() % 10) < 4 ? (b + a) * 0.5 : a;});
         return dataset;
   }
   return dataset;
}

/**
 * fonction qui mesure le temps d'exécution d'une certaine fonction
 * @tparam Fn: type générique permettant de passer la fonction de tri
 * @tparam T: type générique du contenu du dataset à trier
 * @param fonction: fonction dont on caclule le temps d'exécution
 * @param dataset: dataset à trier
 * @return temps d'exécution
 */
template <typename Fn, typename T>
double mesure_temps_execution(Fn fonction, std::vector<T> dataset){

   auto debut_timer = std::chrono::high_resolution_clock::now();
   fonction(dataset.begin(), dataset.end());
   auto fin_timer = std::chrono::high_resolution_clock::now();

   std::chrono::duration<double, std::milli> temps_ms = fin_timer - debut_timer;
   return temps_ms.count();
}

/**
 * fonction qui mesure le nombre d'affectations que fait une certaine fonction en triant un certain dataset
 *@tparam Fn: type générique permettant de passer la fonction de tri
 * @tparam T: type générique du contenu du dataset à trier
 * @param fonction: fonction dont on caclule le temps d'exécution
 * @param dataset: dataset à trier
 * @return nombre d'affectations
 */
template<typename Fn, typename T>
unsigned long long mesure_aff(Fn fonction, std::vector<OpCounter<T>> dataset) {
   OpCounter<T>::reset_aff();
   fonction(dataset.begin(), dataset.end());

   return OpCounter<T>::acces_aff();

}

/**
 * fonction qui mesure le nombre d'opérations que fait une certaine fonction en triant un certain dataset
 *@tparam Fn: type générique permettant de passer la fonction de tri
 * @tparam T: type générique du contenu du dataset à trier
 * @param fonction: fonction dont on caclule le temps d'exécution
 * @param dataset: dataset à trier
 * @return nombre d'opérations
 */
template<typename Fn, typename T>
unsigned long long mesure_op(Fn fonction, std::vector<OpCounter<T>> dataset) {
   OpCounter<T>::reset_op();
   fonction(dataset.begin(), dataset.end());

   return OpCounter<T>::acces_op();
}

/**
 * crée un csv contenant les valeurs du dataset trié
 * @tparam T: type générique du contenu du dataset à trier
 * @param path_filename: nom du chemin où stocker le fichier csv
 * @param taille_echantillon: taille du dataset à trier
 * @param mesures: mesures pour un certain paramètre pour un certain tri
 */
template <typename T>
void exporter_csv(std::string const& path_filename, const std::vector<unsigned>& taille_echantillon,
                  const std::map<std::string, std::vector<T>>& mesures) {

   std::ofstream out(path_filename);

   if(not out.is_open()) {
      std::cerr << "Pas pu ouvrir le fichier en écriture" << std::endl;
      return;
   }

   out << "N";
	 for (const auto& [clef, valeur] : mesures) {
		  out << "," << clef;
	 }
	 out << std::endl;
   for (size_t i = 0; i < taille_echantillon.size(); ++i) {
      out << taille_echantillon.at(i);
		 for (const auto& [clef, valeur] : mesures) {
			  out << "," << valeur.at(i);
		 }
			 out << std::endl;
		 }

   out << std::endl;

   out.close();
}
