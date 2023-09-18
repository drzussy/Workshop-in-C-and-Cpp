#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
typedef Matrix& (*ActivationFunction)(Matrix&);

class Dense{
 public:
  //constructor
  Dense(const Matrix& weights, const Matrix& bias, ActivationFunction
  func);

  //get_weights
  const Matrix& get_weights() const{return _weights;};
  //get_bias
  const Matrix& get_bias() const{return _bias;};
  //get_activation
  ActivationFunction get_activation() const {return _func;};
  //operators:
  Matrix& operator()(Matrix& img) const;

 private:
  Matrix _weights;
  Matrix _bias;
  ActivationFunction _func;
};

#endif //DENSE_H
