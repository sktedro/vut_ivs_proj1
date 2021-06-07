//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     PATRIK SKALOS <xskalo01@stud.fit.vutbr.cz>
// $Date:       $2021-02-25
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author PATRIK SKALOS
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
 * EmptyTree tests
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
 * NonEmptyTree tests
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
}

/*
 * TreeAxioms tests
 */

TEST_F(TreeAxioms, Axiom1){
  std::vector<Node_t *> leafNodes {};
  tree.GetLeafNodes(leafNodes);
  for(auto node : leafNodes)
    EXPECT_EQ(node->color, 1);
}

TEST_F(TreeAxioms, Axiom2){
  std::vector<Node_t *> allNodes {};
  tree.GetAllNodes(allNodes);
  for(auto node : allNodes){
    ASSERT_NE(node, nullptr);
    if(node->color == 0){
      EXPECT_EQ(node->pLeft->color, 1);
      EXPECT_EQ(node->pRight->color, 1);
    }
  }
}

TEST_F(TreeAxioms, Axiom3){
  std::vector<Node_t *> leafNodes {};
  tree.GetLeafNodes(leafNodes);
  bool init = false;
  int refVal = 0;
  for(auto node : leafNodes){
    int curVal = 0;
    auto tmp = node;
    while(tmp != nullptr){
      if(!init)
        refVal++;
      curVal++;
      tmp = tmp->pParent;
    }
    EXPECT_EQ(refVal, curVal);
    init = true;
  }
}

/*** Konec souboru black_box_tests.cpp ***/
