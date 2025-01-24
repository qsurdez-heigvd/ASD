#include <iostream>
#include <vector>
#include "avlTree.h"

using namespace std;

avlTree<int> make_tree_from_vector(const vector<int> &v) {
   avlTree<int> tree;
   for (int i: v) {
      tree.insert(i);
   }
   return tree;
}

int main() {

   avlTree<int> tree = make_tree_from_vector({14, 8, 20, 3, 10, 17, 23, 2, 6, 13, 21, 5});

   tree.show_indented(cout);

   tree.erase(14);
   tree.show_indented(cout);

   cout << endl;

   cout << tree << endl;

   cout << "Bonnes vacances! :)" << endl;

}
