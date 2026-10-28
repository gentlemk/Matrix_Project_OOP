#include "gtest_test_classes.hpp"

void OperatorsTest::SetUp() {
  m1 = new S21Matrix(3, 4);
  m2 = new S21Matrix(4, 5);
  m3 = new S21Matrix(3, 4);

  for (int i = 0; i < m1->getRows(); i++)
    for (int j = 0; j < m1->getCols(); j++) (*m1)(i, j) = (i + j);

  for (int i = 0; i < m2->getRows(); i++)
    for (int j = 0; j < m2->getCols(); j++) (*m2)(i, j) = (i + j * 1.5);

  for (int i = 0; i < m3->getRows(); i++)
    for (int j = 0; j < m3->getCols(); j++) (*m3)(i, j) = (1.5 * i + j);
}

void OperatorsTest::TearDown() {
  delete m1;
  delete m2;
  delete m3;
}

void MethodsTest::SetUp() {
  m1 = new S21Matrix(3, 4);
  m2 = new S21Matrix(4, 3);
  m3 = new S21Matrix(3, 4);
  m4 = new S21Matrix(4, 4);
  m5 = new S21Matrix(5, 5);

  for (int i = 0; i < m1->getRows(); i++)
    for (int j = 0; j < m1->getCols(); j++) (*m1)(i, j) = (i + j);

  for (int i = 0; i < m2->getRows(); i++)
    for (int j = 0; j < m2->getCols(); j++) (*m2)(i, j) = (i + j * 1.5);

  for (int i = 0; i < m3->getRows(); i++)
    for (int j = 0; j < m3->getCols(); j++) (*m3)(i, j) = (1.5 * i + j);
}

void MethodsTest::TearDown() {
  delete m1;
  delete m2;
  delete m3;
  delete m4;
  delete m5;
}
