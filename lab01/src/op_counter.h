
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : op_counter.h
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:31
  -----------------------------------------------------------------------------------
 */

#ifndef ASD2022_L1_COMPLEXITE_OP_COUNTER_H
#define ASD2022_L1_COMPLEXITE_OP_COUNTER_H

#include <iostream>

using ull = unsigned long long;

template <typename T> class OpCounter;

template <typename T>
std::ostream& operator<< (std::ostream& lhs, OpCounter<T>& rhs);



template <typename T>
class OpCounter {
public:
   explicit OpCounter(T _valeur = 0) : valeur(_valeur) {};
   OpCounter(const OpCounter& opCounter);

   // operateurs d'affectation
   OpCounter<T>& operator = (const OpCounter<T>& rhs);
   OpCounter<T>& operator = (T val);

   // operateurs de comparaisons
   bool operator == (const OpCounter<T>& rhs) const;
   inline bool operator != (const OpCounter<T>& rhs) const {return !(this == rhs);};

   bool operator < (const OpCounter<T>& rhs) const;
   inline bool operator <= (const OpCounter<T>& rhs) const {return (this < rhs or this == rhs);};
   inline bool operator > (const OpCounter<T>& rhs) const {return !(this <= rhs);};
   inline bool operator >= (const OpCounter<T>& rhs) const {return !(this < rhs);};

   OpCounter& operator += (const OpCounter<T>& rhs);
   OpCounter operator + (const OpCounter<T> &rhs);

   // fonctions outils
   friend std::ostream& operator<< <>(std::ostream& lhs, OpCounter<T>& rhs);
   OpCounter operator* (const double rhs) const;

   static ull acces_aff() {return compteur_aff;};
   static ull acces_op() {return compteur_op;};
   static void reset_aff() {compteur_aff = 0;};
   static void reset_op() {compteur_op = 0;};
private:
   inline static ull compteur_aff = 0;
   inline static ull compteur_op = 0;
   T valeur;

};

#include "op_counter_impl.h"

#endif //ASD2022_L1_COMPLEXITE_OP_COUNTER_H
