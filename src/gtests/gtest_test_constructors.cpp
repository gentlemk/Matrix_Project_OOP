#include "gtest_test_classes.hpp"

TEST_F(ConstructorTest, TestDefaultConstructor) {
  m1_default = new S21Matrix();

  EXPECT_EQ(m1_default->getRows(), DEFAULT_ROWS);
  EXPECT_EQ(m1_default->getCols(), DEFAULT_COLS);

  delete m1_default;
}

TEST_F(ConstructorTest, TestParamConstructorWithError) {
  EXPECT_THROW(S21Matrix(-4, 3), std::invalid_argument);
  EXPECT_THROW(S21Matrix(3, -4), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 3), std::invalid_argument);
  EXPECT_THROW(S21Matrix(3, 0), std::invalid_argument);
}

TEST_F(ConstructorTest, TestParamConstructor) {
  m2_param = new S21Matrix(4, 6);

  EXPECT_EQ(m2_param->getRows(), 4);
  EXPECT_EQ(m2_param->getCols(), 6);

  delete m2_param;
}

TEST_F(ConstructorTest, TestCopyConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 10.0;
  original(1, 2) = 20.0;

  S21Matrix copied(original);

  EXPECT_TRUE(copied == original);

  copied(0, 0) = 99.0;
  EXPECT_NEAR(original(0, 0), 10.0, 1e-7);
}

TEST_F(ConstructorTest, TestMoveConstructorPreservesData) {
  S21Matrix original(2, 2);
  original(0, 0) = 10.0;
  original(1, 1) = 20.0;

  S21Matrix moved(std::move(original));

  EXPECT_NEAR(moved(0, 0), 10.0, 1e-7);
  EXPECT_NEAR(moved(1, 1), 20.0, 1e-7);
  EXPECT_EQ(original.getRows(), 0);
  EXPECT_EQ(original.getCols(), 0);
}

TEST_F(ConstructorTest, TestMoveConstructor) {
  m2_param = new S21Matrix(4, 6);
  m5_moved = new S21Matrix(std::move(*m2_param));

  EXPECT_EQ(m5_moved->getRows(), 4);
  EXPECT_EQ(m5_moved->getCols(), 6);
  EXPECT_EQ(m2_param->getRows(), 0);
  EXPECT_EQ(m2_param->getCols(), 0);

  delete m2_param;
  delete m5_moved;
}

TEST_F(ConstructorTest, TestMoveAssignment) {
  m2_param = new S21Matrix(4, 6);
  m5_moved = new S21Matrix(2, 2);

  // Перемещаем один объект в другой
  *m5_moved = std::move(*m2_param);

  EXPECT_EQ(m5_moved->getRows(), 4);
  EXPECT_EQ(m5_moved->getCols(), 6);

  // Проверяем, что исходный объект "опустошен"
  EXPECT_EQ(m2_param->getRows(), 0);
  EXPECT_EQ(m2_param->getCols(), 0);

  delete m2_param;
  delete m5_moved;
}

TEST_F(ConstructorTest, TestMoveAssignmentSelf) {
  m5_moved = new S21Matrix(4, 6);

  // Хак, чтобы обойти проверку компилятора -Werror=self-move
  S21Matrix &ref = *m5_moved;
  *m5_moved = std::move(ref);

  // Объект должен остаться целым и невредимым
  EXPECT_EQ(m5_moved->getRows(), 4);
  EXPECT_EQ(m5_moved->getCols(), 6);

  delete m5_moved;
}

TEST_F(ConstructorTest, SetRowsBadSize) {
  m2_param = new S21Matrix(2, 4);
  EXPECT_THROW(m2_param->setRows(-3), std::invalid_argument);
  EXPECT_THROW(m2_param->setRows(0), std::invalid_argument);  // проверка на 0
  delete m2_param;
}

TEST_F(ConstructorTest, SetRowsNormalLowerSize) {
  m2_param = new S21Matrix(2, 4);
  m2_param->setRows(1);
  EXPECT_EQ(m2_param->getRows(), 1);
  delete m2_param;
}

TEST_F(ConstructorTest, SetRowsNormalMoreSize) {
  m2_param = new S21Matrix(2, 4);
  m2_param->setRows(3);

  EXPECT_EQ(m2_param->getRows(), 3);

  for (int j = 0; j < 4; ++j)
    EXPECT_NEAR((*m2_param)(2, j), 0.0, 1e-7);  // Новые ячейки заполнены нулями

  delete m2_param;
}

TEST_F(ConstructorTest, SetColsBadSize) {
  m2_param = new S21Matrix(2, 4);
  EXPECT_THROW(m2_param->setCols(-3), std::invalid_argument);
  EXPECT_THROW(m2_param->setCols(0), std::invalid_argument);  // проверка на 0
  delete m2_param;
}

TEST_F(ConstructorTest, SetColsNormalLowerSize) {
  m2_param = new S21Matrix(2, 4);
  m2_param->setCols(1);
  EXPECT_EQ(m2_param->getCols(), 1);
  delete m2_param;
}

TEST_F(ConstructorTest, SetColsNormalMoreSize) {
  m2_param = new S21Matrix(2, 4);
  m2_param->setCols(5);

  EXPECT_EQ(m2_param->getCols(), 5);

  for (int i = 0; i < 2; ++i) EXPECT_NEAR((*m2_param)(i, 4), 0.0, 1e-7);

  delete m2_param;
}