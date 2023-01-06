/*
    Copyright 2022 SUSTech CS205 2022-Fall
    License(CC BY 4.0)
    Author: Jiacheng Luo
    This is a demo of how to use the matrix libray.
*/
#include <math.h>
#include <stdio.h>

#include "matrix.h"  // NOLINT
// Use #include "matrix.h" to use the matrix library.
int main() {
  // You can use the following method to generate a new matrix.
  Matrix *created_matrix1 = createMatrixZeros(3, 4);
  // An all 0 matrix with the size of 3 * 4.
  showMatrix(created_matrix1);
  // print the matrix

  Matrix *created_matrix2 = createMatrixOnes(3, 4);
  // An all 1 matrix with the size of 3 * 4.
  showMatrix(created_matrix2);

  Matrix *created_matrix3 = createMatrix(3, 4, -1);
  // An all value matrix with the size of 3 * 4.
  showMatrix(created_matrix3);

  Matrix *created_matrix4 = createMatrixEye(3, 4);
  // A matrix of size 3 * 4 with a primary diagonal of 1.
  showMatrix(created_matrix4);

  Matrix *created_matrix5 = createMatrixIdentity(3);
  // A square matrix of order 3
  showMatrix(created_matrix5);

  float args[] = {1.1, 1.2, 1.3, 1.4, 2.1, 2.2, 2.3, 2.4, 3.1, 3.2, 3.3, 3.4};
  Matrix *created_matrix6 = createMatrixArray(3, 4, args);
  // A matrix of size 3 * 4 with specify array elements
  showMatrix(created_matrix6);

  Matrix *created_matrix7 = createMatrixString(
      "-1.1 -1.2 -1.3 -1.4; 2.1 2.2 2.3 2.4; -3.1 -3.2 -3.3 -3.4");
  // A matrix of size 3 * 4 with specify array elements
  showMatrix(created_matrix7);

  Matrix *created_matrix8 = createMatrixEmpty(3, 4);
  // A matrix of size 3 * 4 with empty elements
  showMatrix(created_matrix8);

  Matrix *created_matrix9 = createMatrixRandom(3, 4);
  // A matrix of size 3 * 4 with [0, 1) random elements
  showMatrix(created_matrix9);

  Matrix *created_matrix10 = createMatrixArange(1, 10, 2);
  // A matrix of size 1 * k with elements [1, 3, 5, 7, 9]
  showMatrix(created_matrix10);

  Matrix *created_matrix11 = createMatrixFile("../../doc/myMatrix.txt");
  // A matrix with elements in "myMatrix.txt"
  showMatrix(created_matrix11);

  // You can use the following methods to get some information about the
  // function

  showMatrix(created_matrix1);
  // Print the matrix on the console

  int created_matrix1_size = MatrixSize(created_matrix1);
  // Take the number of elements in the matrix
  printf("created_matrix1_size = %d\n", created_matrix1_size);

  float created_matrix1_11 = MatrixElement(created_matrix1, 1, 1);
  // Take the element [1, 1] in the matrix
  printf("created_matrix1[1, 1] = %.3lf\n", created_matrix1_11);

  float created_matrix6_max = MatrixMaxElement(created_matrix6);
  // Find the maximum element in the matrix
  printf("created_matrix6_max = %.3lf\n", created_matrix6_max);

  float created_matrix6_min = MatrixMinElement(created_matrix6);
  // Find the minimum element in the matrix
  printf("created_matrix6_min = %.3lf\n", created_matrix6_min);

  float created_matrix6_sum = MatrixElementSum(created_matrix6);
  // Find the element sum in the matrix
  printf("created_matrix6_sum = %.3lf\n", created_matrix6_sum);

  // use MatrixBegin() and MatrixEnd() to obtain begin and end iterator
  printf("Flatten created_matrix6: ");
  for (float *iter = MatrixBegin(created_matrix6);
       iter <= MatrixEnd(created_matrix6); iter++) {
    printf("%.3f ", *iter);
  }
  printf("\n");

  // use MatrixIterator() to obtain all iterators
  float **iters = MatrixIterators(created_matrix6);
  printf("Flatten created_matrix6: ");
  for (int i = 0; i < MatrixSize(created_matrix6); i++) {
    printf("%.3f ", *iters[i]);
  }
  printf("\n");

  // You can use the following methods to modify the matrix.

  modifyMatrixElement(created_matrix1, 1, 1, 123);
  // Modify a position element of the matrix
  showMatrix(created_matrix1);

  reshapeMatrix(created_matrix2, 2, 6);
  // Convert the matrix into a matrix with equal number of elements but
  // different shapes
  showMatrix(created_matrix2);

  Matrix *created_matrix6_12_to_34 = getSubMatrix(created_matrix6, 1, 2, 3, 4);
  // Get submatrix of matrix6[1:2, 3:4]
  showMatrix(created_matrix6_12_to_34);

  copySubMatrix(created_matrix1, 1, 2, 3, 4, created_matrix4, 1, 2, 3, 4);
  // Copy two submatrixes of equal size
  showMatrix(created_matrix1);

  showMatrix(created_matrix3);
  copyMatrix(created_matrix3, created_matrix1);
  // Value-copy two matrixes of equal size
  showMatrix(created_matrix3);
  modifyMatrixElement(created_matrix3, 1, 1, -12);
  showMatrix(created_matrix3);
  showMatrix(created_matrix1);

  showMatrix(created_matrix3);
  copyMatrixbyRef(&created_matrix3, &created_matrix1);
  // Reference-copy two matrixes of equal size
  showMatrix(created_matrix3);
  modifyMatrixElement(created_matrix3, 1, 1, -12);
  showMatrix(created_matrix3);
  showMatrix(created_matrix1);

  deleteMatrix(&created_matrix1);
  // Delete a matrix

  Matrix *matrix_operator1 = createMatrixString("6 5 4; 3 2 1");
  Matrix *matrix_operator2 = createMatrixString("1 2 3; 4 5 6");

  showMatrix(addMatrix(matrix_operator1, matrix_operator2));
  // add two matrixs
  showMatrix(subtractMatrix(matrix_operator1, matrix_operator2));
  // subtracrt two matrixs
  showMatrix(dotMatrix(matrix_operator1, matrix_operator2));
  // dot two matrixs
  showMatrix(devideMatrix(matrix_operator1, matrix_operator2));
  // devide two matrixs
  showMatrix(modMatrix(matrix_operator1, matrix_operator2));
  // mod two matrixs
  showMatrix(operatorMatrix(matrix_operator1, matrix_operator2, pow));
  // Use other functions (can be functions in math library)
  showMatrix(elementProcessMatrix(matrix_operator1, sin));
  // Use other functions (can be functions in math library);

  Matrix *matrix_operator3 = createMatrixString("10 11 12; 13 14 15");
  Matrix *matrix_operator4 = createMatrixString("1 1 1");
  showMatrix(addMatrix(matrix_operator3, matrix_operator4));
  // The broadcast mechanism can be enabled by calculating the corresponding
  // elements between two matrices.

  Matrix *matrix_det =
      createMatrixString("1 1 -1 2; -1 -1 -4 1; 2 4 -6 1; 1 2 4 2");
  // Determinant of calculation matrix
  printf("%.3f\n", MatrixDet(matrix_det));

  Matrix *matrix_mul1 = createMatrixString("2 3 1;4 5 6; 1 3 0; 4 7 9");
  Matrix *matrix_mul2 = createMatrixString("1 1; 0 1; -1 0");
  showMatrix(multiplyMatrix(matrix_mul1, matrix_mul2));
  // Compute matrix multiplication

  showMatrix(addScalarToMatrix(created_matrix2, 10));
  showMatrix(subtractScalarToMatrix(created_matrix2, 10));
  showMatrix(multiplyScalarToMatrix(created_matrix2, 10));
  showMatrix(devideScalarToMatrix(created_matrix2, 10));
  showMatrix(modScalarToMatrix(created_matrix2, 10));
  // Calculation of Matrix and Scalar

  Matrix *matrix_trans = createMatrixString("1 2 3; 4 5 6; 7 8 9; 10 11 12");
  showMatrix(transposeMatrix(matrix_trans));
  // Transposition of calculation matrix

  Matrix *matrix_inv = createMatrixString("1 1 -1; 1 2 1; 3 1 -2");
  showMatrix(MatrixInv(matrix_inv));
  // Calculating the inverse of a matrix

  showMatrix(MatrixPower(matrix_inv, 10));
  showMatrix(MatrixPower(matrix_inv, -10));
  showMatrix(multiplyMatrix(MatrixPower(matrix_inv, 10),
                            MatrixPower(matrix_inv, -10)));
  // Calculating the power of a matrix

  Matrix *matrix_put1 = createMatrixString("1 2; 3 4");
  Matrix *matrix_put2 = createMatrixString("5 6; 7 8");
  showMatrix(MatrixHorizontalStack(matrix_put1, matrix_put2));
  // Horizontal splicing of matrices
  showMatrix(MatrixVerticalStack(matrix_put1, matrix_put2));
  // Vertical splicing of matrices

  createMatrixFile("");
  Matrix *a = createMatrixString("1 2 3; 4 5 6; 7 8 9");
  Matrix *b = createMatrixString("1 2 3");
  addMatrix(a, b);
  Matrix *c = createMatrixZeros(1, 1);
  MatrixInv(c);
  // all warnings

  a = NULL;
  MatrixSize(a);
  b = createMatrixZeros(1, 1);
  MatrixElement(b, 1, 2);
  createMatrixEmpty(-1, 1);
  createMatrixEmpty(1, -1);
  createMatrixEmpty(1000000000, 1000000000);
  createMatrixString("1..1");
  reshapeMatrix(a, 1, 1);
  reshapeMatrix(b, -1, 1);
  reshapeMatrix(b, 1, -1);
  reshapeMatrix(b, 1000000000, 1000000000);
  reshapeMatrix(b, 1, 2);
  a = createMatrixZeros(3, 4);
  b = createMatrixOnes(4, 3);
  copyMatrix(a, b);
  deleteMatrix(&a);
  operatorMatrix(a, b, pow);
  a = createMatrixOnes(4, 4);
  operatorMatrix(a, b, pow);
  deleteMatrix(&a);
  addScalarToMatrix(a, 1);
  subtractScalarToMatrix(a, 1);
  multiplyScalarToMatrix(a, 1);
  devideScalarToMatrix(a, 1);
  modScalarToMatrix(a, 1);
  multiplyMatrix(a, b);
  a = createMatrixZeros(4, 3);
  multiplyMatrix(a, b);
  deleteMatrix(&a);
  MatrixMaxElement(a);
  MatrixMinElement(a);
  MatrixElementSum(a);
  transposeMatrix(a);
  elementProcessMatrix(a, sin);
  MatrixPower(a, 10);
  a = createMatrixZeros(4, 3);
  MatrixPower(a, 10);
  deleteMatrix(&a);
  MatrixBegin(a);
  MatrixEnd(a);
  MatrixIterators(a);
  MatrixHorizontalStack(a, b);
  MatrixVerticalStack(a, b);
  a = createMatrixZeros(1, 2);
  b = createMatrixZeros(3, 4);
  MatrixHorizontalStack(a, b);
  MatrixVerticalStack(a, b);
  deleteMatrix(&a);
  MatrixDet(a);
  a = createMatrixZeros(1, 2);
  MatrixDet(a);
  deleteMatrix(&a);
  MatrixInv(a);
  a = createMatrixZeros(1, 2);
  MatrixInv(a);
  // all errors
  return 0;
}
