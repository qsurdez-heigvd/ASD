/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2023-L3-Tris
 * @file : creation_dataset.h
 * @date : 03.04.2023
 */
#ifndef ASD_L3_TRIS_CREATION_DATASET_H
#define ASD_L3_TRIS_CREATION_DATASET_H

template<typename T>
std::vector<T> creation_dataset(size_t N, uint32_t seed) {

	std::vector<T> dataset(N);
	std::minstd_rand0 generator(seed);
	std::iota(dataset.begin(), dataset.end(), 0);
	shuffle(dataset.begin(), dataset.end(), generator);

	return dataset;
}

#endif //ASD_L3_TRIS_CREATION_DATASET_H
