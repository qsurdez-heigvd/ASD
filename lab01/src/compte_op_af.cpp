
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : compte_op_af.cpp
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:31
  -----------------------------------------------------------------------------------
 */

#include "op_counter.h"
#include "tri.h"
#include "tools.h"
#include "op_counter.h"
#include <vector>
#include <map>

#include <functional>

using namespace std;
int main() {

   TYPE_DATASET types_dataset[] = {TYPE_DATASET::CROISSANT, TYPE_DATASET::DECROISSANT,
                                   TYPE_DATASET::ALEATOIRE, TYPE_DATASET::PRESQUE_TRIEE};

   const vector<unsigned> tailles_dataset = {10, 75, 100, 1000, 5000, 7500,
															 10000, 20000, 50000, 75000, 100000};

   for(auto type : types_dataset){
      map<string, vector<unsigned long long>> nombre_operations{{"tri_a_bulle", {}}, {"tri_par_insertion", {}},
                                          {"tri_par_selection", {}}, {"sort", {}}, {"stable_sort", {}}};
      map<string, vector<unsigned long long>> nombre_affectations{{"tri_a_bulle", {}},
                                                                  {"tri_par_insertion", {}}, {"tri_par_selection", {}},
                                                                  {"sort", {}}, {"stable_sort", {}}};
      for(double N : tailles_dataset){
         vector<OpCounter<int>> dataset = creation_dataset<OpCounter<int>>((size_t) N, SEED, type);
         nombre_operations["tri_a_bulle"].push_back(mesure_op(tri_a_bulle<vector<OpCounter<int>>::iterator>, dataset));
         nombre_affectations["tri_a_bulle"].push_back(mesure_aff(tri_a_bulle<vector<OpCounter<int>>::iterator>, dataset));
         nombre_operations["tri_par_insertion"].push_back(mesure_op(tri_par_insertion<vector<OpCounter<int>>::iterator>, dataset));
         nombre_affectations["tri_par_insertion"].push_back(mesure_aff(tri_par_insertion<vector<OpCounter<int>>::iterator>, dataset));
         nombre_operations["tri_par_selection"].push_back(mesure_op(tri_par_selection<vector<OpCounter<int>>::iterator>, dataset));
         nombre_affectations["tri_par_selection"].push_back(mesure_aff(tri_par_selection<vector<OpCounter<int>>::iterator>, dataset));
         nombre_operations["sort"].push_back(mesure_op(sort<vector<OpCounter<int>>::iterator>, dataset));
         nombre_affectations["sort"].push_back(mesure_aff(sort<vector<OpCounter<int>>::iterator>, dataset));
         nombre_operations["stable_sort"].push_back(mesure_op(stable_sort<vector<OpCounter<int>>::iterator>, dataset));
         nombre_affectations["stable_sort"].push_back(mesure_aff(stable_sort<vector<OpCounter<int>>::iterator>, dataset));
      }

      string nom_fichier_op = "../../rapport/csv/mesure_nombre_operations_" + nom_enum[type] + ".csv";
      exporter_csv<unsigned long long>(nom_fichier_op, tailles_dataset, nombre_operations);
      string nom_fichier_aff = "../../rapport/csv/mesure_nombre_affectations_" + nom_enum[type] + ".csv";
      exporter_csv<unsigned long long>(nom_fichier_aff, tailles_dataset, nombre_affectations);
   }

   return 0;
}