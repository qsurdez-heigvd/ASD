
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : temps_calcul.cpp
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:32
  -----------------------------------------------------------------------------------
 */

#include <vector>
#include <random>
#include <map>
#include "tri.h"
#include "tools.h"

using namespace std;

int main(){

   TYPE_DATASET types_dataset[] = {TYPE_DATASET::CROISSANT, TYPE_DATASET::DECROISSANT,
                                   TYPE_DATASET::ALEATOIRE, TYPE_DATASET::PRESQUE_TRIEE};
   const vector<unsigned> tailles_dataset = {10, 75, 100, 1000, 5000, 7500, 10000, 20000, 50000, 75000, 100000};

   for(auto type : types_dataset){
      map<string, vector<double>> mesures{{"tri_a_bulle", {}}, {"tri_par_insertion", {}},
                                         {"tri_par_selection", {}}, {"sort", {}}, {"stable_sort", {}}};
      for(double N : tailles_dataset){
         vector<int> dataset = creation_dataset<int>((size_t) N, SEED, type);
         mesures["tri_a_bulle"].push_back(mesure_temps_execution(tri_a_bulle<vector<int>::iterator>, dataset));
         mesures["tri_par_insertion"].push_back(mesure_temps_execution(tri_par_insertion<vector<int>::iterator>, dataset));
         mesures["tri_par_selection"].push_back(mesure_temps_execution(tri_par_selection<vector<int>::iterator>, dataset));
         mesures["sort"].push_back(mesure_temps_execution(sort<vector<int>::iterator>, dataset));
         mesures["stable_sort"].push_back(mesure_temps_execution(stable_sort<vector<int>::iterator>, dataset));
      }
      string nom_fichier = "../../rapport/csv/mesure_temps_de_calcul_" + nom_enum[type] + ".csv";
      exporter_csv<double>(nom_fichier, tailles_dataset, mesures);
   }

   return 0;
}

