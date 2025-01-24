#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream
// Ajoutez si nécessaire d'autres inclusions de librairies
#include <cassert>

template<class T>
class ArrayDeque {
public:
   using value_type = T;
   using reference = T &;
   using const_reference = const T &;
   using pointer = T *;
   using size_type = std::size_t;

   explicit ArrayDeque(size_type _capacite = 0) : debut(0),
                                                  taille(0),
                                                  capacite(_capacite),
                                                  buffer(nullptr) {
      if (capacite)
         buffer = reinterpret_cast<pointer> (
            ::operator new(capacite * sizeof(value_type)));
   }

   // Placez ici les méthodes publiques nécessaires pour passer le codecheck
   ~ArrayDeque() {
      for (size_type i = 0; i < taille; ++i)
         (buffer + i_physique(i))->~value_type();
      ::operator delete(buffer);
   }

   ArrayDeque(const ArrayDeque<value_type> &autre) : ArrayDeque(autre.capacite) {
      debut = autre.debut;
      for (; taille < autre.taille; ++taille)
         new(buffer + i_physique(taille)) value_type(autre.at(taille));
   }

   void push_back(const_reference e) {
      if (full()) {
         reallocate(nouvelle_capacite());
      }
      new(buffer + i_physique(taille)) value_type{e};
      ++taille;
   }

   void push_front(const_reference e) {

      if (full()) {
         reallocate(nouvelle_capacite());
      }
      size_type avant = i_physique(
         capacite - 1); // La construction est bonne et c'est debut qui pose prob
      new(buffer + avant) value_type{e};
      debut = avant;
      ++taille;

   }

   void pop_back() {
      at(taille - 1).~value_type();
      --taille;
   }

   void pop_front() {
      at(0).~value_type();
      --taille;
      debut = i_physique(1);
   }

   size_type capacity() const {
      return capacite;
   }

   size_type size() const {
      return taille;
   }

   bool empty() const {
      return taille == 0;
   }

   bool full() const {
      return taille == capacite;
   }

   reference front() const {
      return at(0);
   }

   reference back() const {
      return at(taille - 1);
   }

   void swap(ArrayDeque<value_type> &autre) noexcept {
      using std::swap;
      swap(autre.buffer, this->buffer);
      swap(autre.debut, this->debut);
      swap(autre.taille, this->taille);
      swap(autre.capacite, this->capacite);
   }

   void shrink_to_fit() {
      reallocate(taille);
   }

   reference operator[](size_type e) const {
      return buffer[i_physique(e)];
   }

   ArrayDeque<value_type> &operator=(const ArrayDeque<value_type> &autre) {
      ArrayDeque<value_type> tmp{autre};
      swap(tmp);
      return *this;
   }


private:
   pointer buffer;
   size_type capacite;
   size_type debut;
   size_type taille;

   // Placez ici les méthodes privées qui permettent de rendre votre code plus clair
   size_type i_physique(size_type i_logique) const {
      return (debut + i_logique + capacite) % capacite;
   }

   size_type nouvelle_capacite() const {
      if (capacite == 0)
         return 1;
      else
         return 2 * capacite;
   }

   void reallocate(size_t nouvelle_capacite) {
      ArrayDeque<value_type> tmp(nouvelle_capacite);

      for (size_type i = 0; i < taille; ++i) {
         new(tmp.buffer + i) value_type(std::move(at(i)));
         tmp.taille++;
      }

      swap(tmp);
   }

   reference at(size_type i) const {
      return operator[](i);
   }

};

template<typename value_type>
inline
std::ostream &operator<<(std::ostream &s,
                         const ArrayDeque<value_type> &v) {
   s << "(" << v.size() << "/" << v.capacity() << ") : ";
   if (not v.empty())
      s << v.front() << " -> " << v.back() << " : ";
   s << "[";
   for (int i = 0; i < v.size(); ++i) {
      s << v[i];
      if (i != v.size() - 1)
         s << ", ";
   }
   s << "]";
   return s;
}


#endif /* ArrayDeque_hpp */
