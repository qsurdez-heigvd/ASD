/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : puzzle.h
 * @date : 09.03.2023
 * @content : corps de la classe puzzle
 */
#ifndef ASD2022_L2_RECURSIVITE_PUZZLE_H
#define ASD2022_L2_RECURSIVITE_PUZZLE_H

#include <array>
#include <vector>
#include <string>
#include "pieceOrientee.h"
#include "pieces.h"


class Puzzle {
public :

	Puzzle(std::size_t taille, const Pieces &liste);

	[[nodiscard]] bool estCompatible(size_t positionX, size_t positionY) const;

	static bool figureCompatible(const AttachementType &a, const AttachementType &b) ;

	static std::string creerSolution(const std::vector<std::vector<PieceOrientee>> &grilleSoluce);

	void trouveSolution(std::vector<std::string> &solutions,
							  size_t coordX = 0, size_t coordY = 0);

	static unsigned lisNombreIteration() { return nombreIteration;}


private:
	static unsigned nombreIteration;
	std::size_t tailleGrille;
	std::vector<std::vector<PieceOrientee>> grille;
	std::vector<std::string> solution;
	std::vector<PieceOrientee> piecesDispo;

};


#endif //ASD2022_L2_RECURSIVITE_PUZZLE_H
