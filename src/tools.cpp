#include <cmath>
#include <utility>

#include "s21_matrix_oop.hpp"

double **AllocateMemory(int rows, int cols) {
  double **mem = new double *[rows] {};
  try {
    for (int i = 0; i < rows; i++) {
      mem[i] = new double[cols]();
    }

  } catch (...) {
    for (int i = 0; i < rows; i++) {
      delete[] mem[i];
    }
    delete[] mem;
    throw;
  }
  return mem;
}

void FreeMemory(double **mem, int rows) {
  if (mem != nullptr) {
    for (int i = 0; i < rows; i++) {
      delete[] mem[i];
    }
    delete[] mem;
  }
}

bool isEqual(double a, double b) { return std::fabs(a - b) < 1e-6; }

void switchCols(S21Matrix &mtrx, int col1, int col2) {
  for (int i = 0; i < mtrx.getRows(); i++) {
    std::swap(mtrx(i, col1), mtrx(i, col2));
  }
}

void addRows(S21Matrix &mtrx, int row1, int row2, double k) {
  for (int j = 0; j < mtrx.getCols(); j++) {
    mtrx(row1, j) += mtrx(row2, j) * k;
  }
}

double get_elementij_mul(const S21Matrix &m1, const S21Matrix &m2, int i,
                         int j) {
  int k = m1.getCols();
  double result = 0.0;
  for (int l = 0; l < k; l++) {
    result += m1(i, l) * m2(l, j);
  }
  return result;
}