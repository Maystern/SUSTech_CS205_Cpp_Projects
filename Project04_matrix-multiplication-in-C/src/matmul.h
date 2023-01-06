#include "matrix.h"
#ifndef SRC_MATMUL_H_
#define SRC_MATMUL_H_
Matrix *matmul_plain(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_improved(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_changeCycleOrder(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_blockMatrix(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_blockMatrix_2x2(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_blockMatrix_4x4(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_strassen(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_package(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_package_SIMD_NEON(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_openBLAS(Matrix *matrix1, Matrix *matrix2);
Matrix *matmul_plain_SIMD_NEON(Matrix *matrix1, Matrix *matrix2);
#endif  // SRC_MATMUL_H_F