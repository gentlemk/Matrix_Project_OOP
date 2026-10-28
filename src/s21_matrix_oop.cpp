#include "s21_matrix_oop.hpp"

#include <cstring>

S21Matrix::S21Matrix() : rows_{DEFAULT_ROWS}, cols_{DEFAULT_COLS} {
  matrix_ = AllocateMemory(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_{rows}, cols_{cols}, matrix_{nullptr} {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Incorrect matrix size");
  matrix_ = AllocateMemory(rows, cols);
}

S21Matrix::~S21Matrix() { FreeMemory(matrix_, rows_); }

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_{other.rows_}, cols_{other.cols_} {
  matrix_ = AllocateMemory(rows_, cols_);

  for (int i = 0; i < rows_; i++)
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
}

S21Matrix::S21Matrix(S21Matrix &&moved) noexcept
    : rows_{moved.rows_}, cols_{moved.cols_}, matrix_{moved.matrix_} {
  moved.cols_ = 0;
  moved.rows_ = 0;
  moved.matrix_ = nullptr;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix temp(other);
    std::swap(rows_, temp.rows_);
    std::swap(cols_, temp.cols_);
    std::swap(matrix_, temp.matrix_);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    FreeMemory(matrix_, rows_);
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
