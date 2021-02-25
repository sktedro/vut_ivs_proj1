//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class General: public ::testing::Test{
};

class Empty: public ::testing::Test{
protected:
    Matrix m = Matrix();
};

class Square2x2: public ::testing::Test{
public:
    Matrix m = Matrix(2, 2);
protected:
    virtual void SetUp() {
      std::vector< std::vector<double> > values = {{1, 2}, {3, 4}};
      m.set(values);
    }
};

class Square3x3: public ::testing::Test{
public:
    //Solvable matrix:
    Matrix solvable = Matrix(3, 3);
    std::vector< std::vector<double> > solvable_values = {{1, -3, 3}, {2, 3, -1}, {4, -3, -1}};
    std::vector<double> solvable_right = {-4, 15, 19};
    std::vector<double> solvable_result = {5, 1, -2};
    //Invertible matrix:
    Matrix invertible = Matrix(3, 3);
    Matrix invertible_inverse = Matrix(3, 3);
    std::vector< std::vector<double> > invertible_values = {{2, 1, 2}, {2, 2, 1}, {1, 1, 1}};
    std::vector< std::vector<double> > inverse_values = {{1, 1, -3}, {-1, 0, 2}, {0, -1, 2}};
    //Non-invertible matrix:
    Matrix nonInvertible = Matrix(3, 3);
    std::vector< std::vector<double> > nonInvertible_values = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
};

class DifferentSizes: public ::testing::Test{
public:
    Matrix m = Matrix(2, 2);
    Matrix m2x3 = Matrix(2, 3);
    Matrix m3x2 = Matrix(3, 2);
protected:
    virtual void SetUp() {
      std::vector< std::vector<double> > values2x3 = {{1, 2}, {3, 4}, {5, 6}};
      m2x3.set(values2x3);
      std::vector< std::vector<double> > values3x2 = {{1, 2, 5}, {3, 4, 6}};
      m3x2.set(values3x2);
    }
};

class Square2x2_2: public ::testing::Test{
public:
    Matrix m1 = Matrix(2, 2);
    Matrix m2 = Matrix(2, 2);
protected:
    virtual void SetUp() {
      std::vector< std::vector<double> > values = {{1, 2}, {3, 4}};
      m1.set(values);
      values = {{0, 1}, {2, 3}};
      m2.set(values);
    }
};

/*
 * Constructor tests
 */

TEST_F(General, ConstSquare1Matrix){
  EXPECT_NO_THROW(Matrix());
}

TEST_F(General, ConstValidMatrix){
  EXPECT_NO_THROW(Matrix(1,1));
}

TEST_F(General, ConstInvalidMatrix){
  EXPECT_ANY_THROW(Matrix(1, 0));
  EXPECT_ANY_THROW(Matrix(0, 1));
  EXPECT_ANY_THROW(Matrix(0, 0));
}

/*
 * Set and get
 */

TEST_F(Empty, SetVal){
  EXPECT_TRUE(m.set(0, 0, 1));
}

TEST_F(Empty, SetInvalidVal){
  EXPECT_FALSE(m.set(-1, -1, 1));
  EXPECT_FALSE(m.set(1, 1, 1));
  EXPECT_FALSE(m.set(1, 0, 1));
  EXPECT_FALSE(m.set(0, 1, 1));
}

TEST_F(Empty, SetInvalidArr){
  std::vector<std::vector< double > > values = {{1, 2}, {3, 4}};
  EXPECT_FALSE(m.set(values));
}

TEST_F(Empty, GetVal){
  EXPECT_EQ(m.get(0, 0), 0);
}

TEST_F(Empty, GetInvalidVal){
  EXPECT_ANY_THROW(m.get(1, 1));
  EXPECT_ANY_THROW(m.get(1, 0));
  EXPECT_ANY_THROW(m.get(0, 1));
}

TEST_F(Square2x2, Set2x2){
  Matrix m2 = Matrix(2, 2);
  ASSERT_TRUE(m2.set(0, 0, 1));
  ASSERT_TRUE(m2.set(0, 1, 2));
  ASSERT_TRUE(m2.set(1, 0, 3));
  ASSERT_TRUE(m2.set(1, 1, 4));
  EXPECT_EQ(m, m2);
}

TEST_F(Square2x2, Get2x2){
  EXPECT_EQ(m.get(0, 0), 1);
  EXPECT_EQ(m.get(0, 1), 2);
  EXPECT_EQ(m.get(1, 0), 3);
  EXPECT_EQ(m.get(1, 1), 4);
}

TEST_F(Square2x2, Set2x2Arr){
  Matrix m2 = Matrix(2, 2);
  ASSERT_TRUE(m2.set({{1, 2}, {3, 4}}));
  EXPECT_EQ(m, m2);
}

/*
 * Comparing matrices
 */

TEST_F(Square2x2_2, Equal){
  EXPECT_TRUE(m1 == m1);
}

TEST_F(Square2x2_2, NonEqual){
  EXPECT_FALSE(m2 == m1);
  EXPECT_FALSE(m1 == m2);
}

TEST_F(DifferentSizes, EqualDifferentSizes){
  EXPECT_ANY_THROW(m == m2x3);
  EXPECT_ANY_THROW(m == m3x2);
}

/*
 * Adding matrices
 */

TEST_F(Square2x2_2, Add){
  Matrix result = m1 + m2;
  Matrix expected = Matrix(2, 2);
  expected.set({{1, 3}, {5, 7}});
  EXPECT_EQ(expected, result);
}

TEST_F(DifferentSizes, AddDifferentSizes){
  EXPECT_ANY_THROW(m + m2x3);
  EXPECT_ANY_THROW(m + m3x2);
}

/*
 * Multiplying matrices
 */

TEST_F(Square2x2_2, MultiplyByMatrix){
  Matrix result1 = m1 * m2;
  //TODO
}

TEST_F(DifferentSizes, MultiplyByMatrixOfDifferentSize){
  EXPECT_ANY_THROW(m * m3x2);
}

TEST_F(Square2x2_2, MultiplyByConstant){
  Matrix result1 = m1 * 2;
  Matrix result2 = m1 * 0;
  //TODO
}

/*
 * Solving equations
 */

TEST_F(Empty, SolveSingularEquation){
  std::vector<double> values = {0};
  EXPECT_ANY_THROW(m.solveEquation(values));
}

TEST_F(Empty, SolveEquationInvalid){
  std::vector<double> v[] = {{}, {1}, {1, 2}, {1, 2, 3}};
  for(int i = 0; i < 4; i++)
    EXPECT_ANY_THROW(m.solveEquation(v[i]));
  //TODO ma toto zmysel?
}

TEST_F(Empty, SolveOneSolution){
  std::vector<std::vector<double>> values = {{3, 1}, {3, -2}};
  std::vector<double> right = {15, 6};
  std::vector<double> solution = {4, 3};
  Matrix m = Matrix(2, 2);
  ASSERT_TRUE(m.set(values));
  EXPECT_EQ(m.solveEquation(right), solution);
}

TEST_F(Empty, SolveInfiniteSolutions){
  std::vector<std::vector<double>> values = {{1, 2}, {-2, -4}};
  std::vector<double> right = {18, -36};
  Matrix m = Matrix(2, 2);
  ASSERT_TRUE(m.set(values));
  EXPECT_ANY_THROW(m.solveEquation(right));
}

TEST_F(Empty, SolveNoSolution){
  std::vector<std::vector<double>> values = {{2, 3}, {4, 6}};
  std::vector<double> right = {35, 75};
  Matrix m = Matrix(2, 2);
  ASSERT_TRUE(m.set(values));
  EXPECT_ANY_THROW(m.solveEquation(right));
}

TEST_F(Empty, SolveInvalidRightSide){
  std::vector<std::vector<double>> values = {{3, 1}, {3, -2}};
  std::vector<double> right1 = {15};
  std::vector<double> right2 = {15, 6, 6};
  Matrix m = Matrix(2, 2);
  ASSERT_TRUE(m.set(values));
  EXPECT_ANY_THROW(m.solveEquation(right1));
  EXPECT_ANY_THROW(m.solveEquation(right2));
}

TEST_F(Empty, SolveInvalidNonSquare){
  std::vector<std::vector<double>> values = {{1, 2}, {3, 4}, {5, 6}};
  Matrix m = Matrix(3, 2);
  std::vector<double> right = {1, 2};
  //TODO Tu maju byt tri hodnoty... Ale s dvoma to funguje :)))
  ASSERT_TRUE(m.set(values));
  EXPECT_ANY_THROW(m.solveEquation(right));
}

TEST_F(Empty, Solve1x1){
  Matrix m = Matrix();
  std::vector<double> values = {1};
  ASSERT_TRUE(m.set(0, 0, 1));
  ASSERT_EQ(m.solveEquation(values), values);
}

TEST_F(Square3x3, Solve3x3){
  ASSERT_TRUE(solvable.set(solvable_values));
  EXPECT_EQ(solvable.solveEquation(solvable_right), solvable_result);
}

TEST_F(Empty, Solve4x4){
  Matrix m = Matrix(4, 4);
  std::vector< std::vector<double> > values = {{2, 1, 1, 1}, {1, 2, 1, 1}, {1, 1, 2, 1}, {1, 1, 1, 2}};
  ASSERT_TRUE(m.set(values));
  std::vector<double> right = {11, 12, 13, 14};
  std::vector<double> result = {1, 2, 3, 4};
  ASSERT_EQ(m.solveEquation(right), result);
}

/*
 * Transposing a matrix
 */

TEST_F(Square2x2, Transpose){
  Matrix transposed = Matrix(2, 2);
  transposed.set({{1, 3}, {2, 4}});
  EXPECT_EQ(m.transpose(), transposed);
}

/*
 * Inverse matrix tests
 */

TEST_F(Square2x2, Inverse){
  Matrix inverted = Matrix(2, 2);
  ASSERT_TRUE(inverted.set({{-2, 1}, {1.5, -0.5}}));
  EXPECT_EQ(m.inverse(), inverted);
}

TEST_F(Empty, InverseInvalid){
  EXPECT_ANY_THROW(m.inverse());
}

TEST_F(Square3x3, Inverse3x3){
  ASSERT_TRUE(invertible_inverse.set(inverse_values));
  ASSERT_TRUE(invertible.set(invertible_values));
  EXPECT_EQ(invertible.inverse(),  invertible_inverse);
}

TEST_F(Square3x3, InverseSingular3x3){
  ASSERT_TRUE(nonInvertible.set(nonInvertible_values));
  EXPECT_ANY_THROW(nonInvertible.inverse());
}

/*** Konec souboru white_box_tests.cpp ***/
