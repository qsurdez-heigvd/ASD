#ifndef PILE_IMPL_H
#define PILE_IMPL_H

#include <stdexcept> // std::out_of_range
#include "pile.h"

// AJOUTEZ VOTRE CODE ICI ...

template<typename T>
Pile<T>::Pile(size_t n) :taille(0), capacite(n), data(nullptr) {
   data = (n) ? (T *) ::operator new(n) : data;
}

template<typename T>
Pile<T>::~Pile() {
   for (size_t i = 0; i < taille; ++i)
      (data + i)->~T();
   ::operator delete(data);
   taille = 0;
}

template<typename T>
bool Pile<T>::full() const noexcept {
   return taille >= capacite;
}

template<typename T>
bool Pile<T>::empty() const noexcept {
   return taille == 0;
}

template<typename T>
void Pile<T>::push(T e) {
   if (!full()) {
      data[taille] = std::move(e);
      taille++;
   } else {
      throw std::out_of_range(__func__);
   }
}

template<typename T>
void Pile<T>::pop() {
   if (!empty()) {
      (data + taille - 1)->~T();
      taille--;
   } else {
      throw std::out_of_range(__func__);
   }
}

template<typename T>
const T &Pile<T>::top() const {
   if (!empty()) {
      return data[taille - 1];
   } else {
      throw std::out_of_range(__func__);
   }
}

template<typename T>
Pile<T>::Pile(const Pile &other) : taille(other.taille), capacite(other.capacite) {
   data = (T *) ::operator new(capacite);
   std::copy(other.data, other.data + other.taille, data);
}

template<typename T>
void Pile<T>::swap(Pile &other) noexcept {
   Pile<T> tmp = *this;
   *this = other;
   other = tmp;
}

template<typename T>
Pile<T> &Pile<T>::operator=(const Pile<T> &other) {
   if (this == &other) return *this;
   Pile<T> tmp{other};
   if (other.taille <= capacite) {
      swap(tmp);
   } else {
      for (size_t i = 0; i < taille; ++i)
         (data + i)->~T();
      this->data = tmp.data;
      this->taille = tmp.taille;
      this->capacite = tmp.capacite;
   }
   return *this;
}

// ... FIN DE VOTRE CODE

#endif
