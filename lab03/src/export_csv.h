/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : export_csv.h
 * @date : 21.03.2023
 */
#ifndef ASD_LABOS_2021_EXPORT_CSV_H
#define ASD_LABOS_2021_EXPORT_CSV_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

/**
* creates a csv containing the values of the sorted dataset
 * @tparam T: generic type of the dataset content to sort
 * @param path_filename: path name where to store the csv file
 * @param sample_size: size of the dataset to be sorted
 * @param measures: measures for a certain parameter for a certain sort
 */
template<typename T>
void export_csv(std::string const &path_filename,
					 const std::vector<unsigned> &sample_size,
					 const std::map<std::string, std::vector<T>> &measures) {

	std::ofstream out(path_filename);

	if (not out.is_open()) {
		std::cerr << "Could not open file in writing mode" << std::endl;
		return;
	}

	out << "N";
	for (const auto &[key, value]: measures) {
		out << "," << key;
	}
	out << std::endl;
	for (size_t i = 0; i < sample_size.size(); ++i) {
		out << sample_size.at(i);
		for (const auto &[key, value]: measures) {
			out << "," << value.at(i);
		}
		out << std::endl;
	}

	out << std::endl;

	out.close();
}

#endif //ASD_LABOS_2021_EXPORT_CSV_H
