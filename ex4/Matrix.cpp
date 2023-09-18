#include "Matrix.h"
#include <cmath>
using std::cout;
using std::endl;
#define SQRT 0.5
//constructor

Matrix::Matrix (const int rows, const int cols): _rows(rows), _cols(cols)
{
  if(rows < 1 || cols < 1)
  {
    throw std::length_error("error lengths gotta be positive ints bru");
  }
   _vals = new float[_rows*_cols];
   for(int i=0; i< _rows*_cols; i++)
   {
     _vals[i] = 0;
   }
}
//copy constructor
Matrix::Matrix (const Matrix &src_matrix):
_rows(src_matrix._rows), _cols(src_matrix._cols)
{
  _vals = new float[_rows*_cols];
  for(int i=0;i<_rows*_cols; i++)
  {
    _vals[i] = src_matrix._vals[i];
  }
}

Matrix::~Matrix ()
{
  delete[] _vals;
}

Matrix& Matrix::transpose()
{
  Matrix trans_temp(_rows, _cols);
  int temp = _rows;
  _rows = _cols;
  _cols = temp;
  //copy matrix for reference
  for(int i=0; i<_rows*_cols; i++)
  {
    trans_temp[i] = _vals[i];
  }
  //transpose matrix
  for (int i=0; i<_rows; i++)
  {
    for(int j=0; j<_cols; j++)
    {
      _vals[i*_cols+j] = trans_temp[j*_rows+i];
    }
  }
  return *this;
}

void Matrix::plain_print () const
{
  for(int i=0; i<_rows; i++)
  {
    for(int j=0; j<_cols; j++)
    {
      cout<<_vals[i*_cols + j] << " ";
    }
    cout<<endl;
  }
}

float Matrix::sum() const
{
  float sum = 0;
  for(int i=0; i<_rows*_cols; i++)
  {
    sum += _vals[i];
  }
  return sum;
}

Matrix Matrix::dot(const Matrix &rhs) const
{

  //handle error if not same dimensions
  if(_rows != rhs._rows ||_cols != rhs._cols)
  {
    throw std::length_error("dimensions of a and b not the same!");
  }
  Matrix dot_product(_rows, _cols);

  // assume same dimensions
  for(int i=0; i<_cols*_rows; i++)
  {
    dot_product[i] = _vals[i] * rhs._vals[i];
  }
  return dot_product;
}

float Matrix::norm()
{
  float fro = 0;
  for(int i=0; i<_rows*_cols; i++)
  {
    fro += (float) pow (_vals[i], 2);
  }
  return (float) pow(fro, SQRT);
}

int Matrix::argmax ()
{
  float max_val = _vals[0];
  int max_index = 0;
  for(int i=0; i<_rows*_cols; i++)
  {
    if(_vals[i] > max_val)
    {
      max_val = _vals[i];
      max_index = i;
    }
  }
  return max_index;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
  if(lhs._rows != rhs._rows || lhs._cols != rhs._cols)
  {
    throw std::length_error("dimensions arent matching");
  }
//  assume same dimensions
  Matrix sum(lhs._rows, lhs._cols);
//  sum._vals = new float[lhs._rows*lhs._cols];
  for(int i=0; i<lhs._rows*lhs._cols; i++)
  {
    sum._vals[i] = lhs._vals[i] + rhs._vals[i];
  }
  return sum;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
  if(_rows != rhs._rows || _cols != rhs._cols)
  {
    throw std::length_error("Matrices arent of matching dimensions!");
  }
  for(int i=0; i<_rows*_cols; i++)
  {
    _vals[i] += rhs._vals[i];
  }
  return *this;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
  if(lhs._cols != rhs._rows)
  {
    throw std::length_error("Incorrect dimensions for matrix mult!");
  }
  Matrix sum(lhs._rows, rhs._cols);
  sum._rows = lhs._rows;
  sum._cols = rhs._cols;
//  sum._vals = new float[lhs._rows*rhs._cols];
  for(int i=0; i<lhs._rows; i++)
  {
    for(int j=0; j<rhs._cols; j++)
    {
      for(int k=0; k<lhs._cols; k++)
      {
        sum._vals[i*sum._cols+ j] += lhs._vals[i*lhs._cols + k] * rhs
            ._vals[k*rhs._cols + j];
      }
    }
  }
  return sum;
}

const float& Matrix::operator[](const int i) const
{
  if(i<0 || _rows*_cols <= i)
  {
    throw std::out_of_range("i is out of range");
  }
  return _vals[i];
}

float& Matrix::operator[](const int i)
{
  if(i<0 || _rows*_cols <= i)
  {
    throw std::out_of_range("i is out of range");
  }
  return _vals[i];
}

const float& Matrix::operator()(const int i, const int j) const
{
  if( i < 0 || _rows <= i || j < 0 || _cols <= j)
  {
    throw std::out_of_range("i is out of range");
  }
  return _vals[i*_cols + j];
}

float& Matrix::operator()(const int i, const int j)
{
  if( i < 0 || _rows <= i || j < 0 || _cols <= j)
  {
    throw std::out_of_range("i is out of range");
  }
  return _vals[i*_cols + j];
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
  if(this != &rhs)
  {
    const float* old_my_vals = _vals;
    const float* old_rhs_vals = rhs._vals;
    _vals = new float[rhs._rows*rhs._cols];
    //if new throws this is umodified
    for(int i=0; i<rhs._rows*rhs._cols; i++)
    {
      _vals[i] = old_rhs_vals[i];
    }
    _rows = rhs._rows;
    _cols = rhs._cols;
    delete[] old_my_vals;
  }
//  const float* old_my_vals = _vals;
//  const float* old_rhs_vals = rhs._vals;
//  _vals = new float[rhs._cols*rhs._rows];
//  _rows = rhs._rows;
//  _cols = rhs._cols;
//  for(int i=0; i<rhs._rows*rhs._cols; i++)
//  {
//    _vals[i] = old_rhs_vals[i];
//  }
//  delete[] old_my_vals;
  return *this;
}

Matrix operator*(Matrix& matrix,const float scalar)
{
  Matrix result(matrix._rows, matrix._rows);
  for(int i=0; i<matrix._cols*matrix._rows; i++)
  {
    result._vals[i] = matrix._vals[i] * scalar;
  }
  return result;
}

Matrix operator*(const float scalar, Matrix& matrix)
{
  return matrix*scalar;
}

std::ostream& operator<<(std::ostream& os, const Matrix& a)
{
  for(int i=0; i< a._rows; i++)
  {
    for(int j=0; j<a._cols; j++)
    {
      if(a(i,j) > SEEABLE)
      {
        os << "**";
      }
      else
      {
        os << "  ";
      }
    }
    os << std::endl;
  }
  return os;
}

//to do
std::istream& operator>>(std::istream& is, const Matrix& matrix)
{
  if(!is)
  {
    throw std::runtime_error("bad stream");
  }
  for(int i = 0; i < matrix.get_rows()*matrix.get_cols(); i++)
  {
    is.read ( (char*) &matrix[i], sizeof (float));
  }
  if(!is.good())
  {
    throw std::runtime_error("file not big enough!");
  }
  return is;
}
