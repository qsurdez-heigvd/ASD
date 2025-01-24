/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : pieceOrientee.h
 * @date : 09.03.2023
 * @content : corps de la classe pieceOrientee
 */
#ifndef ASD2022_L2_RECURSIVITE_PIECEORIENTEE_H
#define ASD2022_L2_RECURSIVITE_PIECEORIENTEE_H

#include "pieces.h"
#include <array>

class PieceOrientee {
public:
   PieceOrientee(Piece figurines_, unsigned int id_, char orientation_ = 'a') : orientation(orientation_),
   figurines(figurines_), id(id_){};
   PieceOrientee() : orientation('a'), figurines({NONE, NONE, NONE, NONE}), id(0) {};

   void rotation(char orientation_);
   [[nodiscard]] char getOrientation() const {return orientation;}
   [[nodiscard]] unsigned int getId() const {return id;}
   [[nodiscard]] AttachementType getFigurines(std::size_t direction) const {return figurines.at(direction);}

private:
   char orientation;
   Piece figurines;
   unsigned int id;
};


#endif //ASD2022_L2_RECURSIVITE_PIECEORIENTEE_H
