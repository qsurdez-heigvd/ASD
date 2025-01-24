#ifndef ASD_2021_AVL_IMPL_H
#define ASD_2021_AVL_IMPL_H

#include <utility>
#include <algorithm>

template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {
}

template<typename Key>
avlTree<Key>::avlTree(avlTree<Key> const &other) {
   root = avl::nodeCopy(other.root);
}

template<typename Key>
avlTree<Key> &avlTree<Key>::operator=(avlTree<Key> const &other) {
   if (this == &other) return *this;
   avlTree<Key> tmp(other);
   std::swap(this->root, tmp.root);
   return *this;
}

template<typename Key>
avlTree<Key>::~avlTree() {
    if (root != nullptr){
        avl::clear(root);
    }
}

template<typename Key>
bool avlTree<Key>::contains(Key const &k) const noexcept {
   return (avl::find_in_subtree(root, k) != nullptr);
}

template<typename Key>
Key const &avlTree<Key>::min() const {
   return avl::findExtremum(root, avl::LEFT)->key;
}

template<typename Key>
Key const &avlTree<Key>::max() const {
   return avl::findExtremum(root, avl::RIGHT)->key;
}

template<typename Key>
void avlTree<Key>::erase_min() {
   erase(min());
}

template<typename Key>
void avlTree<Key>::erase_max() {
   erase(max());
}

template<typename Key>
void avlTree<Key>::erase(Key const &k) noexcept {
   avl::eraseNode(root, k);
}


template<typename Key>
void avlTree<Key>::insert(Key const &k) {
   avl::insert_in_subtree(root, k);
}

template<typename Key>
std::ostream &avlTree<Key>::show_indented(std::ostream &out) const {
   return avl::show_indented(root, out);
}

template<typename Key>
std::ostream &operator<<(std::ostream &out, avlTree<Key> const &tree) {
   return avl::treeToString(out, tree.root);
}

template<typename Key>
std::istream &operator>>(std::istream &in, avlTree<Key> &tree) {
return avl::treeFromString(in, tree.root);
}

template<typename Key>
[[nodiscard]] unsigned char avlTree<Key>::height() const noexcept {
   return root != nullptr ? root->height : 0;
}


#endif //ASD_2021_AVL_IMPL_H
