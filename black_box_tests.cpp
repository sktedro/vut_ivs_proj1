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
    std::pair<bool, void *> node[5];

protected:
    BinaryTree tree;
    virtual void SetUp(){
      int keys[] = {1, 2, 3, 4, 5};
      for(int i = 0; i < 5; i++)
        node[i] = tree.InsertNode(keys[i]);
    }
};

TEST_F(EmptyTree, GetRoot){
  EXPECT_EQ(tree.GetRoot(), nullptr);
  BinaryTree();
  EXPECT_EQ(tree.GetRoot(), nullptr);
}

TEST_F(EmptyTree, DeleteNode){
  EXPECT_EQ(tree.DeleteNode(1), false);
}

TEST_F(EmptyTree, FindNode){
  EXPECT_EQ(tree.FindNode(1), nullptr);
}

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

TEST_F(EmptyTree, InsertNode){
  std::pair <bool, void *> node_1 = tree.InsertNode(1);
  EXPECT_EQ(node_1.first, true);
  EXPECT_NE(node_1.second, nullptr);
}

TEST_F(EmptyTree, Insert_Find_Delete){
  ASSERT_EQ(tree.FindNode(1), nullptr);
  
  std::pair <bool, void *> node_1 = tree.InsertNode(1);
  ASSERT_EQ(node_1.first, true);
  EXPECT_NE(node_1.second, nullptr);
  EXPECT_EQ(node_1.second, tree.GetRoot());
  EXPECT_EQ(tree.FindNode(1), node_1.second);
  
  EXPECT_TRUE(tree.DeleteNode(1));
  EXPECT_FALSE(tree.DeleteNode(1));
  EXPECT_EQ(tree.FindNode(1), nullptr);
  
}



TEST_F(NonEmptyTree, GetRoot){
  EXPECT_NE(tree.GetRoot(), nullptr);
}

TEST_F(NonEmptyTree, InsertNode){
  std::pair <bool, void *> node_20 = tree.InsertNode(20);
  ASSERT_TRUE(node_20.first);
  ASSERT_NE(node_20.second, nullptr);
  
  void *pNode_1 = tree.FindNode(1);
  std::pair <bool, void *> node_1 = tree.InsertNode(1);
  EXPECT_FALSE(node_1.first);
  EXPECT_EQ(pNode_1, node_1.second);
}

TEST_F(NonEmptyTree, DeleteNode){
  EXPECT_TRUE(tree.DeleteNode(1));
  EXPECT_EQ(tree.FindNode(1), nullptr);
  EXPECT_FALSE(tree.DeleteNode(1));
}

TEST_F(NonEmptyTree, FindNode){
  //ASSERT_NE(tree.FindNode(1), nullptr);
  ASSERT_EQ(tree.FindNode(1), node[0].second);
  
  std::pair <bool, void *> node_20 = tree.InsertNode(20);
  ASSERT_TRUE(node_20.first);
  void *pNode_20 = node_20.second;
  EXPECT_EQ(pNode_20, tree.FindNode(20));
}


/*** Konec souboru black_box_tests.cpp ***/
