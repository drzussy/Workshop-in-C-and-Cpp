#include "Dense.h"

Dense::Dense (const Matrix &weights, const Matrix &bias,
              const ActivationFunction func)
{
  if(bias.get_rows() != weights.get_rows() || bias.get_cols() != 1)
  {
    throw std::length_error("mismatching length of vectors");
  }
  _bias = bias;
  _weights = weights;
  _func = func;
}

Matrix& Dense::operator() (Matrix& img) const
{
//    why doesn't this work?
//    return _func(_weights*img + _bias)
    img = _weights*img + _bias;
    return _func(img);
}