#include "gtest_test_classes.hpp"

// ()
TEST_F(OperatorsTest, TestIndexInRange) { EXPECT_NEAR((*m1)(2, 2), 4.0, 1e-7); }

TEST_F(OperatorsTest, TestIndexInOutRange1) {
  EXPECT_THROW((*m1)(2, 5) = 5.6, std::out_of_range);
}

TEST_F(OperatorsTest, TestIndexInOutRange2) {
  EXPECT_THROW((*m1)(-5, 2) = 5.6, std::out_of_range);
}

// =
TEST_F(OperatorsTest, TestAssignment) {
  S21Matrix temp(1, 1);  // Изначально другой размер
  temp = *m1;

  ASSERT_EQ(temp.getRows(), m1->getRows());
  ASSERT_EQ(temp.getCols(), m1->getCols());

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), (*m1)(i, j), 1e-7);
}

TEST_F(OperatorsTest, TestAssignmentSelf) {
  S21Matrix temp = *m1;
  temp = temp;  // Самоприсваивание
  EXPECT_TRUE(temp == *m1);
}

// ==
TEST_F(OperatorsTest, TestEquality) {
  EXPECT_FALSE(*m1 == *m2);
  EXPECT_FALSE(*m1 == *m3);
  EXPECT_TRUE(*m1 == *m1);
}

// +
TEST_F(OperatorsTest, TestAdditionWithDifferentSizes) {
  EXPECT_THROW(S21Matrix temp = *m1 + *m2, std::invalid_argument);
}

TEST_F(OperatorsTest, TestAdditionNormal1) {
  S21Matrix temp = *m1 + *m1;

  ASSERT_EQ(temp.getRows(), m1->getRows());
  ASSERT_EQ(temp.getCols(), m1->getCols());

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), 2 * (i + j), 1e-7);
}

TEST_F(OperatorsTest, TestAdditionNormal2) {
  S21Matrix temp = *m1 + *m3;

  ASSERT_EQ(temp.getRows(), m1->getRows());
  ASSERT_EQ(temp.getCols(), m1->getCols());

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), (2.5 * i + 2 * j), 1e-7);
}

// -
TEST_F(OperatorsTest, TestSubtractionWithDifferentSizes) {
  EXPECT_THROW(S21Matrix temp = *m1 - *m2, std::invalid_argument);
}

TEST_F(OperatorsTest, TestSubstractionNormal1) {
  S21Matrix temp = *m1 - *m1;

  ASSERT_EQ(temp.getRows(), m1->getRows());
  ASSERT_EQ(temp.getCols(), m1->getCols());

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++) EXPECT_NEAR(temp(i, j), 0.0, 1e-7);
}

TEST_F(OperatorsTest, TestSubstractionNormal2) {
  S21Matrix temp = *m3 - *m1;

  ASSERT_EQ(temp.getRows(), m3->getRows());
  ASSERT_EQ(temp.getCols(), m3->getCols());

  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), 0.5 * i, 1e-7);
}

// *(double)
TEST_F(OperatorsTest, TestMultiplicationByScalar) {
  S21Matrix temp = *m1 * 2.5;
  for (int i = 0; i < temp.getRows(); i++)
    for (int j = 0; j < temp.getCols(); j++)
      EXPECT_NEAR(temp(i, j), (*m1)(i, j) * 2.5, 1e-7);
}

// *(S21Matrix)
TEST_F(OperatorsTest, TestMatrixMultiplication) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);

  // Заполняем матрицы для умножения
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) a(i, j) = 1.0;  // Матрица из единиц 2х3

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) b(i, j) = 2.0;  // Матрица из двоек 3х2

  S21Matrix result = a * b;
  ASSERT_EQ(result.getRows(), 2);
  ASSERT_EQ(result.getCols(), 2);

  // 1*2 + 1*2 + 1*2 = 6
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) EXPECT_NEAR(result(i, j), 6.0, 1e-7);
}

// +=
TEST_F(OperatorsTest, TestAdditionAssignment) {
  S21Matrix temp = *m1;
  temp += *m3;
  EXPECT_TRUE(temp == (*m1 + *m3));
}

// -=
TEST_F(OperatorsTest, TestSubtractionAssignment) {
  S21Matrix temp = *m3;
  temp -= *m1;
  EXPECT_TRUE(temp == (*m3 - *m1));
}

// *=
TEST_F(OperatorsTest, TestMultiplicationAssignment) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  b(0, 0) = 2;
  b(0, 1) = 0;
  b(1, 0) = 1;
  b(1, 1) = 2;

  S21Matrix expected = a * b;
  a *= b;

  EXPECT_TRUE(a == expected);
}