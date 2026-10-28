#include "gtest_test_classes.hpp"

// EqMatrix()
TEST_F(MethodsTest, TestEqualMatrix) {
  EXPECT_FALSE(m1->EqMatrix(*m2));
  EXPECT_FALSE(m3->EqMatrix(*m1));
  EXPECT_FALSE(m4->EqMatrix(*m1));
  EXPECT_TRUE(m1->EqMatrix(*m1));
}

TEST_F(MethodsTest, TestSumMatrixWithDifferentSizes) {
  EXPECT_THROW(m1->SumMatrix(*m2), std::invalid_argument);
}

TEST_F(MethodsTest, TestSumMatrixNormal1) {
  S21Matrix temp = *m1;
  temp.SumMatrix(*m1);

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), 2 * (i + j), 1e-7);
}

TEST_F(MethodsTest, TestSubMatrixWithDifferentSizes) {
  EXPECT_THROW(m1->SubMatrix(*m2), std::invalid_argument);
}

TEST_F(MethodsTest, TestMulNumber) {
  const double num = 4.6;
  m2->MulNumber(num);

  for (int i = 0; i < m2->getRows(); i++)
    for (int j = 0; j < m2->getCols(); j++)
      EXPECT_NEAR((*m2)(i, j), num * (i + j * 1.5), 1e-7);
}

TEST_F(MethodsTest, TestMulMatrixWithDifferentSizes) {
  EXPECT_THROW(m1->MulMatrix(*m5), std::invalid_argument);
}

TEST_F(MethodsTest, TestTransposeNormal1) {
  S21Matrix transpose = m1->Transpose();

  EXPECT_EQ(transpose.getRows(), m1->getCols());
  EXPECT_EQ(transpose.getCols(), m1->getRows());

  for (int i = 0; i < transpose.getRows(); i++)
    for (int j = 0; j < transpose.getCols(); j++)
      EXPECT_NEAR(transpose(i, j), (*m1)(j, i), 1e-7);
}

TEST_F(MethodsTest, TestCalcComplementsWithNonSquareMatrix) {
  EXPECT_THROW(m1->CalcComplements(), std::invalid_argument);
}

TEST_F(MethodsTest, TestCalcComplements1x1) {
  S21Matrix a(1, 1);
  a(0, 0) = 42.0;
  S21Matrix result = a.CalcComplements();
  EXPECT_NEAR(result(0, 0), 1.0, 1e-7);
}

// Determinant()
TEST_F(MethodsTest, TestDeterminantWithNonSquareMatrix) {
  EXPECT_THROW(m1->Determinant(), std::invalid_argument);
}

TEST_F(MethodsTest, TestDeterminant1x1) {
  S21Matrix a(1, 1);
  a(0, 0) = 42.0;
  EXPECT_NEAR(a.Determinant(), 42.0, 1e-7);
}

TEST_F(MethodsTest, TestDeterminantWithZeros) {
  S21Matrix a(3, 3);
  double arr[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) a(i, j) = arr[i][j];

  EXPECT_NEAR(a.Determinant(), 0.0, 1e-7);
}

// InverseMatrix()
TEST_F(MethodsTest, TestInverseMatrixWithNonSquareMatrix) {
  EXPECT_THROW(m1->InverseMatrix(), std::invalid_argument);
}

TEST_F(MethodsTest, TestInverseMatrixWithZeroDeterminant) {
  for (int i = 0; i < m4->getRows(); i++)
    for (int j = 0; j < m4->getCols(); j++) (*m4)(i, j) = 0.0;

  EXPECT_THROW(m4->InverseMatrix(), std::invalid_argument);
}

TEST_F(MethodsTest, TestInverseMatrix1x1) {
  S21Matrix a(1, 1);
  a(0, 0) = 5.0;
  S21Matrix result = a.InverseMatrix();
  EXPECT_NEAR(result(0, 0), 0.2, 1e-7);
}