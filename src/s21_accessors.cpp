#include "s21_matrix_oop.hpp"

int S21Matrix::getRows() const noexcept { return rows_; }
int S21Matrix::getCols() const noexcept { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0) throw std::invalid_argument("Incorrect matrix size");

  if (rows != rows_) {
    auto newMatrix = AllocateMemory(rows, cols_);
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols_; j++)
        newMatrix[i][j] = (i < rows_) ? matrix_[i][j] : 0.0;

    FreeMemory(matrix_, rows_);
    rows_ = rows;
    matrix_ = newMatrix;
  }
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0) throw std::invalid_argument("Incorrect matrix size");

  if (cols != cols_) {
    auto newMatrix = AllocateMemory(rows_, cols);
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols; j++)
        newMatrix[i][j] = ((j < cols_) && matrix_) ? matrix_[i][j] : 0.0;

    FreeMemory(matrix_, rows_);
    cols_ = cols;
    matrix_ = newMatrix;
  }
}
