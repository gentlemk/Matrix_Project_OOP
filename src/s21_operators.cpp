#include "s21_matrix_oop.hpp"

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (other.getRows() != rows_ || other.getCols() != cols_)
    throw std::invalid_argument("Different dimensions of the matrices");

  S21Matrix result(*this);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(i, j) += other(i, j);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  if (other.getRows() != rows_ || other.getCols() != cols_)
    throw std::invalid_argument("Different dimensions of the matrices");

  S21Matrix result(*this);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(i, j) -= other(i, j);

  return result;
}

S21Matrix S21Matrix::operator*(const double number) const {
  S21Matrix result(*this);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(i, j) *= number;

  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (cols_ != other.getRows())
    throw std::invalid_argument(
        "The number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");

  S21Matrix result(rows_, other.getCols());
  for (int i = 0; i < result.getRows(); i++)
    for (int j = 0; j < result.getCols(); j++)
      result(i, j) = get_elementij_mul(*this, other, i, j);

  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  if (other.getRows() != rows_ || other.getCols() != cols_) return false;

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      if (!isEqual(other(i, j), (*this)(i, j))) return false;

  return true;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (other.getRows() != rows_ || other.getCols() != cols_)
    throw std::invalid_argument("Different dimensions of the matrices");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) += other(i, j);

  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (other.getRows() != rows_ || other.getCols() != cols_)
    throw std::invalid_argument("Different dimensions of the matrices");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) -= other(i, j);

  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  if (cols_ != other.getRows())
    throw std::invalid_argument(
        "The number of columns of the first matrix is not "
        "equal to the number of rows of the second matrix");

  S21Matrix result(rows_, other.getCols());

  for (int i = 0; i < result.getRows(); i++)
    for (int j = 0; j < result.getCols(); j++)
      result(i, j) = get_elementij_mul(*this, other, i, j);

  *this = std::move(result);
  return *this;
}

const double &S21Matrix::operator()(int row, int col) const {
  // исключение - выход за пределы массива
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::out_of_range("The index is outside the matrix");

  return matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    throw std::out_of_range("The index is outside the matrix");

  return matrix_[row][col];
}