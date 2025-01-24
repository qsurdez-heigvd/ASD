#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"

namespace avl {
   /**
  * Function used to calculate the new height of a node
  * @tparam Key type of the key
  * @param node the node that needs an update in its height
  */
   template<typename Key>
   void updateHeight(Node<Key> *&node);

   /**
    * Function to know the value of balancing of a node
    * @tparam Key type of the key
    * @param node node of interest
    * @return value of balancing
    */
   template<typename Key>
   char computeBalance(Node<Key> *node);

   /**
   * @brief Function that will performe a right or left rotation on a given node
   * @tparam Key the type of the key
   * @param node the node on which we perform the rotation
   * @param s the side of the rotation either LEFT or RIGHT
   */
   template<typename Key>
   void rotation(Node<Key> *&node, Side direction);

   /**
     * Function that will perform a left rotation on a given node
     * @tparam Key type of the key
     * @param node node on which the rotation will be made
     */
   template<typename Key>
   void leftRotation(Node<Key> *&node);

   /**
    * Function that will performe a right rotation on a given node
    * @tparam Key type of the key
    * @param node node on which the rotation will be made
    */
   template<typename Key>
   void rightRotation(Node<Key> *&node);

   /**
    * Function that allows to represent a tree from a string format
    * @tparam Key type of the key
    * @param in stream from which originates the string
    * @param node node from which the tree must be created
    * @return stream given in parameter once the tree is made
    */
   template<typename Key>
   std::istream &treeFromString(std::istream &in, Node<Key> *&node);

   /**
    * Function that allows a tree to be represented in a string format
    * @tparam Key type of the key
    * @param out stream to write the string to
    * @param node node from which the string is created
    * @return stream given in parameter once the tree is written
    */
   template<typename Key>
   std::ostream &treeToString(std::ostream &out, Node<Key> const *node);

   /**
    * Function to free the memory occupied by a tree
    * beginning at a specific root
    * @tparam Key type of the key
    * @param root root of the tree to be destroyed
    */
   template<typename Key>
   void clear(Node<Key> *&root);

   /**
    * Function that will erase a specific value in the tree
    * @tparam Key type of the key
    * @param root root from which we search the value to erase
    * @param k value of the key to erase
    * @return the updated root
    */
   template<typename Key>
   Node<Key> *eraseNode(Node<Key> *&root, Key const &k);

   /**
    * Function to get access of the height of a specific node
    * @tparam Key type of the key
    * @param node node of interest
    * @return height of the node of interest
    */
   template<typename Key>
   unsigned char getHeight(Node<Key> *node);

   /**
    * Function used to restore balance of a given node
    * @tparam Key type of the key
    * @param node node on which the balancing is done
    */
   template<typename Key>
   void restoringBalance(Node<Key> *&node);

   /**
    * @brief Finds the extremum of a subtree either the minimum or the maximum
    * @tparam Key the type of the key
    * @param root the root of the subtree
    * @param s the side of the extremum, LEFT for the minimum, RIGHT for the maximum
    * @return the extremum of the subtree
    */
   template<typename Key>
   Node<Key> *findExtremum(Node<Key> *const &root, Side direction);


   template<typename Key>
   void insert_in_subtree(Node<Key> *&r, Key
   const &k) {
      if (r == nullptr) {
         r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
      } else if (k == r->key) {
         return;
      } else {
         Side s = k < r->key ? LEFT : RIGHT;
         insert_in_subtree(r
                              ->children[s], k);
      }
      restoringBalance(r);
   }

   template<typename Key>
   Node<Key> *find_in_subtree(Node<Key> *const node, Key const &k) noexcept {
      if (node == nullptr) return nullptr;
      Node<Key> *wanted_node;
      if (node->key == k) {
         wanted_node = node;
      } else if (k >= node->key) {
         wanted_node = find_in_subtree(node->right(), k);
      } else {
         wanted_node = find_in_subtree(node->left(), k);
      }
      return wanted_node;
   }

   template<typename Key>
   std::ostream &show_indented(Node<Key> *r,
                               std::ostream &out,
                               std::string before,
                               bool isright) {
      out << before;
      if (not r) {
         out << ".\n";
      } else {
         if (not before.empty()) {
            before[before.size() - 2] = ' ';
            if (isright) {
               before[before.size() - 3] = ' ';
            }
         }
         out << r->key << std::endl;
         if (r->children != Node<Key>::NO_CHILD) {
            for (Side s: {LEFT, RIGHT}) {
               show_indented(r->children[s], out, before + "|_ ", s);
            }
         }
      }
      return out;
   }

   template<typename Key>
   void updateHeight(Node<Key> *&node) {
      if (node != nullptr) {
         node->height = 1 + std::max(getHeight(node->left()), getHeight(node->right()));
      }
   }

   template<typename Key>
   Node<Key> *nodeCopy(Node<Key> *other) {
      if (other == nullptr) return nullptr;
      auto root = new Node<Key>{other->key, Node<Key>::NO_CHILD, 0};
      root->left() = nodeCopy(other->left());
      root->right() = nodeCopy(other->right());
      updateHeight(root);
      return root;
   }

   template<typename Key>
   char computeBalance(Node<Key> *node) {
      // assuming that heights have been updated before computeBalance function call
      if (node != nullptr) {
         return (char) (getHeight(node->left()) - getHeight(node->right()));
      }
      return 0;
   }


   template<typename Key>
   void rotation(Node<Key> *&node, Side direction) {

      if (node == nullptr) {
         return;
      }
      Node<Key> *tmp = node->children[!direction];
      node->children[!direction] = tmp->children[direction];
      tmp->children[direction] = node;
      node = tmp;
      updateHeight(node->children[direction]);
      updateHeight(node);
   }


   template<typename Key>
   void leftRotation(Node<Key> *&node) {
      rotation(node, LEFT);

   }

   template<typename Key>
   void rightRotation(Node<Key> *&node) {
      rotation(node, RIGHT);

   }

   template<typename Key>
   void restoringBalance(Node<Key> *&node) {
      if (node == nullptr) {
         return;
      }
      if (computeBalance(node) < -1) { // leans right
         if (computeBalance(node->right()) > 0) { // RL
            rightRotation(node->right());
         }
         leftRotation(node);
      } else if (computeBalance(node) > 1) { // leans left
         if (computeBalance(node->left()) < 0) { // LR
            leftRotation(node->left());
         }
         rightRotation(node);
      } else {
         updateHeight(node);
      }
   }

   template<typename Key>
   unsigned char getHeight(Node<Key> *node) {
      return node ? node->height : 0;
   }

   template<typename Key>
   Node<Key> *eraseNode(Node<Key> *&root, Key const &k) {
      if (root != nullptr) {
         if (k < root->key) {
            eraseNode(root->left(), k);
         } else if (k > root->key) {
            eraseNode(root->right(), k);
         } else {
            if (root->left() == nullptr || root->right() == nullptr) {
               Node<Key> *temp = root->left() ? root->left() : root->right();
               if (temp == nullptr) {
                  temp = root;
                  root = nullptr;
               } else {
                  auto *new_r = new Node<Key>{temp->key, temp->left(), temp->right(),
                                             temp->height};
                  delete (root);
                  root = std::move(new_r);
                  delete (temp);
               }
            } else {
               // here we choose to replace the root by
               // the max found in the left subtree
               Node<Key> *temp = findExtremum(root->left(), RIGHT);
               auto *new_r = new Node<Key>{temp->key, root->left(), root->right(),
                                           temp->height};
               delete (root);
               root = new_r;
               root->left() = eraseNode(root->left(), temp->key);
               delete (temp);
            }
         }
      }
      updateHeight(root);
      restoringBalance(root);
      return root;
   }

   template<typename Key>
   std::ostream &treeToString(std::ostream &out, Node<Key> const *node) {
      if (node == nullptr) {
         out << ".";
      } else {
         out << node->key;
         out << "(";
         node->left() != nullptr ? treeToString(out, node->left()) : out << ".";
         out << ",";
         node->right() != nullptr ? treeToString(out, node->right()) : out << ".";
         out << ")";
      }
      return out;
   }

   template<typename Key>
   std::istream &treeFromString(std::istream &in, Node<Key> *&node) {
      if (std::isdigit(in.peek())) {
         Key key;
         in >> key;
         insert_in_subtree(node, key);
         in.ignore();
         if (!in.fail()) {
            treeFromString(in, node->left());
            in.ignore();
            treeFromString(in, node->right());
         }
      }
      restoringBalance(node);
      in.ignore();
      return in;
   }

   template<typename Key>
   void clear(Node<Key> *&root) {
      if (root != nullptr) {
         if (root->left() != nullptr)
            clear(root->left());
         if (root->right() != nullptr)
            clear(root->right());
      }
      delete (root);
      root = nullptr;
   }

   template<typename Key>
   Node<Key> *findExtremum(Node<Key> *const &root, Side direction) {
      if (root == nullptr) {
         throw std::out_of_range("Tree is empty");
      }
      // doit descendre dans le noeud gauche jusqu'à ce que le prochain noeud soit null
      if (root->children[direction] != nullptr) {
         return findExtremum(root->children[direction], direction);
      } else {
         return root;
      }
   }


}


#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
