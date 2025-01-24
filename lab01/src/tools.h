
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : tools.h
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:33
  -----------------------------------------------------------------------------------
 */

#ifndef ASD2022_L1_COMPLEXITE_TOOLS_H
#define ASD2022_L1_COMPLEXITE_TOOLS_H

#include <vector>
#include <cstdint>
#include <map>
#include <string>
#include "op_counter.h"

constexpr uint32_t SEED = 42;

enum class TYPE_DATASET { CROISSANT, DECROISSANT, ALEATOIRE, PRESQUE_TRIEE};

std::map<TYPE_DATASET, std::string> nom_enum {{TYPE_DATASET::CROISSANT, "dataset_croissant"},
                                    {TYPE_DATASET::DECROISSANT, "dataset_decroissant"},
                                    {TYPE_DATASET::ALEATOIRE, "dataset_aleatoire"},
                                    {TYPE_DATASET::PRESQUE_TRIEE, "dataset_presque_trie"}};

template <typename T>
std::vector<T> creation_dataset(size_t N, uint32_t seed, TYPE_DATASET type);

template <typename Fn, typename T>
double mesure_temps_execution(Fn fonction, std::vector<T> dataset);

template<typename Fn, typename T>
unsigned long long mesure_aff(Fn fonction, std::vector<OpCounter<T>> dataset);

template<typename Fn, typename T>
unsigned long long mesure_op(Fn fonction, std::vector<OpCounter<T>> dataset);

template <typename T>
void exporter_csv(std::string const& path_filename, const std::vector<unsigned>& taille_echantillon,
                  const std::map<std::string, std::vector<T>>& mesures2);

#include "tools_impl.h"

#endif //ASD2022_L1_COMPLEXITE_TOOLS_H
