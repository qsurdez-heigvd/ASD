#ifndef LISTE_H
#define LISTE_H

#include "LSIterator.h"
#include <utility> // std::swap;
#include <forward_list>
#include <cassert>

template<typename T>
class ListeSimple {
public:
   using value_type = T;
   using reference = T &;
   using const_reference = T const &;

private:
   struct Maillon {
      value_type valeur;
      Maillon *suivant;
   };

   Maillon avant_premier;

public:
   using iterator = LSIterator<value_type>;
   friend iterator;

   using const_iterator = LSConstIterator<value_type>;
   friend const_iterator;

   /**
    * renvoie un itérateur constant sur le premier maillon de la liste
    */
   const_iterator cbegin() const noexcept {
      return const_iterator(avant_premier.suivant);
   }

   /**
    * renvoie un itérateur sur le premier maillon de la liste
    */
   iterator begin() noexcept { return iterator(avant_premier.suivant); }

   /**
    * renvoie un itérateur constanr sur le premier maillon de la liste
    */
   const_iterator begin() const noexcept { return cbegin(); }

   /**
    * constructeur par défaut
    */
   ListeSimple() : avant_premier{value_type{}, nullptr} {}

   /**
    * destructeur
    */
   ~ListeSimple() {
      while (!empty()) {
         pop_front();
      }
   }

   /**
    * constructeur de copie
    * @param autre liste simple qu'on veut copier
    */
   ListeSimple(const ListeSimple<T>& autre) : avant_premier{T{}, nullptr} {
      if (this == &autre) return;

      iterator iterateur_courant = before_begin();
      for (const_iterator i = autre.cbegin(); i != autre.cend(); i++) {
         insert_after(iterateur_courant, *i);
         iterateur_courant++;
      }
   }

   /**
    * opérateur d'affectation
    * @param autre liste simple qu'on veut copier
    * @return liste affectée
    */
   ListeSimple &operator=(const ListeSimple<T> &autre) {
      if (this == &autre) {
         return *this;
      }
      auto tmp(autre);
      swap(tmp);
      return *this;

   }

   /**
    * renvoie un itérateur constant sur le maillon suivant le dernier de la liste
    */
   const_iterator cend() const noexcept {
      return const_iterator(nullptr);
   }

   /**
    * renvoie un itérateur constant sur le maillon suivant le dernier de la liste
    */
   const_iterator end() const noexcept { return cend(); }

   /**
    * renvoie un itérateur sur le maillon suivant le dernier de la liste
    */
   iterator end() noexcept {
      return iterator(nullptr);
   }

   /**
    * renvoie un itérateur sur le maillon précédent le premier de la liste
    */
   iterator before_begin() noexcept {
      return iterator(&avant_premier);
   }

   /**
    * renvoie un itérateur constant sur le maillon précédent le premier de la liste
    */
   const_iterator before_begin() const noexcept {
      return cbefore_begin();
   }

   /**
    * renvoie un itérateur constant sur le maillon précédent le premier de la liste
    */
   const_iterator cbefore_begin() const noexcept {
      return const_iterator(&avant_premier);
   }

   /**
    * renvoie un bool qui vaut true si la liste est vide, false sinon
    */
   [[nodiscard]] bool empty() const noexcept {
      return begin() == nullptr;
   }

   /**
    * renvoie une référence sur un itérateur sur le premier maillon de la liste
    */
   reference front() {
      if (empty()) throw std::length_error(__func__);

      return *begin();
   }

   /**
    * renvoie une référence constante sur un itérateur sur le premier maillon de la
    * liste
    */
   const_reference front() const noexcept {
      if (empty()) throw std::length_error(__func__);

      return *begin();
   }

   /**
    * insert un maillon après une position donnée
    * @param pos position après lquelle le maillon va être ajouté
    * @param value valeur contenue dans le nouveau maillon
    */
   void insert_after(iterator pos, const T& value) const {
      if (pos == nullptr) throw std::out_of_range(__func__);
      auto nouveau_maillon = new Maillon{value, pos.m->suivant};
      if (nouveau_maillon == nullptr) {
         throw std::bad_alloc();
      }
      pos.m->suivant = nouveau_maillon;
   }

   /**
    * efface à la position passée en paramètre + 1
    * @param position
    * @return
    */
   iterator erase_after(iterator position) {
      if (position.m->suivant == nullptr)
         throw std::out_of_range(__func__);
      if (position == nullptr)
         throw std::out_of_range(__func__);
      auto tmp = position.m->suivant;
      position.m->suivant = tmp->suivant;
      delete (tmp);
      return ++position;
   }

   /**
    * insert les maillons contenus dans l'intervalle [first, last[ après la
    * position pos
    * @param pos position après laquelle coller les nouveaux éléments
    * @param first iterateur sur le premier maillon de l'intervalle
    * @param last iterateur sur le dernier maillon de l'intervalle
    */
   void splice_after(iterator pos, iterator first, iterator last) {
      if (pos == first or pos == last or first == last) {
         return;
      }

      Maillon* tmp = pos.m->suivant;
      pos.m->suivant = first.m->suivant;
      first.m->suivant = last.m->suivant;
      last.m->suivant = tmp;
   }

   /**
    * met en première position ce qui est passée en paramètre
    * @param value valeur à insérer
    */
   void push_front(const_reference value) {
      insert_after(before_begin(), value);
   }

   /**
    * détruit le maillon en première position
    */
   void pop_front() {
      if (avant_premier.suivant == nullptr) {
         throw std::out_of_range(__func__);
      }
      erase_after(before_begin());
   }

   /**
    * fonction permettant d'interchanger deux éléments
    * @param other élément avec lequel interchanger l'élément propre
    */
   void swap(ListeSimple<value_type> &other) noexcept {
      if (before_begin() == other.before_begin()) return;

      using std::swap;
      swap(avant_premier, other.avant_premier);
   }

/**
 * tri par sélection
 */
   void sort(){
      if(empty()) return;

      iterator j = before_begin();

      auto iMin = j;
      auto i = j;
      while (next(j) != end()) {
         iMin = j;
         i = next(j);
         while (next(i) != end()) {
            if (*next(i) < *next(iMin)) {
               iMin = i;
            }
            ++i;
         }
         if (iMin != j) {
            splice_after(j, iMin, next(iMin));
         }
         ++j;
      }
   }
};

#endif //LISTE_H
