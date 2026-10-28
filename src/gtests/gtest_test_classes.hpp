#ifndef GTEST_MAIN_HPP
#define GTEST_MAIN_HPP

#include <gtest/gtest.h>

#include "../s21_matrix_oop.hpp"

class ConstructorTest : public ::testing::Test {
 protected:
  S21Matrix *m1_default;
  S21Matrix *m2_param;
  S21Matrix *m3_param_err;
  S21Matrix *m4_copied;
  S21Matrix *m5_moved;
};

class OperatorsTest : public ::testing::Test {
 protected:
  S21Matrix *m1;
  S21Matrix *m2;
  S21Matrix *m3;

  void SetUp() override;

  void TearDown() override;
};

class MethodsTest : public ::testing::Test {
 protected:
  S21Matrix *m1;
  S21Matrix *m2;
  S21Matrix *m3;
  S21Matrix *m4;
  S21Matrix *m5;

  void SetUp() override;
  void TearDown() override;
};

#endif
