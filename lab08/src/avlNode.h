#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

   enum Side {
      LEFT = 0, RIGHT = 1
   };

   template<typename Key>
   struct Node {
      Key const key;
      std::array<Node*, 2> children;
      unsigned char height;

      inline Node*& left() noexcept { return children[LEFT]; }
      inline Node* const& left() const noexcept { return children[LEFT]; }
      inline Node*& right() noexcept { return children[RIGHT]; }
      inline Node* const& right() const noexcept { return children[RIGHT]; }

      static constexpr std::array<Node*, 2> NO_CHILD{nullptr, nullptr};
   };

   template<typename Key>
   void insert_in_subtree(Node<Key>*& r,
                          Key const& k);

   template<typename Key>
   std::ostream&  show_indented(Node<Key> *r,
                                std::ostream &out = std::cout,
                                std::string before = "",
                                bool isright = false);
}

#include "avlNodeImplementation.h"

#endif //ASD_LABS_2021_AVLNODE_H