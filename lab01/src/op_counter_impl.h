
/*
  -----------------------------------------------------------------------------------
  Nom du fichier : op_counter_impl.h
  Auteur(s)      : Q. Surdez, REDACTED, REDACTED
  Date creation  : 07.03.23 15:32
  -----------------------------------------------------------------------------------
 */

#ifndef ASD2022_L1_COMPLEXITE_OP_COUNTER_IMPL_H
#define ASD2022_L1_COMPLEXITE_OP_COUNTER_IMPL_H
#include "op_counter.h"

template <typename T>
OpCounter<T>::OpCounter(const OpCounter<T>& opCounter) : valeur(opCounter.valeur){
   ++compteur_aff;
}

template <typename T>
bool OpCounter<T>::operator == (const OpCounter<T>& rhs) const {
   ++OpCounter::compteur_op;
   return rhs.valeur == this->valeur;
}

template <typename T>
OpCounter<T> &OpCounter<T>::operator=(const OpCounter<T> &rhs) {
   ++OpCounter::compteur_aff;
   this->valeur = rhs.valeur;
   return *this;
}

template <typename T>
OpCounter<T> &OpCounter<T>::operator=(T val) {
   ++OpCounter::compteur_aff;
   this->valeur = val;
   return *this;
}

template <typename T>
bool OpCounter<T>::operator<(const OpCounter<T> &rhs) const {
   ++OpCounter::compteur_op;
   return (this->valeur < rhs.valeur);
}

template <typename T>
OpCounter<T> &OpCounter<T>::operator+=(const OpCounter<T> &rhs) {
   ++OpCounter::compteur_aff;
   ++OpCounter::compteur_op;
   this->valeur += rhs.valeur;
   return *this;
}

template <typename T>
std::ostream& operator<< (std::ostream& lhs, OpCounter<T>& rhs){
   lhs << "Valeur: " << rhs.valeur << std::endl;
   lhs << "Nombre d'operations: " << rhs.compteur_op << std::endl;
   lhs << "Nombre d'affectations: " << rhs.compteur_aff << std::endl;
   return lhs;
}

template <typename T>
OpCounter<T> OpCounter<T>:: operator + (const OpCounter<T> &rhs) {
   OpCounter res = *this;
   res += rhs;
   return res;
}

template <typename T>
OpCounter<T> OpCounter<T>::operator*(const double rhs) const {
   OpCounter<T> result{};
   result.valeur = (T)(this->valeur * rhs);
   return result;
}



#endif //ASD2022_L1_COMPLEXITE_OP_COUNTER_IMPL_H
