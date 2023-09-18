#include "MlpNetwork.h"

#define ARR_SIZE 4

#define RELU_REPS 3

digit MlpNetwork::operator() (const Matrix &img)
{
  Matrix temp_im = img;
  temp_im.vectorize();
  temp_im = layer1(temp_im);
  temp_im = layer2(temp_im);
  temp_im = layer3(temp_im);
  temp_im = layer4(temp_im);
  digit result;
  result.value = temp_im.argmax();
  result.probability = temp_im[(int)result.value];
  return result;
}