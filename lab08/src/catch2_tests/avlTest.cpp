#define CATCH_CONFIG_FAST_COMPILE

#include "catch_amalgamated.hpp"
#include "../avlTree.h"

#include <sstream>
#include <string>

using namespace std;

avlTree<int> make_easy_test_tree() { // order of insertion requires AVL no balancing
   avlTree<int> tree;
   for (int i: {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
      tree.insert(i);
   return tree;
}

avlTree<int> make_tree_from_vector(const vector<int> &v) {
   avlTree<int> tree;
   for (int i: v) {
      tree.insert(i);
   }
   return tree;
}

TEST_CASE("default constructor", "[avlTree]") {

   SECTION("Construction of an empty tree") {
      avlTree<int> tree;

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }
}

TEST_CASE("copy constructor", "[avlTree]") {

   SECTION("Copy an empty tree") {
      avlTree<int> tree;
      avlTree<int> tree2(tree);

      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }

   SECTION("Copy a non empty tree") {
      avlTree<int> tree = make_easy_test_tree();
      avlTree<int> tree2(tree);

      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }

   SECTION("Copy a one element tree") {
      avlTree<int> tree;
      tree.insert(1);
      avlTree<int> tree2(tree);

      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }
}

TEST_CASE("destructor", "[avlTree]") {

   SECTION("Destroy a non empty tree") {
      avlTree<int> tree = make_easy_test_tree();
      tree.~avlTree();
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }

   SECTION("Destroy an empty tree") {
      avlTree<int> tree;
      tree.~avlTree();
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }

   SECTION("Destroy a non empty dynamically allocated tree") {
      auto *tree = new avlTree<int>;
      *tree = make_easy_test_tree();
      tree->~avlTree();
      ostringstream oss;
      tree->show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }
}

TEST_CASE("insert", "[avlTree]") {

   SECTION("Insert into empty tree") {
      avlTree<int> tree;
      tree.insert(42);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "42\n");
   }

   SECTION("Insert smaller to the left") {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(2);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ 2\n"
                           "|_ .\n");
   }

   SECTION("Insert larger to the right") {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(4);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ .\n"
                           "|_ 4\n");
   }

   SECTION("Insert twice has no effect") {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(4);
      tree.insert(4);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ .\n"
                           "|_ 4\n");
   }

   SECTION("Easy tree") {
      avlTree<int> tree = make_easy_test_tree();

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "6\n"
                           "|_ 3\n"
                           "|  |_ 2\n"
                           "|  |  |_ 1\n"
                           "|  |  |_ .\n"
                           "|  |_ 4\n"
                           "|     |_ .\n"
                           "|     |_ 5\n"
                           "|_ 9\n"
                           "   |_ 7\n"
                           "   |  |_ .\n"
                           "   |  |_ 8\n"
                           "   |_ 10\n");
   }

   SECTION("Right right case imbalance") {
      avlTree<int> tree;

      tree.insert(3);
      tree.insert(2);
      tree.insert(1);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "2\n"
                           "|_ 1\n"
                           "|_ 3\n");
   }

   SECTION("Left left case imbalance") {
      avlTree<int> tree;

      tree.insert(1);
      tree.insert(2);
      tree.insert(3);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "2\n"
                           "|_ 1\n"
                           "|_ 3\n");
   }

   SECTION("Right left case imbalance") {
      avlTree<int> tree;

      tree.insert(2);
      tree.insert(4);
      tree.insert(3);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ 2\n"
                           "|_ 4\n");
   }

   SECTION("Left right case imbalance") {
      avlTree<int> tree;

      tree.insert(4);
      tree.insert(2);
      tree.insert(3);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ 2\n"
                           "|_ 4\n");
   }

   SECTION("Imbalanced tree") {
      avlTree<int> tree = make_tree_from_vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});


      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "4\n"
                           "|_ 2\n"
                           "|  |_ 1\n"
                           "|  |_ 3\n"
                           "|_ 8\n"
                           "   |_ 6\n"
                           "   |  |_ 5\n"
                           "   |  |_ 7\n"
                           "   |_ 9\n"
                           "      |_ .\n"
                           "      |_ 10\n");
   }

}

TEST_CASE("display_indented", "[avlTree]") {

   SECTION("Empty tree") {
      avlTree<int> tree;

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }

   SECTION("Easy test tree") {
      avlTree<int> tree = make_easy_test_tree();

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "6\n"
                           "|_ 3\n"
                           "|  |_ 2\n"
                           "|  |  |_ 1\n"
                           "|  |  |_ .\n"
                           "|  |_ 4\n"
                           "|     |_ .\n"
                           "|     |_ 5\n"
                           "|_ 9\n"
                           "   |_ 7\n"
                           "   |  |_ .\n"
                           "   |  |_ 8\n"
                           "   |_ 10\n");
   }
}

TEST_CASE("operator<<", "[avlTree]") {

   SECTION("Empty tree") {
      avlTree<int> tree;

      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == ".");
   }

   SECTION("One node tree") {
      avlTree<int> tree;
      tree.insert(3);

      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "3(.,.)");
   }

   SECTION("Easy test tree") {
      avlTree<int> tree = make_easy_test_tree();

      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
   }

   SECTION("More complex test tree") {
      avlTree<int> tree = make_tree_from_vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

      ostringstream oss;
      oss << tree;
      REQUIRE(oss.str() == "4(2(1(.,.),3(.,.)),8(6(5(.,.),7(.,.)),9(.,10(.,.))))");
   }

}

TEST_CASE("operator>>", "[avlTree]") {

   SECTION("Empty tree") {

      avlTree<int> tree;
      string emptyTree = ".";

      istringstream iss(emptyTree);
      iss >> tree;

      ostringstream oss;
      oss << tree;

      REQUIRE(oss.str() == ".");
   }

   SECTION("One node tree") {
      avlTree<int> tree;
      string sTree = "3(.,.)";

      istringstream iss(sTree);
      iss >> tree;

      ostringstream oss;
      oss << tree;

      REQUIRE(oss.str() == "3(.,.)");
   }

   SECTION("Easy test tree") {
      avlTree<int> tree;
      string sTree = "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))";

      istringstream iss(sTree);
      iss >> tree;

      ostringstream oss;
      oss << tree;

      REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
   }

   SECTION("More complex test tree") {
      avlTree<int> tree;
      string sTree = "1(.,2(.,3(.,4)))";

      istringstream iss(sTree);
      iss >> tree;

      ostringstream oss;
      oss << tree;

      REQUIRE(oss.str() == "3(1(.,2(.,.)),4(.,.))");
   }
}

TEST_CASE("operator=", "[avlTree]") {

   SECTION("Affectation in an empty tree") {
      avlTree<int> tree = make_easy_test_tree();
      avlTree<int> tree2;
      tree2 = tree;
      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }

   SECTION("Affectation in a non empty tree") {
      avlTree<int> tree = make_easy_test_tree();
      avlTree<int> tree2 = make_tree_from_vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
      tree2 = tree;
      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }

   SECTION("Affectation of an empty tree in a non empty tree") {
      avlTree<int> tree;
      avlTree<int> tree2 = make_easy_test_tree();
      tree2 = tree;
      ostringstream oss1, oss2;
      tree.show_indented(oss1);
      tree2.show_indented(oss2);
      REQUIRE(oss1.str() == oss2.str());
   }
}

TEST_CASE("min and max", "[avlTree]") {

   SECTION("Min easy test tree") {
      avlTree<int> tree = make_easy_test_tree();

      REQUIRE(tree.min() == 1);
   }

   SECTION("Min one element tree") {
      avlTree<int> tree;
      tree.insert(13);
      REQUIRE(tree.min() == 13);
   }

   SECTION("Min empty tree") {
      avlTree<int> emptyTree;
      try {
         emptyTree.min();
      } catch (const std::exception &e) {
         REQUIRE((string) e.what() == "Tree is empty");
      }
   }

   SECTION("Max easy test tree") {
      avlTree<int> tree = make_easy_test_tree();
      REQUIRE(tree.max() == 10);
   }

   SECTION("Max one element tree") {
      avlTree<int> tree;
      tree.insert(13);
      REQUIRE(tree.max() == 13);
   }

   SECTION("Max empty tree") {
      avlTree<int> emptyTree;
      try {
         emptyTree.max();
      } catch (const std::exception &e) {
         REQUIRE((string) e.what() == "Tree is empty");
      }
   }

}

TEST_CASE("erase", "[avlTree]") {

   SECTION("Empty tree") {
      avlTree<int> tree;
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");

   }

   SECTION("Tree with one node") {
      avlTree<int> tree;
      tree.insert(6);
      tree.erase(6);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }


   SECTION("Erase root") {
        avlTree<int> tree = make_tree_from_vector({2, 1, 3});
        tree.erase(2);
        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "1\n"
                             "|_ .\n"
                             "|_ 3\n");
   }

   SECTION("Erase leaf node") {
      avlTree<int> tree = make_tree_from_vector({2, 1, 3});
      tree.erase(3);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "2\n"
                           "|_ 1\n"
                           "|_ .\n");
   }

   SECTION ("Erase single child node") {
      avlTree<int> tree = make_tree_from_vector({5, 1, 6, 3});
      tree.erase(1);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "5\n"
                           "|_ 3\n"
                           "|_ 6\n");
   }

   SECTION("Erase node with two children") {
      avlTree<int> tree = make_tree_from_vector({6, 3, 8, 2, 4});
      tree.erase(3);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "6\n"
                           "|_ 2\n"
                           "|  |_ .\n"
                           "|  |_ 4\n"
                           "|_ 8\n");
   }

   SECTION("Erase that requires more than one rotation") {
      avlTree<int> tree = make_tree_from_vector({14, 8, 20, 3, 10, 17, 23, 2, 6, 13, 21, 5});
      ostringstream oss;


      tree.erase(14);
      tree.show_indented(oss);

      REQUIRE(oss.str() == "13\n"
                           "|_ 6\n"
                           "|  |_ 3\n"
                           "|  |  |_ 2\n"
                           "|  |  |_ 5\n"
                           "|  |_ 8\n"
                           "|     |_ .\n"
                           "|     |_ 10\n"
                           "|_ 20\n"
                           "   |_ 17\n"
                           "   |_ 23\n"
                           "      |_ 21\n"
                           "      |_ .\n");


   }

   SECTION("Erase min"){
      avlTree<int> tree = make_tree_from_vector({5, 1, 6, 3});
      tree.erase_min();

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "5\n"
                           "|_ 3\n"
                           "|_ 6\n");
   }

   SECTION("Erase max"){
      avlTree<int> tree = make_tree_from_vector({5, 1, 6, 3});
      tree.erase_max();

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ 1\n"
                           "|_ 5\n");
   }

   SECTION("Erase wrong key") {
      avlTree<int> tree = make_tree_from_vector({2,3,4});
      tree.erase(6);

      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == "3\n"
                           "|_ 2\n"
                           "|_ 4\n");
   }

}

   TEST_CASE("contains", "[avlTree]") {

      SECTION("Easy test tree: node is root") {
         avlTree<int> tree = make_easy_test_tree();
         REQUIRE(tree.contains(6) == true);
      }

      SECTION("Easy test tree: node is in left subtree") {
         avlTree<int> tree = make_easy_test_tree();
         REQUIRE(tree.contains(9) == true);
      }

      SECTION("Easy test tree: node is in right subtree") {
         avlTree<int> tree = make_easy_test_tree();
         REQUIRE(tree.contains(2) == true);
      }

      SECTION("Easy test tree: node not in tree") {
         avlTree<int> tree = make_easy_test_tree();
         REQUIRE(tree.contains(100) == false);
      }
   }

   TEST_CASE("height", "[avlTree]") {

      SECTION("Height of empty tree") {
         avlTree<int> tree;

         REQUIRE(tree.height() == 0);
      }

      SECTION("Height of a single node tree with no children") {
         avlTree<int> tree;

         tree.insert(0);

         REQUIRE(tree.height() == 1);
      }

      SECTION("Height of a single child tree") {
         avlTree<int> tree;

         tree.insert(2);
         tree.insert(8);

         REQUIRE(tree.height() == 2);
      }

      SECTION("Height of a complex tree") {
         avlTree<int> tree = make_tree_from_vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

         REQUIRE(tree.height() == 4);
      }
   }