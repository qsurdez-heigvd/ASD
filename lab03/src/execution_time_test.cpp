/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : execution_time_test.cpp
 * @date : 21.03.2023
 */
#include "execution_time.h"
#include "export_csv.h"
#include "tri_par_base.h"
#include "tri_rapide.h"
#include <vector>
#include <map>
#include <random>
#include "creation_dataset.h"

using namespace std;

const size_t NUMBER_OF_TESTS = 10;
const uint32_t SEED = 13;


int main() {

	map<string, vector<double>> measures{{"tri_par_base_1",  {}},
													 {"tri_par_base_2",  {}},
													 {"tri_par_base_4",  {}},
													 {"tri_par_base_8",  {}},
													 {"tri_par_base_16", {}},
													 {"tri_rapide",      {}}};
	const vector<unsigned> tailles_dataset = {10, 100, 1000, 5000, 10000, 50000,
															100000, 200000, 500000, 1000000};


	for (unsigned N: tailles_dataset) {
		vector<unsigned> dataset = creation_dataset<unsigned>(N, SEED);
		measures["tri_par_base_1"].push_back(
			measure_execution_time(tri_par_base<vector<unsigned>::iterator, 1u>,
										  dataset, NUMBER_OF_TESTS));
		measures["tri_par_base_2"].push_back(
			measure_execution_time(tri_par_base<vector<unsigned>::iterator, 2u>,
										  dataset, NUMBER_OF_TESTS));
		measures["tri_par_base_4"].push_back(
			measure_execution_time(tri_par_base<vector<unsigned>::iterator, 4u>,
										  dataset, NUMBER_OF_TESTS));
		measures["tri_par_base_8"].push_back(
			measure_execution_time(tri_par_base<vector<unsigned>::iterator, 8u>,
										  dataset, NUMBER_OF_TESTS));
		measures["tri_par_base_16"].push_back(
			measure_execution_time(tri_par_base<vector<unsigned>::iterator, 16u>,
										  dataset, NUMBER_OF_TESTS));
		measures["tri_rapide"].push_back(
			measure_execution_time(tri_rapide<vector<unsigned>::iterator>,
										  dataset, NUMBER_OF_TESTS));
		cout << N << endl;
	}

	string nom_fichier = "../../rapport/csv/mesure_temps_de_calcul.csv";
	export_csv<double>(nom_fichier, tailles_dataset, measures);

	return 0;

};
