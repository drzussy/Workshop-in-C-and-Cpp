

#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
namespace activation
{
    //relu function
    Matrix& relu(Matrix& matrix);
    //softmax function
    Matrix& softmax(Matrix& matrix);
}
#endif //ACTIVATION_H