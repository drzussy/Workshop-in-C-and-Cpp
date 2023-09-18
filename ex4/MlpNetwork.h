//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};

// Insert MlpNetwork class here...
class MlpNetwork{
 public:
  //constructor
  MlpNetwork(const Matrix* weights, const Matrix* biases):
  layer1(weights[0],biases[0],activation::relu),
  layer2(weights[1],biases[1],activation::relu),
  layer3(weights[2],biases[2],activation::relu),
  layer4(weights[3],biases[3],activation::softmax)
  {
    if(weights[0].get_rows() != weights[1].get_cols() ||
    weights[1].get_rows() != weights[2].get_cols() ||
    weights[2].get_rows() != weights[3].get_cols())
    {
      throw std::length_error("consecutive layer matrix dimensions dont "
                              "match");
    }
  };
  //operators
  digit operator()(const Matrix& img);

 private:
  Dense layer1;
  Dense layer2;
  Dense layer3;
  Dense layer4;

};
#endif // MLPNETWORK_H