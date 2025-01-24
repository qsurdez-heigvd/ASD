/**
 * @authors : Q.Surdez, REDACTED, REDACTED
 * @project : ASD2022-L2-Recursivite
 * @file : figuresCompatibles
 * @date : 09.03.2023
 * @content : définition d'une map contenant les compatibilités entre figures
 */
#ifndef ASD2022_L2_RECURSIVITE_FIGURESCOMPATIBLES_H
#define ASD2022_L2_RECURSIVITE_FIGURESCOMPATIBLES_H

#include "pieces.h"
#include <map>

const std::map<AttachementType, AttachementType> COMPATIBLE {
   {DAME_HAUT, DAME_BAS},
   {DAME_BAS, DAME_HAUT},
   {FILLE_HAUT, FILLE_BAS},
   {FILLE_BAS, FILLE_HAUT},
   {ARROSOIR_GAUCHE, ARROSOIR_DROIT},
   {ARROSOIR_DROIT, ARROSOIR_GAUCHE},
   {GATEAU_GAUCHE, GATEAU_DROIT},
   {GATEAU_DROIT, GATEAU_GAUCHE},
   {ARROSOIR_INVERSE, ARROSOIR_INVERSE}
};

#endif //ASD2022_L2_RECURSIVITE_FIGURESCOMPATIBLES_H
