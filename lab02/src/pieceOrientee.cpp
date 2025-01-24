/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : pieceOrientee.cpp
 * @date : 09.03.2023
 * @content : définitions des méthodes de la classe pieceOrientee
 */
#include "pieceOrientee.h"
#include <algorithm>

using namespace std;

/**
 * Fonction qui applique une rotation à une pièce
 * @param orientation_: char indiquant le côté de la pièce qu'on veut mettre en haut (a,b,c,d)
 */
void PieceOrientee::rotation(char orientation_) {

	unsigned cranDecalage = unsigned(abs(orientation_ - this->orientation));
	this->orientation = orientation_;
	rotate(this->figurines.begin(), this->figurines.begin() + cranDecalage,
			 this->figurines.end());

}
