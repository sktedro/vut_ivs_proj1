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

/*
TEST_F(EmptyTree, GetRoot){
  EXPECT_EQ(tree.GetRoot(), nullptr);
  BinaryTree();
  EXPECT_EQ(tree.GetRoot(), nullptr);
}
 */

TEST_F(EmptyTree, InsertNode){
  std::pair <bool, void *> node_1 = tree.InsertNode(1);
  EXPECT_EQ(node_1.first, true);
  EXPECT_NE(node_1.second, nullptr);
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

TEST_F(NonEmptyTree, InsertExistingNode){
  std::pair <bool, void *> node_1 = tree.InsertNode(1);
  EXPECT_FALSE(node_1.first);
  EXPECT_EQ(node[0].second, node_1.second);
}

TEST_F(NonEmptyTree, InsertNode){
  std::pair <bool, void *> node_10 = tree.InsertNode(10);
  ASSERT_TRUE(node_10.first);
  ASSERT_NE(node_10.second, nullptr);
}

TEST_F(NonEmptyTree, DeleteNonExistantNode){
  EXPECT_FALSE(tree.DeleteNode(10));
}

TEST_F(NonEmptyTree, DeleteNode){
  EXPECT_NE(tree.FindNode(1), nullptr);
  EXPECT_TRUE(tree.DeleteNode(1));
  EXPECT_EQ(tree.FindNode(1), nullptr);
}

TEST_F(NonEmptyTree, FindNonExistantNode){
  ASSERT_EQ(tree.FindNode(10), nullptr);
}

TEST_F(NonEmptyTree, FindNode){
  ASSERT_EQ(tree.FindNode(1), node[0].second);
  /*
  std::pair <bool, void *> node_10 = tree.InsertNode(10);
  ASSERT_TRUE(node_10.first);
  void *pNode_10 = node_10.second;
  EXPECT_EQ(pNode_10, tree.FindNode(10));
   */
}





/*** Konec souboru black_box_tests.cpp ***/
