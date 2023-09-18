#include "Matrix.h"
#include "Activation.h"

int matrix_class_test();
int Dense_class_test();
bool readFileToMatrix (const std::string &filePath, Matrix &mat)
{
//TODO: implement this function
  std::ifstream rf;
  rf.open(filePath, std::ios::in | std::ios::binary);
  if(!rf.is_open())
  {
    return false;
  }
  rf >> mat;
  return true;
}

int main()
{
  if(matrix_class_test() == 1)
  {
    return 1;
  }
  if(Dense_class_test() == 1)
  {
    return 1;
  }
//
//  //activation tests
//  std::cout<<"matrix a" << std::endl;
//  b.plain_print();
//  std::cout << "matrix b" << std::endl;
//  a.plain_print();
//  a = b;
//  std::cout << "matrix a after assigment of b to a" << std::endl;
//  a.plain_print();
//  activation::relu();

  std::cout << "PASSED ALL TESTS" << std::endl;
  return 0;
}

int matrix_class_test()
{
  Matrix matrix1;
  if(matrix1.get_cols() != 1 || matrix1.get_rows() != 1)
  {
    return 1;
  }
  Matrix a(2, 2);
  if(a.get_cols() != 2 || a.get_rows() != 2)
  {
    return 1;
  }
  for(int i=0; i<4;i++)
  {
    a[i] = (float)i;
  }
  std::cout << "matrix a (" << a.get_rows() << "x" << a.get_cols() << "):" <<
            std::endl;
  a.plain_print();
  for(int i=0; i<4; i++)
  {
    if(a[i] != (float) i)
    {
      return 1;
    }
  }

  Matrix b(2, 2);
  for(int i=0; i<4;i ++)
  {
    b[i] = (float) i * 2;
  }
  std::cout << "matrix b (" << b.get_rows() << "x" << b.get_cols() << "):" <<
            std::endl;
  b.plain_print();


  //test regular multiplication
  Matrix c = a*b;
  std::cout << "matrix c (" << c.get_rows() << "x" << c.get_cols() << "):" <<
            std::endl;
  c.plain_print();

  //test transpose
  c.transpose();
  std::cout << "matrix c transposed (" << c.get_rows() << "x" << c.get_cols
      () << "):" << std::endl;
  c.plain_print();
  if(c[1] != 12 || c[0] != 4)
  {
    std::cout << "FAILED TEST: c is not transposed" << std::endl;
    return 1;
  }

  //test argmax
  if(c.argmax() != 3)
  {
    std::cout << "FAILED TEST: argmax c is index 3 and you got " << c.argmax
        () <<
              std::endl;
    return 1;
  }
//  //test dot, hadamard product

  std::cout << "hadamard_prod(a.c) (" << a.get_rows() << "x" << a.get_cols()
            << "):" << std::endl;
  a.dot (c).plain_print();
  std::cout << "Frobenius value: " << a.norm() << std::endl;

  Matrix d(2, 1);
  for(int i=0; i<2; i++)
  {
    d[i] = 4*((float)i+1);
  }
  std::cout << "matrix d (" << d.get_rows() << "x" << d.get_cols()
            << "):" << std::endl;
  d.plain_print();

  //test matrix multiplication
  Matrix e = b*d;
  std::cout << "matrix e = b*d (" << e.get_rows() << "x" << e.get_cols() <<
            "):" << std::endl;
  e.plain_print();
  if(e[0] != 16 || e[1] != 64)
  {
    std::cout << "FAILED TEST: matrix multiplication b*d failed" << std::endl;
    return 1;
  }

  //test matrix transpose with chaining
  d.transpose().transpose();
  std::cout << "matrix d transposed twice with chaining(" << d.get_rows() <<
            "x" << d
                .get_cols()
            << "):" << std::endl;
  d.plain_print();
  if(d.get_cols() != 1 || d.get_rows() != 2)
  {
    std::cout << "FAILED TEST: matrix d transposed twice failed" << std::endl;
    return 1;
  }

  //test argmax on e
  if(e.argmax() != 1)
  {
    std::cout << "FAILED TEST: argmax e is index 1 and you got " << e.argmax
        () <<
              std::endl;
    return 1;
  }

  float sum = e.sum();
  if(sum != 80)
  {
    std::cout << "FAILED TEST: sum of e is 80 and you got " << sum
              << std::endl;
    return 1;
  }

  //test () operator
  a(0,1) = 10;
  if(a(0,1) != 10)
  {
    std::cout << "operator () failed" << std::endl;
  }
  std::cout << "matrix a (" << a.get_rows() << "x" << a.get_cols() << "):" <<
            std::endl;
  a.plain_print();

  //test multiplication by scalar
  std::cout << "matrix 5*a(" << a.get_rows() << "x" << a.get_cols() << "):" <<
            std::endl;
  Matrix mult_res = 5*a;
  (mult_res).plain_print();
  if(mult_res(0,1) != 50)
  {
    std::cout << "FAILED TEST: matrix 5*a failed" << std::endl;
    return 1;
  }
  std::cout << "matrix a*0.2 (" << a.get_rows() << "x" << a.get_cols() << "):"
            <<std::endl;
  mult_res = mult_res*0.2;
  (mult_res).plain_print();
  if(mult_res(0,1) != 10)
  {
    std::cout << "FAILED TEST: matrix a*0.2 failed" << std::endl;
    return 1;
  }
//
//  std::cout << "a:" << std::endl;
//  a.plain_print();
//  std::cout << "d:" << std::endl;
//  d.plain_print();
//  std::cout << "e:" << std::endl;
//  e.plain_print();

  std::cout << "a*d+e:" << std::endl;
  a = a*d +e;

  a.plain_print();

  a.vectorize().transpose();
  std::cout << "matrix a vectorize then transpose:" << std::endl;
  a.plain_print();

  Matrix img(28,28);
  std::string file_path = "images/im0";
  readFileToMatrix (file_path, img);
  std::cout << img << std::endl;


  std::cout << "PASSED MATRIX CLASS TESTS" << std::endl;
  return 0;
}

int Dense_class_test()
{
  return 0;
}