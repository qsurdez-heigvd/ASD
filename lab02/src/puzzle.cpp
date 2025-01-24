/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : puzzle.cpp
 * @date : 09.03.2023
 * @content : définitions des méthodes de la classe puzzle
 */
#include "puzzle.h"
#include "figuresCompatibles.h"
#include <iostream>

using namespace std;

unsigned Puzzle::nombreIteration = 0;

/**
 * vérifie si la pièce peut être posée à la position choisie
 * @param positionX: position x de la grille à laquelle on veut poser la pièce
 * @param positionY: position y de la grille à laquelle on veut poser la pièce
 * @return: bool qui vaut 1 si la pièce est compatible avec la position choisie
 */
bool Puzzle::estCompatible(size_t positionX, size_t positionY) const{

	if (positionX + 1 < tailleGrille) {
		// tester (i+1, j) celle en bas
		if (!figureCompatible(grille.at(positionX + 1).at(positionY).getFigurines(0),
									 grille.at(positionX).at(positionY).getFigurines(2))) {
			return false;
		}
	}
	if (positionY + 1 < tailleGrille) {
		// tester (i, j+1) celle à droite
		if (!figureCompatible(grille.at(positionX).at(positionY + 1).getFigurines(3),
									 grille.at(positionX).at(positionY).getFigurines(1))) {
			return false;
		}
	}
	if (positionX > 0) {
		// tester (i-1, j) celle en haut
		if (!figureCompatible(grille.at(positionX - 1).at(positionY).getFigurines(2),
									 grille.at(positionX).at(positionY).getFigurines(0))) {
			return false;
		}
	}
	if (positionY > 0) {
		// tester (i, j-1) celle à gauche
		if (!figureCompatible(grille.at(positionX).at(positionY - 1).getFigurines(1),
									 grille.at(positionX).at(positionY).getFigurines(3))) {
			return false;
		}
	}

	return true;
}

/**
 * Constructeur qui crée un puzzle rempli de pièces None et il initialse la liste de pièces disonibles et leur id de 1
 * à taille (dans l'ordre)
 * @param taille: taille du puzzle (taillextaille)
 * @param liste: vector de PieceOrientee contenant la liste de pièces disponibles pour compléter le puzzle
 */
Puzzle::Puzzle(std::size_t taille, const Pieces &liste) {
   if (taille * taille != liste.size())
      cerr << "Le nombre de pièces n'est pas égal aux dimensions du puzzle.";
	tailleGrille = taille;
	grille = vector < vector < PieceOrientee >> (tailleGrille, vector<PieceOrientee>
		(tailleGrille, PieceOrientee()));


	for (auto i = liste.begin(); i != liste.end(); i++) {
		PieceOrientee piece = PieceOrientee(*i, unsigned((i + 1) - liste.begin()));
		piecesDispo.push_back(piece);
	}

}

/**
 * vérifie si deux figures sont compatibles
 * @param figure1: AttachementType désignant la première figure
 * @param figure2: AttachementType désignant la deuxième figure
 * @return: bool qui vaut 1 si les deux figures sont compatibles
 */
bool Puzzle::figureCompatible(const AttachementType &figure1, const AttachementType &figure2) {
	if (figure1 == ARROSOIR_INVERSE or figure2 == ARROSOIR_INVERSE)
		return false;
	if (figure1 == NONE or figure2 == NONE)
		return true;
	if (COMPATIBLE.at(figure1) == figure2)
		return true;
	return false;
}

/**
 * crée la solution au format compatible avec le site pour vérifier les solutions
 * @param grilleSoluce: grille contenant une solution au puzzle
 * @return: string contenant la solution au format souhaité
 */
string Puzzle::creerSolution(const vector<vector<PieceOrientee>> &grilleSoluce) {
	string solution;
	for (auto &vecteur: grilleSoluce) {
		for (auto &piece: vecteur) {
			solution.append(to_string(piece.getId()) + piece.getOrientation() + " ");
		}
	}
	return solution;
}

/**
 * fonction récursive qui permet de trouver toutes les solutions possibles du puzzle
 * @param solutions: vecteur de string qui contiendra toutes les solutions
 * @param coordX: coordonnée x de la pièce à tester
 * @param coordY: coordonnée y de la pièce à tester
 */
void Puzzle::trouveSolution(vector <std::string> &solutions,
									 size_t
									 coordX, size_t coordY) {
	++nombreIteration;
	if (piecesDispo.empty()) {
		solutions.push_back(creerSolution(grille));
		return;
	}
// nouvelles coordonnées par rapport à la grille,
// on saute une ligne si on est à la fin de la ligne
	size_t newCoordX = (coordY >= tailleGrille - 1) ? coordX + 1 : coordX;
	size_t newCoordY = (coordY + 1) % tailleGrille;
//pour chaque pièce disponible
	for (auto piece = piecesDispo.begin(); piece != piecesDispo.end();
		  ++piece) {

		// on la place dans la grille à la position que l'on cherche
		grille.at(coordX).at(coordY) = *piece;

		// on sauvegarde la pièce
		// on enlève la pièce de la liste des pièces disponibles
		PieceOrientee piece_a_enlever = *piece;
		piecesDispo.erase(piece);

		// pour chaque orientation possible
		for (char orientation = 'a'; orientation <= 'd'; orientation++) {

			// on la tourne à l'orientation que l'on cherche
			grille.at(coordX).at(coordY).rotation(orientation);

			// si la pièce est compatible avec les pièces adjacentes
			if (estCompatible(coordX, coordY)) {

				// on appelle la fonction récursive avec la position suivante et la
				// nouvelle liste de pièces disponibles
				trouveSolution(solutions, newCoordX, newCoordY);


			}

		}
		// on remet la pièce dans la liste des pièces disponibles
		piecesDispo.insert(piece, piece_a_enlever);
	}
	// on enlève la pièce qu'on avait posée
	grille.at(coordX).at(coordY) = PieceOrientee();
}

