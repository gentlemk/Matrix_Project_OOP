#ifndef S21_MATRIX_OOP_HPP
#define S21_MATRIX_OOP_HPP

#include <memory>
#include <stdexcept>

inline constexpr int DEFAULT_ROWS = 3;
inline constexpr int DEFAULT_COLS = 3;

class S21Matrix {
 private:
  int rows_;
  int cols_;
  double **matrix_;

 public:
  // Геттеры
  int getRows() const noexcept;
  int getCols() const noexcept;

  // Мутаторы
  void setRows(int rows);
  void setCols(int cols);

  // конструкторы и деструктор
  S21Matrix();  // конструктор по умолчанию
  S21Matrix(int rows, int cols);  // конструктор с параметрами
  S21Matrix(const S21Matrix &other);  // конструктор копирования
  S21Matrix(S21Matrix &&moved) noexcept;  // конструктор перемещения
  ~S21Matrix();                           // деструктор

  // операторы присваивания
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  // Арифметические операторы
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double number) const;

  // Составные операторы
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);

  // Сравнение
  bool operator==(const S21Matrix &other) const;

  // Доступ к элементам
  double &operator()(int row, int col);
  const double &operator()(int row, int col) const;

  // операции над матрицами
  bool EqMatrix(const S21Matrix &other) noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};

// Вспомогательные функции
bool isEqual(double a, double b);
void switchCols(S21Matrix &mtrx, int col1, int col2);
void inline swap(double &, double &);
void addRows(S21Matrix &mtrx, int row1, int row2, double k);
double get_elementij_mul(const S21Matrix &m1, const S21Matrix &m2, int i,
                         int j);
double **AllocateMemory(int rows, int cols);
void FreeMemory(double **mem, int rows);

#endif  // S21_MATRIX_OOP_HPP
