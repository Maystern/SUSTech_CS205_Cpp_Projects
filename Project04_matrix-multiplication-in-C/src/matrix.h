/*
    Copyright 2022 SUSTech CS205 2022-Fall
    License(CC BY 4.0)
    Author: Jiacheng Luo
    This is the header file of the matrix library.
*/
#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_
#include <stddef.h>
#include <stdint.h>
typedef struct _Matrix {
  size_t rows, cols;
  float *data;
} Matrix;
size_t MatrixSize(const Matrix *matrix);
float MatrixElement(const Matrix *matrix, const size_t row_id,
                    const size_t col_id);
float MatrixMaxElement(const Matrix *matrix);
float MatrixMinElement(const Matrix *matrix);
float MatrixElementSum(const Matrix *matrix);
float *MatrixBegin(const Matrix *matrix);
float *MatrixEnd(const Matrix *matrix);
float **MatrixIterators(const Matrix *matrix);
float MatrixDet(Matrix *matrix);
void modifyMatrixElement(const Matrix *matrix, const size_t row_id,
                         const size_t col_id, const float value);
void showMatrix(const Matrix *matrix);
void printMatrixToFile(const Matrix *matrix, const char *file_name);
void deleteMatrix(Matrix **matrix);
void reshapeMatrix(Matrix *matrix, const size_t rows, const size_t cols);
void copySubMatrix(const Matrix *dest_matrix, const size_t dest_row_id1,
                   const size_t dest_col_id1, const size_t dest_row_id2,
                   const size_t dest_col_id2, const Matrix *src_matrix,
                   const size_t src_row_id1, const size_t src_col_id1,
                   const size_t src_row_id2, const size_t src_col_id2);
void copyMatrix(const Matrix *dest_matrix, const Matrix *src_matrix);
void copyMatrixbyRef(Matrix **dest_matrix, Matrix **src_matrix);
Matrix *operatorMatrix(const Matrix *matrix1, const Matrix *matrix2,
                       const double (*fun)(double, double));
Matrix *createMatrix(const size_t rows, const size_t cols, const double value);
Matrix *createMatrixZeros(const size_t rows, const size_t cols);
Matrix *createMatrixOnes(const size_t rows, const size_t cols);
Matrix *createMatrixEye(const size_t rows, const size_t cols);
Matrix *createMatrixIdentity(const size_t orders);
Matrix *createMatrixArray(const size_t rows, const size_t cols,
                          const float *arr);
Matrix *createMatrixString(const char *str);
Matrix *createMatrixEmpty(const size_t rows, const size_t cols);
Matrix *createMatrixRandom(const size_t rows, const size_t cols,
                           const float leftBound, const float rightBound);
Matrix *createMatrixArange(const float start, const float stop, float step);
Matrix *createMatrixFile(const char *file_name);
Matrix *getSubMatrix(const Matrix *matrix, const size_t row_id1,
                     const size_t col_id1, const size_t row_id2,
                     const size_t col_id2);
Matrix *addMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *subtractMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *dotMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *devideMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *modMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2);
Matrix *addScalarToMatrix(const Matrix *matrix, const float value);
Matrix *subtractScalarToMatrix(const Matrix *matrix, const float value);
Matrix *multiplyScalarToMatrix(const Matrix *matrix, const float value);
Matrix *devideScalarToMatrix(const Matrix *matrix, const float value);
Matrix *modScalarToMatrix(const Matrix *matrix, const float value);
Matrix *transposeMatrix(const Matrix *matrix);
Matrix *elementProcessMatrix(Matrix *matrix, const double (*fun)(double));
Matrix *MatrixPower(Matrix *Matrix, int64_t power);
Matrix *MatrixHorizontalStack(Matrix *matrix1, Matrix *matrix2);
Matrix *MatrixVerticalStack(Matrix *matrix1, Matrix *matrix2);
Matrix *MatrixInv(Matrix *matrix);
Matrix *MatrixAbs(Matrix *matrix);
float MatrixMaxRelativeError(Matrix *matrixBase, Matrix *matrixInput);
#endif  // SRC_MATRIX_H_
