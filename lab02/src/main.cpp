/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : main.cpp
 * @date : 09.03.2023
 * @content : programme main dans lequel on crée un puzzle puis trouve toutes ses solutions avec notre fonction
 * récursive, tout en comptant son nombre d'appels
 */
#include <iostream>
#include "pieceOrientee.h"
#include "puzzle.h"

using namespace std;

const unsigned TAILLE_COTE = 3;

int main() {

	Puzzle puzzle(TAILLE_COTE, PIECES);
	vector<string> solutions;
	puzzle.trouveSolution(solutions);
	cout << "Nombre d'appels a la fonction recursive : "
		  << Puzzle::lisNombreIteration()
		  << endl;
	cout << "Nombre de solutions : " << solutions.size() << endl;
	cout << "Liste des solutions : " << endl;
	for (const auto &solution: solutions) {
		std::cout << solution << std::endl;
	}

}