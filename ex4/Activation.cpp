#include "Activation.h"
#include <cmath>

Matrix& activation::relu(Matrix& matrix)
{
  int rows = matrix.get_rows();
  int cols = matrix.get_cols();
  //for col in matrix
  for(int i=0; i<cols*rows; i++)
  {
    if(matrix[i] < 0)
    {
      matrix[i] = 0;
    }
  }
  return matrix;
}

//softmax function
Matrix& activation::softmax(Matrix& matrix)
{
  int rows = matrix.get_rows();
  int cols = matrix.get_cols();
  //iterate over columns
  float outer_scalar_sum = 0;
  for(int i=0; i<cols*rows;i++)
  {

      outer_scalar_sum += std::exp(matrix[i]);
      matrix[i] = std::exp(matrix[i]);
  }
  for(int i=0; i<cols*rows; i++)
  {
    matrix[i] *= 1 / outer_scalar_sum;
  }
  return matrix;
}



