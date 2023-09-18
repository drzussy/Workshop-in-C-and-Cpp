// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>

#define SEEABLE 0.1
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
	int rows, cols;
} matrix_dims;

// Insert Matrix class here...
class Matrix{
  public:
    //  constructor
    Matrix(int rows, int cols);
    //  default constructor
    Matrix(): Matrix(1, 1){};
    //  copy constructor
    Matrix(const Matrix &src_matrix);
    //  destructor
    ~Matrix();

    //methods
    int get_rows() const {return _rows;};
    int get_cols() const {return _cols;};
    Matrix& transpose();
    Matrix& vectorize(){_rows = _rows*_cols; _cols = 1; return *this;};
    void plain_print() const;
    Matrix dot(const Matrix &rhs_mat) const;
    float norm();
    //  rref // bonus
    int argmax();
    float sum() const;

    //  operators
    Matrix& operator=(const Matrix &rhs);
    const float& operator[](int i) const;
    float& operator[](int i);
    const float& operator()(int i, int j) const;
    float& operator()(int i, int j);
    Matrix& operator+=(const Matrix& rhs);
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(Matrix& matrix, float scalar);
    friend Matrix operator*( float scalar, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, const Matrix& matrix);

  private:
    int _rows;
    int _cols;
    float* _vals;



};

#endif //MATRIX_H