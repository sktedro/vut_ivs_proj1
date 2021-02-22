//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"
#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//


class EmptyTree: public ::testing::Test{
protected:
    BinaryTree tree;
};

class NonEmptyTree: public ::testing::Test{
public:
    std::pair<bool, Node_t*> node[5];
protected:
    BinaryTree tree;
    virtual void SetUp(){
      int keys[] = {0, 1, 2, 3, 4};
      for(int i = 0; i < 5; i++)
        node[i] = tree.InsertNode(keys[i]);
    }
};

class TreeAxioms: public ::testing::Test{
public:
    std::pair<bool, Node_t*> node[3];
protected:
    BinaryTree tree;
    virtual void SetUp(){
      int keys[] = {2, 1, 5};
      for(int i = 0; i < 3; i++)
        node[i] = tree.InsertNode(keys[i]);
    }
};

/*
TEST_F(EmptyTree, GetRoot){
  EXPECT_EQ(tree.GetRoot(), nullptr);
  BinaryTree();
  EXPECT_EQ(tree.GetRoot(), nullptr);
}
 */

TEST_F(EmptyTree, InsertNode){
  std::pair <bool, Node_t*> node_1 = tree.InsertNode(1);
  EXPECT_TRUE(node_1.first);
  EXPECT_NE(node_1.second, nullptr);
  EXPECT_EQ(node_1.second->key, 1);
}

TEST_F(EmptyTree, DeleteNode){
  EXPECT_EQ(tree.DeleteNode(1), false);
}

TEST_F(EmptyTree, FindNode){
  EXPECT_EQ(tree.FindNode(1), nullptr);
}

/*
TEST_F(EmptyTree, GetLeafNodes){
  std::vector<Node_t *> outLeafNodes;
  tree.GetLeafNodes(outLeafNodes);
  EXPECT_EQ(&outLeafNodes[0], nullptr);
}

TEST_F(EmptyTree, GetAllNodes){
  std::vector<Node_t *> outAllNodes;
  tree.GetLeafNodes(outAllNodes);
  EXPECT_EQ(&outAllNodes[0], nullptr);
}

TEST_F(EmptyTree, GetNonLeafNodes){
  std::vector<Node_t *> outNonLeafNodes;
  tree.GetLeafNodes(outNonLeafNodes);
  EXPECT_EQ(&outNonLeafNodes[0], nullptr);
}
 */


/*
TEST_F(NonEmptyTree, GetRoot){
  EXPECT_NE(tree.GetRoot(), nullptr);
}
 */

TEST_F(NonEmptyTree, InsertNode_Existing){
  std::pair <bool, Node_t*> node_1 = tree.InsertNode(1);
  EXPECT_FALSE(node_1.first);
  ASSERT_NE(node_1.second, nullptr);
  EXPECT_EQ(node[1].second, node_1.second);
  EXPECT_EQ(node_1.second->key, 1);
}

TEST_F(NonEmptyTree, InsertNode){
  std::pair <bool, Node_t*> node_5 = tree.InsertNode(5);
  EXPECT_TRUE(node_5.first);
  ASSERT_NE(node_5.second, nullptr);
  EXPECT_EQ(node_5.second->key, 5);
}

TEST_F(NonEmptyTree, DeleteNode_NonExistant){
  EXPECT_FALSE(tree.DeleteNode(5));
}

TEST_F(NonEmptyTree, DeleteNode){
  ASSERT_NE(node[1].second, nullptr);
  EXPECT_TRUE(tree.DeleteNode(1));
  EXPECT_EQ(tree.FindNode(1), nullptr);
}

TEST_F(NonEmptyTree, FindNode_NonExistant){
  ASSERT_EQ(tree.FindNode(5), nullptr);
}

TEST_F(NonEmptyTree, FindNode){
  Node_t *node_1 = tree.FindNode(1);
  ASSERT_EQ(node_1, node[1].second);
  EXPECT_EQ(node_1->key, 1);
  /*
  std::pair <bool, void *> node_10 = tree.InsertNode(10);
  ASSERT_TRUE(node_10.first);
  void *pNode_10 = node_10.second;
  EXPECT_EQ(pNode_10, tree.FindNode(10));
   */
}


TEST_F(TreeAxioms, Axiom1){
  std::vector<Node_t *> leafNodes {};
  tree.GetLeafNodes(leafNodes);
  int i = 0;
  for(auto node : leafNodes){
    EXPECT_EQ(node->color, 1);
    i++;
  }
  EXPECT_EQ(i, 4);
}

TEST_F(TreeAxioms, Axiom2){
  std::vector<Node_t *> allNodes {};
  tree.GetAllNodes(allNodes);
  int i = 0, j = 0;
  for(auto node : allNodes){
    ASSERT_NE(node, nullptr);
    if(node->color == 0){
      EXPECT_EQ(node->pLeft->color, 1);
      EXPECT_EQ(node->pRight->color, 1);
      j++;
    }
    i++;
  }
  EXPECT_EQ(i, 7);
  EXPECT_EQ(j, 2);
}

TEST_F(TreeAxioms, Axiom3){
  std::vector<Node_t *> leafNodes {};
  tree.GetLeafNodes(leafNodes);
  for(auto node : leafNodes){
    int i = 0;
    auto tmp = node;
    while(tmp != nullptr){
      i++;
      tmp = tmp->pParent;
    }
    EXPECT_EQ(i, 3);
  }
}

/*** Konec souboru black_box_tests.cpp ***/
