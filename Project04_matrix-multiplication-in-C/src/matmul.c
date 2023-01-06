#include "matmul.h"

#include "cblas.h"
#include "matrix.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
// #define Use_openMP
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON

#ifdef Use_openMP
#include "omp.h"
#endif

#if defined(Use_x86_SIMD_mavx2) || defined(Use_x86_SIMD_mavx512f)
#include "immintrin.h"
#else
#ifdef Use_arm_NEON
#include <arm_neon.h>
#endif
#endif

#define ALIGN_SIZE 32
Matrix *matmul_plain(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t j = 0; j < matrix2->cols; j++)
    for (size_t k = 0; k < matrix1->cols; k++)
      for (size_t i = 0; i < matrix1->rows; i++) {
        new_matrix->data[(size_t)i * matrix2->cols + j] +=
            matrix1->data[(size_t)i * matrix1->cols + k] *
            matrix2->data[(size_t)k * matrix2->cols + j];
      }
  return new_matrix;
}
Matrix *matmul_changeCycleOrder(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t i = 0; i < matrix1->rows; i++)
    for (size_t k = 0; k < matrix1->cols; k++) {
      float tmp = matrix1->data[(size_t)i * matrix1->cols + k];
      for (size_t j = 0; j < matrix2->cols; j++) {
        new_matrix->data[(size_t)i * matrix2->cols + j] +=
            tmp * matrix2->data[(size_t)k * matrix2->cols + j];
      }
    }

  return new_matrix;
}
#define MR 2
#define NR 2
void addDot(float *A, float *B, float *C, size_t k, size_t n) {
  for (size_t p = 0; p < k; p++) {
    *C += A[p] * B[(size_t)p * n];
  }
}
void addDot_MRxNR(float *A, float *B, float *C, size_t m, size_t k, size_t n,
                  size_t i, size_t j) {
  size_t max_ir, max_jr;
  if (m - i > MR)
    max_ir = MR;
  else
    max_ir = m - i;
  if (n - j > NR)
    max_jr = NR;
  else
    max_jr = n - j;
  for (size_t jr = 0; jr < max_jr; jr++) {
    for (size_t ir = 0; ir < max_ir; ir++) {
      addDot(A + (size_t)ir * k, B + jr, C + (size_t)ir * n + jr, k, n);
    }
  }
}
Matrix *matmul_blockMatrix(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t j = 0; j < matrix2->cols; j += NR)
    for (size_t i = 0; i < matrix1->rows; i += MR) {
      addDot_MRxNR(matrix1->data + (size_t)i * matrix1->cols, matrix2->data + j,
                   new_matrix->data + (size_t)i * matrix2->cols + j,
                   matrix1->rows, matrix1->cols, matrix2->cols, i, j);
    }
  return new_matrix;
}
#undef MR
#undef NR
void addDot_2x2(float *A, float *B, float *C, size_t m, size_t k, size_t n,
                size_t i, size_t j) {
  register float C00 = 0.0;
  size_t p;
  for (p = 0; p < k; p++) {
    C00 += A[p] * B[(size_t)p * n];
  }
  C[0] += C00;
  if (j + 1 < n) {
    register float C01 = 0.0;
    for (p = 0; p < k; p++) {
      C01 += A[p] * B[(size_t)p * n + 1];
    }
    C[1] += C01;
  }
  if (i + 1 < m) {
    register float C10 = 0;
    for (p = 0; p < k; p++) {
      C10 += A[k + p] * B[(size_t)p * n];
    }
    C[n] += C10;
  }
  if (i + 1 < m && j + 1 < n) {
    register float C11 = 0;
    for (p = 0; p < k; p++) {
      C11 += A[k + p] * B[(size_t)p * n + 1];
    }
    C[n + 1] += C11;
  }
}
Matrix *matmul_blockMatrix_2x2(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t j = 0; j < matrix2->cols; j += 2)
    for (size_t i = 0; i < matrix1->rows; i += 2) {
      addDot_2x2(matrix1->data + (size_t)i * matrix1->cols, matrix2->data + j,
                 new_matrix->data + (size_t)i * matrix2->cols + j,
                 matrix1->rows, matrix1->cols, matrix2->cols, i, j);
    }
  return new_matrix;
}
void addDot_4x4(float *A, float *B, float *C, size_t m, size_t k, size_t n,
                size_t i, size_t j) {
  register float C00, C01, C02, C03, C10, C11, C12, C13, C20, C21, C22, C23,
      C30, C31, C32, C33;
  register float a0p, a1p, a2p, a3p, bp0, bp1, bp2, bp3;
  size_t p;
  for (p = 0; p < k; p++) {
    a0p = A[p];
    a1p = A[k + p];
    a2p = A[2 * k + p];
    a3p = A[3 * k + p];
    bp0 = B[(size_t)p * n];
    bp1 = B[(size_t)p * n + 1];
    bp2 = B[(size_t)p * n + 2];
    bp3 = B[(size_t)p * n + 3];
    C00 += a0p * bp0;
    if (j + 1 < n) {
      C01 += a0p * bp1;
      if (j + 2 < n) {
        C02 += a0p * bp2;
        if (j + 3 < n) {
          if (j + 3 < n) C03 += a0p * bp3;
        }
      }
    }
    if (i + 1 < m) {
      C10 += a1p * bp0;
      if (j + 1 < n) {
        C11 += a1p * bp1;
        if (j + 2 < n) {
          C12 += a1p * bp2;
          if (j + 3 < n) {
            C13 += a1p * bp3;
          }
        }
      }
    }
    if (i + 2 < m) {
      C20 += a2p * bp0;
      if (j + 1 < n) {
        C21 += a2p * bp1;
        if (j + 2 < n) {
          C22 += a2p * bp2;
          if (j + 3 < n) {
            C23 += a2p * bp3;
          }
        }
      }
    }
    if (i + 3 < m) {
      C30 += a3p * bp0;
      if (j + 1 < n) {
        C31 += a3p * bp1;
        if (j + 2 < n) {
          C32 += a3p * bp2;
          if (j + 3 < n) {
            C33 += a3p * bp3;
          }
        }
      }
    }
  }
  C[0] += C00;
  if (j + 1 < n) C[1] += C01;
  if (j + 2 < n) C[2] += C02;
  if (j + 3 < n) C[3] += C03;
  if (i + 1 < m) {
    C[n] += C10;
    if (j + 1 < n) {
      C[n + 1] += C11;
      if (j + 2 < n) {
        C[n + 2] += C12;
        if (j + 3 < n) {
          C[n + 3] += C13;
        }
      }
    }
  }
  if (i + 2 < m) {
    C[2 * n] += C20;
    if (j + 1 < n) {
      C[2 * n + 1] += C21;
      if (j + 2 < n) {
        C[2 * n + 2] += C22;
        if (j + 3 < n) {
          C[2 * n + 3] += C23;
        }
      }
    }
  }
  if (i + 3 < m) {
    C[3 * n] += C30;
    if (j + 1 < n) {
      C[3 * n + 1] += C31;
      if (j + 2 < n) {
        C[3 * n + 2] += C32;
        if (j + 3 < n) {
          C[3 * n + 3] += C33;
        }
      }
    }
  }
}
Matrix *matmul_blockMatrix_4x4(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
  for (size_t j = 0; j < matrix2->cols; j += 4)
    for (size_t i = 0; i < matrix1->rows; i += 4) {
      addDot_4x4(matrix1->data + (size_t)i * matrix1->cols, matrix2->data + j,
                 new_matrix->data + (size_t)i * matrix2->cols + j,
                 matrix1->rows, matrix1->cols, matrix2->cols, i, j);
    }
  return new_matrix;
}
Matrix *_matmul_strassen(Matrix *matrixA, Matrix *matrixB) {
  size_t matrixSize = matrixA->rows;
  if (matrixSize <= 128) {
    return matmul_changeCycleOrder(matrixA, matrixB);
  }
  if (matrixSize == 1) {
    Matrix *new_matrix = createMatrixEmpty(1, 1);
    new_matrix->data[0] = matrixA->data[0] * matrixB->data[0];
    return new_matrix;
  }
  size_t subMatrixSize = matrixSize / 2;
  Matrix *A11 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *A12 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *A21 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *A22 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  copySubMatrix(A11, 1, 1, subMatrixSize, subMatrixSize, matrixA, 1, 1,
                subMatrixSize, subMatrixSize);
  copySubMatrix(A12, 1, 1, subMatrixSize, subMatrixSize, matrixA, 1,
                subMatrixSize + 1, subMatrixSize, matrixSize);
  copySubMatrix(A21, 1, 1, subMatrixSize, subMatrixSize, matrixA,
                subMatrixSize + 1, 1, matrixSize, subMatrixSize);
  copySubMatrix(A22, 1, 1, subMatrixSize, subMatrixSize, matrixA,
                subMatrixSize + 1, subMatrixSize + 1, matrixSize, matrixSize);
  Matrix *B11 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *B12 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *B21 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  Matrix *B22 = createMatrixEmpty(subMatrixSize, subMatrixSize);
  copySubMatrix(B11, 1, 1, subMatrixSize, subMatrixSize, matrixB, 1, 1,
                subMatrixSize, subMatrixSize);
  copySubMatrix(B12, 1, 1, subMatrixSize, subMatrixSize, matrixB, 1,
                subMatrixSize + 1, subMatrixSize, matrixSize);
  copySubMatrix(B21, 1, 1, subMatrixSize, subMatrixSize, matrixB,
                subMatrixSize + 1, 1, matrixSize, subMatrixSize);
  copySubMatrix(B22, 1, 1, subMatrixSize, subMatrixSize, matrixB,
                subMatrixSize + 1, subMatrixSize + 1, matrixSize, matrixSize);
  Matrix *S1 = subtractMatrix(B12, B22);
  Matrix *S2 = addMatrix(A11, A12);
  Matrix *S3 = addMatrix(A21, A22);
  Matrix *S4 = subtractMatrix(B21, B11);
  Matrix *S5 = addMatrix(A11, A22);
  Matrix *S6 = addMatrix(B11, B22);
  Matrix *S7 = subtractMatrix(A12, A22);
  Matrix *S8 = addMatrix(B21, B22);
  Matrix *S9 = subtractMatrix(A11, A21);
  Matrix *S10 = addMatrix(B11, B12);
  Matrix *P1 = _matmul_strassen(A11, S1);
  Matrix *P2 = _matmul_strassen(S2, B22);
  Matrix *P3 = _matmul_strassen(S3, B11);
  Matrix *P4 = _matmul_strassen(A22, S4);
  Matrix *P5 = _matmul_strassen(S5, S6);
  Matrix *P6 = _matmul_strassen(S7, S8);
  Matrix *P7 = _matmul_strassen(S9, S10);
  Matrix *P5_add_P4 = addMatrix(P5, P4);
  Matrix *P6_del_P2 = subtractMatrix(P6, P2);
  Matrix *C11 = addMatrix(P5_add_P4, P6_del_P2);
  Matrix *C12 = addMatrix(P1, P2);
  Matrix *C21 = addMatrix(P3, P4);
  Matrix *P5_add_P1 = addMatrix(P5, P1);
  Matrix *P3_add_P7 = addMatrix(P3, P7);
  Matrix *C22 = subtractMatrix(P5_add_P1, P3_add_P7);
  Matrix *res = createMatrixEmpty(matrixSize, matrixSize);
  copySubMatrix(res, 1, 1, subMatrixSize, subMatrixSize, C11, 1, 1,
                subMatrixSize, subMatrixSize);
  copySubMatrix(res, 1, subMatrixSize + 1, subMatrixSize, matrixSize, C12, 1, 1,
                subMatrixSize, subMatrixSize);
  copySubMatrix(res, subMatrixSize + 1, 1, matrixSize, subMatrixSize, C21, 1, 1,
                subMatrixSize, subMatrixSize);
  copySubMatrix(res, subMatrixSize + 1, subMatrixSize + 1, matrixSize,
                matrixSize, C22, 1, 1, subMatrixSize, subMatrixSize);
  deleteMatrix(&A11);
  deleteMatrix(&A12);
  deleteMatrix(&A21);
  deleteMatrix(&A22);
  deleteMatrix(&B11);
  deleteMatrix(&B12);
  deleteMatrix(&B21);
  deleteMatrix(&B22);
  deleteMatrix(&S1);
  deleteMatrix(&S2);
  deleteMatrix(&S3);
  deleteMatrix(&S4);
  deleteMatrix(&S5);
  deleteMatrix(&S6);
  deleteMatrix(&S7);
  deleteMatrix(&S8);
  deleteMatrix(&S9);
  deleteMatrix(&S10);
  deleteMatrix(&P1);
  deleteMatrix(&P2);
  deleteMatrix(&P3);
  deleteMatrix(&P4);
  deleteMatrix(&P5);
  deleteMatrix(&P6);
  deleteMatrix(&P7);
  deleteMatrix(&P5_add_P4);
  deleteMatrix(&P6_del_P2);
  deleteMatrix(&P5_add_P1);
  deleteMatrix(&P3_add_P7);
  deleteMatrix(&C11);
  deleteMatrix(&C12);
  deleteMatrix(&C21);
  deleteMatrix(&C22);
  return res;
}
Matrix *matmul_strassen(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  size_t _matrixSize = matrix1->rows;
  if (matrix1->cols > _matrixSize) _matrixSize = matrix1->cols;
  if (matrix2->cols > _matrixSize) _matrixSize = matrix2->cols;
  size_t matrixSize;
  for (matrixSize = 1; matrixSize < _matrixSize; matrixSize *= 2)
    ;
  Matrix *matrixA = createMatrixZeros(matrixSize, matrixSize);
  Matrix *matrixB = createMatrixZeros(matrixSize, matrixSize);
  for (size_t i = 0; i < matrix1->rows; i++)
    for (size_t j = 0; j < matrix1->cols; j++) {
      matrixA->data[(size_t)i * matrixSize + j] =
          matrix1->data[(size_t)i * matrix1->cols + j];
    }
  for (size_t i = 0; i < matrix2->rows; i++)
    for (size_t j = 0; j < matrix2->cols; j++) {
      matrixB->data[(size_t)i * matrixSize + j] =
          matrix2->data[(size_t)i * matrix2->cols + j];
    }
  Matrix *_res = _matmul_strassen(matrixA, matrixB);
  Matrix *new_matrix = createMatrixEmpty(matrix1->rows, matrix2->cols);
  for (size_t i = 0; i < matrix1->rows; i++)
    for (size_t j = 0; j < matrix2->cols; j++)
      new_matrix->data[(size_t)i * matrix2->cols + j] =
          _res->data[(size_t)i * matrixSize + j];
  deleteMatrix(&matrixA);
  deleteMatrix(&matrixB);
  deleteMatrix(&_res);
  return new_matrix;
}
#define NC 72
#define MC 4080
#define KC 256
#define NR 2
#define MR 2
float *_matmul_package_malloc(size_t m, size_t n, size_t size) {
  float *ptr;
  int err =
      posix_memalign((void **)&ptr, (size_t)ALIGN_SIZE, (size_t)size * m * n);
  if (err) {
    printf("_matmul_package_malloc(): -1\n");
    exit(1);
  }
  return ptr;
}
float *make_packageA(Matrix *A, size_t row1, size_t row2, size_t col1,
                     size_t col2) {
  float *pack =
      _matmul_package_malloc(row2 - row1 + 1, col2 - col1 + 1, sizeof(float));
  float *pt = pack;
  size_t i, j, ir, i2;
  for (i = row1; i <= row2; i += MR) {
    i2 = i + MR - 1;
    if (i2 > row2) i2 = row2;
    for (j = col1; j <= col2; j++) {
      for (ir = i; ir <= i2; ir++) {
        *(pt++) = A->data[(size_t)ir * A->cols + j];
      }
    }
  }
  return pack;
}
float *make_packageB(Matrix *B, size_t row1, size_t row2, size_t col1,
                     size_t col2) {
  float *pack =
      _matmul_package_malloc(row2 - row1 + 1, col2 - col1 + 1, sizeof(float));
  float *pt = pack;
  size_t i, j, jr, j2;
  for (j = col1; j <= col2; j += NR) {
    j2 = j + NR - 1;
    if (j2 > col2) j2 = col2;
    for (i = row1; i <= row2; i++) {
      for (jr = j; jr <= j2; jr++) {
        *(pt++) = B->data[(size_t)i * B->cols + jr];
      }
    }
  }
  return pack;
}
void _matmul_package_addDot_MRxNR(Matrix *C, size_t row1, size_t row2,
                                  size_t col1, size_t col2, float *packA,
                                  float *packB, size_t k) {
  size_t i, j, p, m = row2 - row1 + 1, n = col2 - col1 + 1;
  for (p = 0; p < k; p++) {
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
        C->data[C->cols * (i + row1) + j + col1] +=
            packA[(size_t)p * m + i] * packB[(size_t)p * n + j];
      }
    }
  }
}
void _matmul_package_addDot_2x2(Matrix *C, size_t row1, size_t row2,
                                size_t col1, size_t col2, float *packA,
                                float *packB, size_t k) {
  size_t i, j, p, m = row2 - row1 + 1, n = col2 - col1 + 1;
  register float c00 = C->data[C->cols * row1 + col1];
  for (p = 0; p < k; p++) {
    c00 += packA[(size_t)p * m] * packB[(size_t)p * n];
  }
  C->data[(size_t)C->cols * row1 + col1] = c00;
  if (n > 1) {
    register float c01 = C->data[(size_t)C->cols * row1 + col1 + 1];
    for (p = 0; p < k; p++) {
      c01 += packA[(size_t)p * m] * packB[(size_t)p * n + 1];
    }
    C->data[(size_t)C->cols * row1 + col1 + 1] = c01;
  }
  if (m > 1) {
    register float c10 = C->data[(size_t)C->cols * (row1 + 1) + col1];
    for (p = 0; p < k; p++) {
      c10 += packA[(size_t)p * m + 1] * packB[(size_t)p * n];
    }
    C->data[(size_t)C->cols * (row1 + 1) + col1] = c10;
  }
  if (m > 1 && n > 1) {
    float c11 = C->data[(size_t)C->cols * (row1 + 1) + col1 + 1];
    for (p = 0; p < k; p++) {
      c11 += packA[(size_t)p * m + 1] * packB[(size_t)p * n + 1];
    }
    C->data[(size_t)C->cols * (row1 + 1) + col1 + 1] = c11;
  }
}
Matrix *matmul_package(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  size_t m = matrix1->rows, k = matrix1->cols, n = matrix2->cols;
  Matrix *new_matrix = createMatrixZeros(m, n);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t jc = 0; jc < n; jc += NC) {
    size_t jc2 = jc + NC - 1;
    if (jc2 >= n) jc2 = n - 1;
    for (size_t kc = 0; kc < k; kc += KC) {
      size_t kc2 = kc + KC - 1;
      if (kc2 >= k) kc2 = k - 1;
      float *packB = make_packageB(matrix2, kc, kc2, jc, jc2);
      size_t sizeB = (kc2 - kc + 1) * (jc2 - jc + 1);
      for (size_t ic = 0; ic < m; ic += MC) {
        size_t ic2 = ic + MC - 1;
        if (ic2 >= m) ic2 = m - 1;
        float *packA = make_packageA(matrix1, ic, ic2, kc, kc2);
        size_t sizeA = (kc2 - kc + 1) * (ic2 - ic + 1);
        for (size_t pb = 0, jr = jc; pb < sizeB;
             pb += (size_t)(kc2 - kc + 1) * NR, jr += NR) {
          size_t jr2 = jr + NR - 1;
          if (jr2 > jc2) jr2 = jc2;
          for (size_t pa = 0, ir = ic; pa < sizeA;
               pa += (size_t)MR * (kc2 - kc + 1), ir += MR) {
            size_t ir2 = ir + MR - 1;
            if (ir2 > ic2) ir2 = ic2;
            // _matmul_package_addDot_MRxNR(new_matrix, ir, ir2, jr, jr2, packA
            // + pa, packB + pb, kc2 - kc + 1);
            _matmul_package_addDot_2x2(new_matrix, ir, ir2, jr, jr2, packA + pa,
                                       packB + pb, kc2 - kc + 1);
          }
        }
      }
    }
  }
  return new_matrix;
}
#undef MR
#undef NR
#undef KC
#undef MC
#undef NC

#define NC 72
#define MC 512
#define KC 4080
#define NR 16
#define MR 4
float *make_packageA_SIMD_NEON(Matrix *A, size_t row1, size_t row2, size_t col1,
                               size_t col2) {
  float *pack =
      _matmul_package_malloc(row2 - row1 + 1, col2 - col1 + 1, sizeof(float));
  float *pt = pack;
  float *ptA = A->data + (size_t)row1 * A->cols + col1;
  size_t each_add = A->cols - (col2 - col1 + 1);
  for (size_t i = row1; i <= row2; i++) {
    for (size_t j = col1; j <= col2; j++) {
      (*pt++) = *(ptA++);
    }
    ptA += each_add;
  }
  return pack;
}
float *make_packageB_SIMD_NEON(Matrix *B, size_t row1, size_t row2, size_t col1,
                               size_t col2) {
  float *pack =
      _matmul_package_malloc(row2 - row1 + 1, col2 - col1 + 1, sizeof(float));
  float *pt = pack;
  float *ptB = B->data + (size_t)row1 * B->cols + col1;
  size_t each_add = (size_t)1 - (size_t)B->cols * (row2 - row1 + 1);
  for (size_t j = col1; j <= col2; j++) {
    for (size_t i = row1; i <= row2; i++) {
      *(pt++) = *ptB;
      ptB += B->cols;
    }
    ptB += each_add;
  }
  return pack;
}
void _matmul_package_addDot_SIMD_NEON(float *dest, float *v1, float *v2,
                                      size_t len) {
#ifdef Use_x86_SIMD_mavx512f
  // use avx512: -mavx512f
  __m512 sum512 = _mm512_setzero_ps();
  size_t p;
  for (p = 0; p + 15 < len; p += 16, v1 += 16, v2 += 16) {
    sum512 = _mm512_add_ps(
        sum512, _mm512_mul_ps(_mm512_loadu_ps(v1), _mm512_loadu_ps(v2)));
  }
  *dest += _mm512_reduce_add_ps(sum512);
  for (; p < len; p++, v1++, v2++) {
    *dest += (*v1) * (*v2);
  }
#else
#ifdef Use_x86_SIMD_mavx2
  // use avx2: -mavx2
  __m256 sum256 = _mm256_setzero_ps();
  size_t p;
  for (p = 0; p + 7 < len; p += 8, v1 += 8, v2 += 8) {
    sum256 = _mm256_add_ps(
        sum256, _mm256_mul_ps(_mm256_loadu_ps(v1), _mm256_loadu_ps(v2)));
  }
  const __m128 sumQuad = _mm_add_ps(_mm256_castps256_ps128(sum256),
                                    _mm256_extractf128_ps(sum256, 1));
  const __m128 loDual = sumQuad;
  const __m128 hiDual = _mm_movehl_ps(sumQuad, sumQuad);
  const __m128 sumDual = _mm_add_ps(loDual, hiDual);
  const __m128 lo = sumDual;
  const __m128 hi = _mm_shuffle_ps(sumDual, sumDual, 0x1);
  const __m128 sum = _mm_add_ss(lo, hi);
  *dest += _mm_cvtss_f32(sum);
  for (; p < len; p++, v1++, v2++) {
    *dest += (*v1) * (*v2);
  }
#else
#ifdef Use_arm_NEON
  float32x4_t a, b;
  float32x4_t c = vdupq_n_f32(0);
  float sum[4] = {0};
  size_t p;
  for (p = 0; p + 4 < len; p += 4) {
    a = vld1q_f32(v1 + p);
    b = vld1q_f32(v2 + p);
    c = vaddq_f32(c, vmulq_f32(a, b));
  }
  vst1q_f32(sum, c);
  *dest += (sum[0] + sum[1] + sum[2] + sum[3]);
  for (; p < len; p++) {
    *dest += v1[p] * v2[p];
  }
#else
  for (size_t p = 0; p < len; p++) {
    *dest += v1[p] * v2[p];
  }
#endif
#endif
#endif
}
void _matmul_package_addDot_MRxNR_SIMD_NEON(Matrix *C, size_t row1, size_t row2,
                                            size_t col1, size_t col2,
                                            float *packA, float *packB,
                                            size_t k) {
  for (size_t i = row1; i <= row2; i++) {
    for (size_t j = col1; j <= col2; j++) {
      _matmul_package_addDot_SIMD_NEON(C->data + (size_t)C->cols * i + j,
                                       packA + (size_t)(i - row1) * k,
                                       packB + (size_t)(j - col1) * k, k);
    }
  }
}
void _matmul_package_addDot_2x2_SIMD_NEON(Matrix *C, size_t row1, size_t row2,
                                          size_t col1, size_t col2,
                                          float *packA, float *packB,
                                          size_t k) {
  size_t m = row2 - row1 + 1, n = col2 - col1 + 1;
  _matmul_package_addDot_SIMD_NEON(C->data + (size_t)C->cols * row1 + col1,
                                   packA, packB, k);
  if (n > 1)
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * row1 + col1 + 1, packA, packB + k, k);
  if (m > 1)
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * (row1 + 1) + col1, packA + k, packB, k);
  if (n > 1 && m > 1)
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * (row1 + 1) + col1 + 1, packA + k, packB + k,
        k);
}
void _matmul_package_addDot_4x4_SIMD_NEON(Matrix *C, size_t row1, size_t row2,
                                          size_t col1, size_t col2,
                                          float *packA, float *packB,
                                          size_t k) {
  size_t m = row2 - row1 + 1, n = col2 - col1 + 1;
  _matmul_package_addDot_SIMD_NEON(C->data + (size_t)C->cols * row1 + col1,
                                   packA, packB, k);
  if (n > 1) {
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * row1 + col1 + 1, packA, packB + k, k);
    if (n > 2) {
      _matmul_package_addDot_SIMD_NEON(
          C->data + (size_t)C->cols * row1 + col1 + 2, packA, packB + 2 * k, k);
      if (n > 3) {
        _matmul_package_addDot_SIMD_NEON(
            C->data + (size_t)C->cols * row1 + col1 + 3, packA, packB + 3 * k,
            k);
      }
    }
  }
  if (m > 1) {
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * (row1 + 1) + col1, packA + k, packB, k);
    if (n > 1) {
      _matmul_package_addDot_SIMD_NEON(
          C->data + (size_t)C->cols * (row1 + 1) + col1 + 1, packA + k,
          packB + k, k);
      if (n > 2) {
        _matmul_package_addDot_SIMD_NEON(
            C->data + (size_t)C->cols * (row1 + 1) + col1 + 2, packA + k,
            packB + 2 * k, k);
        if (n > 3) {
          _matmul_package_addDot_SIMD_NEON(
              C->data + (size_t)C->cols * (row1 + 1) + col1 + 3, packA + k,
              packB + 3 * k, k);
        }
      }
    }
  }
  if (m > 2) {
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * (row1 + 2) + col1, packA + 2 * k, packB, k);
    if (n > 1) {
      _matmul_package_addDot_SIMD_NEON(
          C->data + (size_t)C->cols * (row1 + 2) + col1 + 1, packA + 2 * k,
          packB + k, k);
      if (n > 2) {
        _matmul_package_addDot_SIMD_NEON(
            C->data + (size_t)C->cols * (row1 + 2) + col1 + 2, packA + 2 * k,
            packB + 2 * k, k);
        if (n > 3) {
          _matmul_package_addDot_SIMD_NEON(
              C->data + (size_t)C->cols * (row1 + 2) + col1 + 3, packA + 2 * k,
              packB + 3 * k, k);
        }
      }
    }
  }
  if (m > 3) {
    _matmul_package_addDot_SIMD_NEON(
        C->data + (size_t)C->cols * (row1 + 3) + col1, packA + 3 * k, packB, k);
    if (n > 1) {
      _matmul_package_addDot_SIMD_NEON(
          C->data + (size_t)C->cols * (row1 + 3) + col1 + 1, packA + 3 * k,
          packB + k, k);
      if (n > 2) {
        _matmul_package_addDot_SIMD_NEON(
            C->data + (size_t)C->cols * (row1 + 3) + col1 + 2, packA + 3 * k,
            packB + 2 * k, k);
        if (n > 3) {
          _matmul_package_addDot_SIMD_NEON(
              C->data + (size_t)C->cols * (row1 + 3) + col1 + 3, packA + 3 * k,
              packB + 3 * k, k);
        }
      }
    }
  }
}
Matrix *matmul_package_SIMD_NEON(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  size_t m = matrix1->rows, k = matrix1->cols, n = matrix2->cols;
  Matrix *new_matrix = createMatrixZeros(m, n);
#ifdef Use_openMP
#pragma omp parallel for schedule(dynamic)
#endif
  for (size_t jc = 0; jc < n; jc += NC) {
    size_t jc2 = jc + NC - 1;
    if (jc2 >= n) jc2 = n - 1;
    for (size_t kc = 0; kc < k; kc += KC) {
      size_t kc2 = kc + KC - 1;
      if (kc2 >= k) kc2 = k - 1;
      float *packB = make_packageB_SIMD_NEON(matrix2, kc, kc2, jc, jc2);
      size_t sizeB = (size_t)(kc2 - kc + 1) * (jc2 - jc + 1);
      for (size_t ic = 0; ic < m; ic += MC) {
        size_t ic2 = ic + MC - 1;
        if (ic2 >= m) ic2 = m - 1;
        float *packA = make_packageA_SIMD_NEON(matrix1, ic, ic2, kc, kc2);
        size_t sizeA = (size_t)(kc2 - kc + 1) * (ic2 - ic + 1);
        for (size_t jr = jc; jr <= jc2; jr += NR) {
          size_t jr2 = jr + NR - 1;
          if (jr2 > jc2) jr2 = jc2;
          size_t pb = (size_t)(kc2 - kc + 1) * NR * ((jr - jc) / NR);
          for (size_t ir = ic; ir <= ic2; ir += MR) {
            size_t pa = (size_t)(kc2 - kc + 1) * MR * ((ir - ic) / MR);
            size_t ir2 = ir + MR - 1;
            if (ir2 > ic2) ir2 = ic2;
            //_matmul_package_addDot_2x2_SIMD_NEON(new_matrix, ir, ir2, jr, jr2,
            // packA + pa, packB + pb, kc2 - kc + 1);
            _matmul_package_addDot_MRxNR_SIMD_NEON(new_matrix, ir, ir2, jr, jr2,
                                                   packA + pa, packB + pb,
                                                   kc2 - kc + 1);
            // _matmul_package_addDot_4x4_SIMD_NEON(new_matrix, ir, ir2, jr,
            // jr2, packA + pa, packB + pb, kc2 - kc + 1);
          }
        }
        free(packA);
      }
      free(packB);
    }
  }
  return new_matrix;
}
#undef MR
#undef NR
#undef KC
#undef MC
#undef NC
Matrix *matmul_plain_SIMD_NEON(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  size_t m = matrix1->rows, k = matrix1->cols, n = matrix2->cols;
  Matrix *new_matrix = createMatrixEmpty(m, n);
  for (size_t j = 0; j < n; j++) {
    float *p = _matmul_package_malloc(1, k, sizeof(float));
    for (size_t i = 0; i < k; i++) {
      p[i] = matrix2->data[(size_t)i * n + j];
    }
    for (size_t i = 0; i < m; i++) {
      _matmul_package_addDot_SIMD_NEON(new_matrix->data + (size_t)i * k + j, p,
                                       matrix1->data + (size_t)i * k, k);
    }
    free(p);
  }
  return new_matrix;
}
Matrix *matmul_improved(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  size_t matrixSize = matrix1->cols;
  if (matrix1->rows > matrixSize) matrixSize = matrix1->rows;
  if (matrix2->cols > matrixSize) matrixSize = matrix2->cols;
  if (matrixSize <= 256)
    return matmul_plain_SIMD_NEON(matrix1, matrix2);
  else
    return matmul_package_SIMD_NEON(matrix1, matrix2);
}
Matrix *matmul_openBLAS(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->cols != matrix2->rows) {
    printf("[matmul_plain] cols and rows can not match!\n");
    return NULL;
  }
  Matrix *new_matrix = createMatrixEmpty(matrix1->rows, matrix2->cols);
  cblas_sgemm(CblasRowMajor, CblasConjNoTrans, CblasNoTrans, matrix1->rows,
              matrix2->cols, matrix1->cols, 1, matrix1->data, matrix1->cols,
              matrix2->data, matrix2->cols, 0, new_matrix->data, matrix2->cols);
  return new_matrix;
}