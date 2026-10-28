#include "s21_matrix_oop.hpp"

bool S21Matrix::EqMatrix(const S21Matrix &other) noexcept {
  return (*this == other);
}

void S21Matrix::SumMatrix(const S21Matrix &other) { *this += other; }
void S21Matrix::SubMatrix(const S21Matrix &other) { *this -= other; }

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) { *this *= other; }

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(j, i) = (*this)(i, j);
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result(0, 0) = 1.0;
    return result;
  }

  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      int mi = 0, mj = 0;
      for (int r = 0; r < rows_; r++) {
        if (r == i) continue;
        mj = 0;
        for (int c = 0; c < cols_; c++) {
          if (c == j) continue;
          minor_matrix(mi, mj) = (*this)(r, c);
          mj++;
        }
        mi++;
      }
      result(i, j) = minor_matrix.Determinant();
      if ((i + j) % 2) result(i, j) *= -1;
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");

  S21Matrix temp = *this;
  double det = 1.0;

  for (int i = 0; i < temp.getRows(); i++) {
    int pivot = i;
    for (int r = i + 1; r < temp.getRows(); r++) {
      if (!isEqual(temp(r, i), 0.0)) {
        pivot = r;
        break;
      }
    }

    if (isEqual(temp(pivot, i), 0.0)) {
      return 0.0;
    }

    if (pivot != i) {
      for (int c = 0; c < temp.getCols(); c++) {
        std::swap(temp(i, c), temp(pivot, c));
      }
      det *= -1.0;
    }

    double support_elem = temp(i, i);

    for (int r = i + 1; r < temp.getRows(); r++) {
      if (!isEqual(temp(r, i), 0.0)) {
        double coeff = -(temp(r, i) / support_elem);
        addRows(temp, r, i, coeff);
      }
    }
  }

  for (int i = 0; i < temp.getRows(); i++) {
    det *= temp(i, i);
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (isEqual(det, 0.0))
    throw std::invalid_argument("The determinant of the matrix is 0");

  S21Matrix result = (this->CalcComplements()).Transpose();
  result.MulNumber(1.0 / det);
  return result;
}