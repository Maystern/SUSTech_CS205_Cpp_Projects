/*
    Copyright 2022 SUSTech CS205 2022-Fall
    License(CC BY 4.0)
    Author: Jiacheng Luo
    This is the matrix library.
*/
#include "matrix.h"  // NOLINT

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
const int kMatrixMaxNum = 1e7;
const char *kPrintFloatFormat = "%.3f\t";
const int kErrorHandleMode = 0;
void errorProcess(char *message, char *details) {
  printf("error: [%s] %s.\n", message, details);
  if (kErrorHandleMode == 1) exit(EXIT_FAILURE);
}
void warningProcess(char *message, char *details) {
  printf("warning: [%s] %s.\n", message, details);
}
int MatrixSize(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return 0;
  }

  return matrix->rows * matrix->cols;
}
float MatrixElement(const Matrix *matrix, const int row_id, const int col_id) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return nan("");
  }

  if (row_id <= 0 || row_id > matrix->rows || col_id <= 0 ||
      col_id > matrix->cols) {
    errorProcess("Illegal Element Access",
                 "The element does not exist in the matrix");
    return nan("");
  }
  return matrix->head_pointer[(row_id - 1) * matrix->cols + col_id - 1];
}
void modifyMatrixElement(const Matrix *matrix, const int row_id,
                         const int col_id, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return;
  }

  if (row_id <= 0 || row_id > matrix->rows || col_id <= 0 ||
      col_id > matrix->cols) {
    errorProcess("Illegal Element Access",
                 "The element does not exist in the matrix");
    return;
  }
  matrix->head_pointer[(row_id - 1) * matrix->cols + col_id - 1] = value;
}
Matrix *createMatrixEmpty(const int rows, const int cols) {
  if (rows <= 0) {
    errorProcess("Illegal Matrix Definition",
                 "The number of rows is not a positive number");
    return NULL;
  } else if (cols <= 0) {
    errorProcess("Illegal Matrix Definition",
                 "The number of cols is not a positive number");
    return NULL;
  } else if (rows > kMatrixMaxNum || cols > kMatrixMaxNum ||
             (int64_t)(rows * cols) > kMatrixMaxNum) {
    errorProcess("Illegal Matrix Definition",
                 "The number of matrix elements is too large");
    return NULL;
  }

  Matrix *new_matrix = malloc(sizeof(Matrix));
  new_matrix->rows = rows;
  new_matrix->cols = cols;
  new_matrix->head_pointer = malloc(rows * cols * sizeof(float));
  return new_matrix;
}
Matrix *createMatrix(const int rows, const int cols, const double value) {
  Matrix *new_matrix = createMatrixEmpty(rows, cols);
  for (int i = 0; i < rows * cols; i++) {
    new_matrix->head_pointer[i] = value;
  }
  return new_matrix;
}
Matrix *createMatrixZeros(const int rows, const int cols) {
  return createMatrix(rows, cols, 0.0);
}
Matrix *createMatrixOnes(const int rows, const int cols) {
  return createMatrix(rows, cols, 1.0);
}
Matrix *createMatrixIdentity(const int orders) {
  return createMatrixEye(orders, orders);
}
Matrix *createMatrixEye(const int rows, const int cols) {
  Matrix *new_matrix = createMatrixZeros(rows, cols);
  for (int i = 1; i <= rows && i <= cols; i++) {
    new_matrix->head_pointer[(i - 1) * cols + i - 1] = 1;
  }
  return new_matrix;
}
Matrix *createMatrixArray(const int rows, const int cols, const float *arr) {
  Matrix *new_matrix = createMatrixZeros(rows, cols);
  for (int i = 1; i <= rows; i++)
    for (int j = 1; j <= cols; j++) {
      new_matrix->head_pointer[(i - 1) * cols + j - 1] =
          arr[(i - 1) * cols + j - 1];
    }
  return new_matrix;
}
Matrix *createMatrixRandom(const int rows, const int cols) {
  srand(time(NULL));
  Matrix *new_matrix = createMatrixEmpty(rows, cols);
  for (int i = 1; i <= rows; i++)
    for (int j = 1; j <= cols; j++) {
      new_matrix->head_pointer[(i - 1) * cols + j - 1] =
          rand() / (RAND_MAX + 1.0);
    }
  return new_matrix;
}
Matrix *createMatrixArange(const float start, const float stop, float step) {
  double max_val, min_val;
  if (start > stop) {
    max_val = start, min_val = stop;
  } else {
    max_val = stop, min_val = start;
  }
  int cnt = (max_val - min_val) / (abs(step));
  if (cnt > kMatrixMaxNum) {
    errorProcess("Illegal Matrix Definition",
                 "The number of matrix elements is too large");
    return NULL;
  }
  cnt = 0;
  for (double now_val = start; min_val <= now_val && now_val <= max_val;
       now_val += step)
    cnt++;
  Matrix *new_matrix = createMatrixZeros(1, cnt);
  int now_id = 0;
  for (double now_val = start; min_val <= now_val && now_val <= max_val;
       now_val += step) {
    new_matrix->head_pointer[now_id++] = now_val;
  }
  return new_matrix;
}
int checkFloat(const char *str, int i, int j) {
  if (i > j) return 1;
  if ((str[i] < '0' || str[i] > '9') && j - i + 1 == 1) return 0;
  if (str[i] != '-' && str[i] != '+' && (str[i] < '0' || str[i] > '9'))
    return 0;
  if (str[i] == '-' || str[i] == '+') i++;
  int dot_pos = -1;
  for (int k = i; k <= j; k++) {
    if ((str[k] < '0' || str[k] > '9') && str[k] != '.') return 0;
    if (str[k] == '.') {
      if (dot_pos != -1) return 0;
      dot_pos = k;
    }
  }
  return 1;
}
float getFloat(const char *str, int i, int j) {
  if (i > j) return 0;
  int is_negative;
  if (str[i] == '-')
    is_negative = -1;
  else
    is_negative = 1;
  if (str[i] == '-' || str[i] == '+') i++;
  int float_int = 0, float_decimal = 0, pow = 1;
  int p;
  for (p = i; p <= j; p++) {
    if (str[p] == '.') break;
    float_int = float_int * 10 + str[p] - '0';
  }
  p++;
  for (; p <= j; p++) {
    float_decimal = float_decimal * 10 + str[p] - '0';
    pow = pow * 10;
  }
  return is_negative * (float_int + 1.0 * float_decimal / (1.0 * pow));
}
Matrix *createMatrixString(const char *str) {
  int len = strlen(str), rows = 1, cols = 0, cnt = 0, last = 0;
  for (int i = 0; i < len; i++) {
    int j = i;
    while ((str[j] == ',' || str[j] == ' ' || str[j] == ';') && j < len) {
      if (str[j] == ',' && last == 0) {
        cnt++;
      } else if (str[j] == ';') {
        if (last == 0) cnt++;
        rows++;
        if (cnt > cols) cols = cnt;
        cnt = 0;
      }
      if (str[j] != ' ') last = 0;
      j++;
    }
    i = j;
    cnt++;
    while (str[j] != ',' && str[j] != ' ' && str[j] != ';' && j < len) j++;
    j--;
    if (checkFloat(str, i, j) == 0) {
      errorProcess("Illegal Matrix Definition", "Illegal element format");
      return NULL;
    }
    last = 1;
    i = j;
  }
  if (cnt > cols) cols = cnt;
  Matrix *new_matrix = createMatrixZeros(rows, cols);
  int row_id = 1, col_id = 0;
  last = 0;
  for (int i = 0; i < len; i++) {
    int j = i;
    while ((str[j] == ',' || str[j] == ' ' || str[j] == ';') && j < len) {
      if (str[j] == ',' && last == 0) {
        col_id++;
      } else if (str[j] == ';') {
        if (last == 0) col_id++;
        row_id++;
        col_id = 0;
      }
      if (str[j] != ' ') last = 0;
      j++;
    }
    i = j;
    col_id++;
    while (str[j] != ',' && str[j] != ' ' && str[j] != ';' && j < len) j++;
    j--;
    new_matrix->head_pointer[(row_id - 1) * cols + col_id - 1] =
        getFloat(str, i, j);
    last = 1;
    i = j;
  }
  return new_matrix;
}
Matrix *createMatrixFile(const char *file_name) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    warningProcess("Illegal File Access", "File does not exist");
    return NULL;
  }
  int tot = 1;
  char c;
  while (!feof(fp)) {
    c = fgetc(fp);
    if (c < 0) break;
    if (c != ' ' && c != '.' && c != '-' && c != ',' && c != '+' &&
        (c > '9' || c < '0'))
      c = ';';
    tot++;
  }
  fclose(fp);
  char *matrix_str = malloc(sizeof(char) * tot);
  int id = 0;
  fp = fopen(file_name, "r");
  while (!feof(fp)) {
    c = fgetc(fp);
    if (c < 0) break;
    if (c != ' ' && c != '.' && c != '-' && c != ',' && c != '+' &&
        (c > '9' || c < '0'))
      c = ';';
    matrix_str[id++] = c;
  }
  matrix_str[id] = '\0';
  return createMatrixString(matrix_str);
}
void printMatrixToFile(const Matrix *matrix, const char *file_name) {
  FILE *fp = fopen(file_name, "w");
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return;
  }

  for (int i = 1; i <= matrix->rows; i++) {
    for (int j = 1; j <= matrix->cols; j++)
      fprintf(fp, kPrintFloatFormat,
              matrix->head_pointer[(i - 1) * matrix->cols + j - 1]);
    if (i != matrix->rows) fprintf(fp, "\n");
  }
  fclose(fp);
}
void showMatrix(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return;
  }

  printf("MatrixSize = [%d, %d]\n", matrix->rows, matrix->cols);
  for (int i = 1; i <= matrix->rows; i++) {
    for (int j = 1; j <= matrix->cols; j++)
      printf(kPrintFloatFormat,
             matrix->head_pointer[(i - 1) * matrix->cols + j - 1]);
    printf("\n");
  }
}
void deleteMatrix(Matrix **matrix) {
  if (matrix == NULL) return;
  if (*matrix == NULL) return;
  free((*matrix)->head_pointer);
  free(*matrix);
  (*matrix) = NULL;
}
void reshapeMatrix(Matrix *matrix, const int rows, const int cols) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Reshape",
                 "Matrix does not exist or has been deleted");
    return;
  } else if (rows <= 0) {
    errorProcess("Illegal Matrix Reshape",
                 "The number of rows is not a positive number");
    return;
  } else if (cols <= 0) {
    errorProcess("Illegal Matrix Reshape",
                 "The number of cols is not a positive number");
    return;
  } else if (rows > kMatrixMaxNum || cols > kMatrixMaxNum ||
             (int64_t)(rows * cols) > kMatrixMaxNum) {
    errorProcess("Illegal Matrix Reshape",
                 "The number of matrix elements is too large");
    return;
  } else if ((int64_t)(rows * cols) != (int64_t)matrix->rows * matrix->cols) {
    errorProcess("Illegal Matrix Reshape",
                 "The number of matrix elements is different before and after "
                 "the reshape");
    return;
  }
  matrix->rows = rows;
  matrix->cols = cols;
}
void checkSubMatrix(const Matrix *matrix, const int row_id1, const int col_id1,
                    const int row_id2, const int col_id2) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Access",
                 "Matrix does not exist or has been deleted");
    return;
  }

  if (1 <= row_id1 && row_id1 <= matrix->rows && 1 <= row_id2 &&
      row_id2 <= matrix->rows && 1 <= col_id1 && col_id1 <= matrix->cols &&
      1 <= col_id2 && col_id2 <= matrix->cols && row_id1 <= row_id2 &&
      col_id1 <= col_id2)
    return;
  errorProcess("Illegal Matrix Access", "The matrix does not exist");
  return;
}
void copySubMatrix(const Matrix *dest_matrix, const int dest_row_id1,
                   const int dest_col_id1, const int dest_row_id2,
                   const int dest_col_id2, const Matrix *src_matrix,
                   const int src_row_id1, const int src_col_id1,
                   const int src_row_id2, const int src_col_id2) {
  checkSubMatrix(dest_matrix, dest_row_id1, dest_col_id1, dest_row_id2,
                 dest_col_id2);
  checkSubMatrix(src_matrix, src_row_id1, src_col_id1, src_row_id2,
                 src_col_id2);
  if (dest_row_id2 - dest_row_id1 != src_row_id2 - src_row_id1 ||
      dest_col_id2 - dest_col_id1 != src_col_id2 - src_col_id1) {
    errorProcess("Illegal Matrix Copy",
                 "Destination matrix and source matrix are different in size");
    return;
  }

  int dest_pos = (dest_row_id1 - 1) * dest_matrix->cols + dest_col_id1 - 1;
  int src_pos = (src_row_id1 - 1) * src_matrix->cols + src_col_id1 - 1;
  for (int i = 1; i <= dest_row_id2 - dest_row_id1 + 1; i++) {
    for (int j = 1; j <= dest_col_id2 - dest_col_id1 + 1; j++) {
      dest_matrix->head_pointer[dest_pos] = src_matrix->head_pointer[src_pos];
      dest_pos++;
      src_pos++;
    }
    dest_pos += dest_matrix->cols - (dest_col_id2 - dest_col_id1 + 1);
    src_pos += src_matrix->cols - (dest_col_id2 - dest_col_id1 + 1);
  }
}
void copyMatrix(const Matrix *dest_matrix, const Matrix *src_matrix) {
  copySubMatrix(dest_matrix, 1, 1, dest_matrix->rows, dest_matrix->cols,
                src_matrix, 1, 1, src_matrix->rows, src_matrix->cols);
}
void copyMatrixbyRef(Matrix **dest_matrix, Matrix **src_matrix) {
  *dest_matrix = *src_matrix;
}
Matrix *getSubMatrix(const Matrix *matrix, const int row_id1, const int col_id1,
                     const int row_id2, const int col_id2) {
  checkSubMatrix(matrix, row_id1, col_id1, row_id1, col_id2);
  Matrix *new_matrix =
      createMatrixZeros(row_id2 - row_id1 + 1, col_id2 - col_id1 + 1);
  int pos = (row_id1 - 1) * matrix->cols + col_id1 - 1;
  for (int i = 1; i <= row_id2 - row_id1 + 1; i++) {
    for (int j = 1; j <= col_id2 - col_id1 + 1; j++) {
      new_matrix->head_pointer[(i - 1) * new_matrix->cols + j - 1] =
          matrix->head_pointer[pos];
      pos++;
    }
    pos += matrix->cols - (col_id2 - col_id1 + 1);
  }
  return new_matrix;
}
Matrix *operatorMatrix(const Matrix *matrix1, const Matrix *matrix2,
                       const double (*fun)(double, double)) {
  if (matrix1 == NULL || matrix2 == NULL) {
    errorProcess("Illegal Matrix Operation",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  if (!(matrix1->rows == matrix2->rows || matrix1->rows == 1 ||
        matrix2->rows == 1) ||
      !((matrix1->cols == matrix2->cols || matrix1->cols == 1 ||
         matrix2->cols == 1))) {
    errorProcess("Illegal Matrix Operation",
                 "The two matrix sizes should match");
    return NULL;
  }
  if (!(matrix1->rows == matrix2->rows && matrix1->cols == matrix2->cols))
    warningProcess("Broadcast Matrix Operation",
                   "The broadcast mechanism is triggered due to the different "
                   "sizes of the two matrices");
  int rows, cols;
  if (matrix1->rows > matrix2->rows)
    rows = matrix1->rows;
  else
    rows = matrix2->rows;
  if (matrix1->cols > matrix2->cols)
    cols = matrix1->cols;
  else
    cols = matrix2->cols;
  Matrix *res_matrix = createMatrixZeros(rows, cols);
  Matrix *tmp_matrix1 = createMatrixZeros(rows, cols),
         *tmp_matrix2 = createMatrixZeros(rows, cols);
  if (matrix1->rows == 1 && matrix1->cols == 1) {
    float value = matrix1->head_pointer[0];
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix1->head_pointer[(i - 1) * cols + j - 1] = value;
  } else if (matrix1->rows == 1) {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix1->head_pointer[(i - 1) * cols + j - 1] =
            matrix1->head_pointer[j - 1];
  } else if (matrix1->cols == 1) {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix1->head_pointer[(i - 1) * cols + j - 1] =
            matrix1->head_pointer[i - 1];
  } else {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix1->head_pointer[(i - 1) * cols + j - 1] =
            matrix1->head_pointer[(i - 1) * cols + j - 1];
  }
  if (matrix2->rows == 1 && matrix2->cols == 1) {
    float value = matrix2->head_pointer[0];
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix2->head_pointer[(i - 1) * cols + j - 1] = value;
  } else if (matrix2->rows == 1) {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix2->head_pointer[(i - 1) * cols + j - 1] =
            matrix2->head_pointer[j - 1];
  } else if (matrix2->cols == 1) {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix2->head_pointer[(i - 1) * cols + j - 1] =
            matrix2->head_pointer[i - 1];
  } else {
    for (int i = 1; i <= rows; i++)
      for (int j = 1; j <= cols; j++)
        tmp_matrix2->head_pointer[(i - 1) * cols + j - 1] =
            matrix2->head_pointer[(i - 1) * cols + j - 1];
  }
  for (int i = 1; i <= rows; i++)
    for (int j = 1; j <= cols; j++)
      res_matrix->head_pointer[(i - 1) * cols + j - 1] =
          fun(tmp_matrix1->head_pointer[(i - 1) * cols + j - 1],
              tmp_matrix2->head_pointer[(i - 1) * cols + j - 1]);
  deleteMatrix(&tmp_matrix1);
  deleteMatrix(&tmp_matrix2);
  return res_matrix;
}
double stdMatrixElementAdd(double x, double y) { return x + y; }
double stdMatrixElementSubtract(double x, double y) { return x - y; }
double stdMatrixElementDot(double x, double y) { return x * y; }
double stdMatrixElementDevide(double x, double y) { return x / y; }
double stdMatrixElementMod(double x, double y) {
  return x - (int64_t)(x / y) * y;
}
Matrix *addMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  return operatorMatrix(matrix1, matrix2, stdMatrixElementAdd);
}
Matrix *subtractMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  return operatorMatrix(matrix1, matrix2, stdMatrixElementSubtract);
}
Matrix *dotMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  return operatorMatrix(matrix1, matrix2, stdMatrixElementDot);
}
Matrix *devideMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  return operatorMatrix(matrix1, matrix2, stdMatrixElementDevide);
}
Matrix *modMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  return operatorMatrix(matrix1, matrix2, stdMatrixElementMod);
}
Matrix *addScalarToMatrix(const Matrix *matrix, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Add a Scalar",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->rows, matrix->cols);
  copyMatrix(new_matrix, matrix);
  for (int i = 0; i < new_matrix->rows * new_matrix->cols; i++)
    new_matrix->head_pointer[i] += value;
  return new_matrix;
}
Matrix *subtractScalarToMatrix(const Matrix *matrix, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Subtract a Scalar",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->rows, matrix->cols);
  copyMatrix(new_matrix, matrix);
  for (int i = 0; i < new_matrix->rows * new_matrix->cols; i++)
    new_matrix->head_pointer[i] -= value;
  return new_matrix;
}
Matrix *multiplyScalarToMatrix(const Matrix *matrix, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix multiply a Scalar",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->rows, matrix->cols);
  copyMatrix(new_matrix, matrix);
  for (int i = 0; i < new_matrix->rows * new_matrix->cols; i++)
    new_matrix->head_pointer[i] *= value;
  return new_matrix;
}
Matrix *devideScalarToMatrix(const Matrix *matrix, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Devide a Scalar",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->rows, matrix->cols);
  copyMatrix(new_matrix, matrix);
  for (int i = 0; i < new_matrix->rows * new_matrix->cols; i++)
    new_matrix->head_pointer[i] /= value;
  return new_matrix;
}
Matrix *modScalarToMatrix(const Matrix *matrix, const float value) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Mod a Scalar",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->rows, matrix->cols);
  copyMatrix(new_matrix, matrix);
  for (int i = 0; i < new_matrix->rows * new_matrix->cols; i++)
    new_matrix->head_pointer[i] =
        new_matrix->head_pointer[i] -
        (int64_t)(new_matrix->head_pointer[i] / value) * value;
  return new_matrix;
}
Matrix *multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2) {
  if (matrix1 == NULL || matrix2 == NULL) {
    errorProcess("Illegal Matrix Multiply",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  if (matrix1->cols != matrix2->rows) {
    errorProcess("Illegal Matrix Multiply",
                 "The two multiplied matrices do not match in size and cannot "
                 "be multiplied");
    return NULL;
  }

  Matrix *res_matrix = createMatrixZeros(matrix1->rows, matrix2->cols);
  for (int i = 1; i <= res_matrix->rows; i++)
    for (int j = 1; j <= res_matrix->cols; j++) {
      double res = 0;
      for (int k = 1; k <= matrix1->cols; k++) {
        res += matrix1->head_pointer[(i - 1) * matrix1->cols + k - 1] *
               matrix2->head_pointer[(k - 1) * matrix2->cols + j - 1];
      }
      res_matrix->head_pointer[(i - 1) * res_matrix->cols + j - 1] = res;
    }
  return res_matrix;
}
float MatrixMaxElement(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Max Element Find",
                 "Matrix does not exist or has been deleted");
    return nan("");
  }

  float result = matrix->head_pointer[0];
  for (int i = 1; i < matrix->rows * matrix->cols; i++)
    if (matrix->head_pointer[i] > result) {
      result = matrix->head_pointer[i];
    }
  return result;
}
float MatrixMinElement(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Min Element Find",
                 "Matrix does not exist or has been deleted");
    return nan("");
  }

  float result = matrix->head_pointer[0];
  for (int i = 1; i < matrix->rows * matrix->cols; i++)
    if (matrix->head_pointer[i] < result) {
      result = matrix->head_pointer[i];
    }
  return result;
}
float MatrixElementSum(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Sum Find",
                 "Matrix does not exist or has been deleted");
    return nan("");
  }

  double result = 0;
  for (int i = 0; i < matrix->rows * matrix->cols; i++) {
    result += matrix->head_pointer[i];
  }
  return result;
}
Matrix *transposeMatrix(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Transpose",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  Matrix *new_matrix = createMatrixZeros(matrix->cols, matrix->rows);
  for (int i = 1; i <= matrix->rows; i++)
    for (int j = 1; j <= matrix->cols; j++) {
      new_matrix->head_pointer[(j - 1) * matrix->rows + i - 1] =
          matrix->head_pointer[(i - 1) * matrix->cols + j - 1];
    }
  return new_matrix;
}
Matrix *elementProcessMatrix(Matrix *matrix, const double (*fun)(double)) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Element Process",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  for (int i = 0; i < matrix->rows * matrix->cols; i++)
    matrix->head_pointer[i] = fun(matrix->head_pointer[i]);
  return matrix;
}
Matrix *MatrixPower(Matrix *matrix, int power) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Power",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }

  if (matrix->cols != matrix->rows) {
    errorProcess("Illegal Matrix Power",
                 "It must be a square matrix to be exponentiated");
    return NULL;
  }
  Matrix *res_matrix = createMatrixIdentity(matrix->rows);
  Matrix *my_matrix = createMatrixEmpty(matrix->rows, matrix->cols);
  copyMatrix(my_matrix, matrix);
  if (power < 0) {
    power = -power;
    Matrix *last_my_matrix = my_matrix;
    my_matrix = MatrixInv(my_matrix);
    deleteMatrix(&last_my_matrix);
  }
  while (power > 0) {
    if (power % 2 == 1) {
      Matrix *last_res_matrix = res_matrix;
      res_matrix = multiplyMatrix(res_matrix, my_matrix);
      deleteMatrix(&last_res_matrix);
    }
    power >>= 1;
    Matrix *last_my_matrix = my_matrix;
    my_matrix = multiplyMatrix(my_matrix, my_matrix);
    deleteMatrix(&last_my_matrix);
  }
  deleteMatrix(&my_matrix);
  return res_matrix;
}
float *MatrixBegin(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Begin",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  return matrix->head_pointer;
}
float *MatrixEnd(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix End",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  return &matrix->head_pointer[matrix->rows * matrix->cols - 1];
}
float **MatrixIterators(const Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Iterator",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  float **iterator = malloc(matrix->rows * matrix->cols * sizeof(float *));
  for (int i = 0; i < matrix->rows * matrix->cols; i++)
    iterator[i] = &matrix->head_pointer[i];
  return iterator;
}
Matrix *MatrixHorizontalStack(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1 == NULL || matrix2 == NULL) {
    errorProcess("Illegal Matrix Horizontal Stack",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  if (matrix1->rows != matrix2->rows) {
    errorProcess("Illegal Matrix Horizontal Stack",
                 "The number of rows of two matrices does not match");
    return NULL;
  }
  Matrix *new_matrix =
      createMatrixZeros(matrix1->rows, matrix1->cols + matrix2->cols);
  copySubMatrix(new_matrix, 1, 1, matrix1->rows, matrix1->cols, matrix1, 1, 1,
                matrix1->rows, matrix1->cols);
  copySubMatrix(new_matrix, 1, matrix1->cols + 1, matrix1->rows,
                matrix1->cols + matrix2->cols, matrix2, 1, 1, matrix2->rows,
                matrix2->cols);
  return new_matrix;
}
Matrix *MatrixVerticalStack(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1 == NULL || matrix2 == NULL) {
    errorProcess("Illegal Matrix Vertical Stack",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  if (matrix1->cols != matrix2->cols) {
    errorProcess("Illegal Matrix Vertical Stack",
                 "The number of columns of two matrices does not match");
    return NULL;
  }
  Matrix *new_matrix =
      createMatrixZeros(matrix1->rows + matrix2->rows, matrix1->cols);
  copySubMatrix(new_matrix, 1, 1, matrix1->rows, matrix1->cols, matrix1, 1, 1,
                matrix1->rows, matrix1->cols);
  copySubMatrix(new_matrix, matrix1->rows + 1, 1, matrix1->rows + matrix2->rows,
                matrix1->cols, matrix2, 1, 1, matrix2->rows, matrix2->cols);
  return new_matrix;
}
float MatrixDet(Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Determinant",
                 "Matrix does not exist or has been deleted");
    return nan("");
  }
  if (matrix->cols != matrix->rows) {
    errorProcess("Illegal Matrix Determinant",
                 "Number of row and column of two matrices does not match");
    return nan("");
  }
  int num = matrix->cols;
  if (num == 1) return matrix->head_pointer[0];
  if (num == 2)
    return matrix->head_pointer[0] * matrix->head_pointer[3] -
           matrix->head_pointer[1] * matrix->head_pointer[2];
  if (num == 3)
    return matrix->head_pointer[0] * matrix->head_pointer[4] *
               matrix->head_pointer[8] +
           matrix->head_pointer[1] * matrix->head_pointer[5] *
               matrix->head_pointer[6] +
           matrix->head_pointer[3] * matrix->head_pointer[7] *
               matrix->head_pointer[2] -
           matrix->head_pointer[0] * matrix->head_pointer[5] *
               matrix->head_pointer[7] -
           matrix->head_pointer[1] * matrix->head_pointer[3] *
               matrix->head_pointer[8] -
           matrix->head_pointer[2] * matrix->head_pointer[4] *
               matrix->head_pointer[6];
  double **data = malloc(num * sizeof(double *));
  double *pdata = malloc(num * (num + 3) * sizeof(double));
  int i, j, k;
  for (j = 0; j < num; j++) {
    data[j] = pdata + (num + 3) * j;
    for (i = 0; i < num; i++) data[j][i] = matrix->head_pointer[j * num + i];
  }
  double value = 1.0;
  for (k = 0; k < num; k++) {
    if (data[k][k] == 0) {
      for (j = k + 1; j < num; j++)
        if (data[j][k] != 0) {
          double *buff = data[k];
          data[k] = data[j];
          data[j] = buff;
          value = 0.0 - value;
          break;
        }
      if (j == num) {
        free(pdata);
        free(data);
        return 0.0;
      }
    }
    value = value * data[k][k];
    for (j = k + 1; j < num; j++) {
      double w = data[j][k] / data[k][k];
      for (int i = k + 1; i < num; i += 4) {
        data[j][i] -= w * data[k][i];
        data[j][i + 1] -= w * data[k][i + 1];
        data[j][i + 2] -= w * data[k][i + 2];
        data[j][i + 3] -= w * data[k][i + 3];
      }
    }
  }
  free(pdata);
  free(data);
  return value;
}
Matrix *MatrixInv(Matrix *matrix) {
  if (matrix == NULL) {
    errorProcess("Illegal Matrix Inverse",
                 "Matrix does not exist or has been deleted");
    return NULL;
  }
  if (matrix->cols != matrix->rows) {
    errorProcess("Illegal Matrix Inverse",
                 "Number of row and column of two matrices does not match");
    return NULL;
  }
  if (MatrixDet(matrix) == 0) {
    warningProcess("Matrix Inverse NULL",
                   "The inverse of the matrix does not exist");
    return NULL;
  }
  int len = matrix->cols;
  double **expand_matrix = malloc(sizeof(double *) * len);
  for (int i = 0; i < len; i++) {
    expand_matrix[i] = malloc(sizeof(double) * len * 2);
  }
  Matrix *new_matrix = createMatrixZeros(len, len);
  for (int i = 0; i < len; i++)
    for (int j = 0; j < len * 2; j++) {
      if (j < len) {
        expand_matrix[i][j] = matrix->head_pointer[i * len + j];
      } else {
        if (j == len + i) {
          expand_matrix[i][j] = 1;
        } else {
          expand_matrix[i][j] = 0;
        }
      }
    }
  for (int i = 0; i < len; i++) {
    if (expand_matrix[i][i] == 0) {
      int j;
      for (j = 0; j < len; j++) {
        if (expand_matrix[j][i] != 0) {
          double *tmp = expand_matrix[i];
          expand_matrix[i] = expand_matrix[j];
          expand_matrix[j] = tmp;
          break;
        }
      }
    }
  }
  for (int i = 0; i < len; i++) {
    double first_element = expand_matrix[i][i];
    for (int j = 0; j < len * 2; j++) {
      expand_matrix[i][j] /= first_element;
    }
    for (int m = 0; m < len; m++) {
      if (m == i) continue;
      double times = expand_matrix[m][i];
      for (int n = 0; n < len * 2; n++) {
        expand_matrix[m][n] -= expand_matrix[i][n] * times;
      }
    }
  }
  for (int i = 0; i < len; i++)
    for (int j = len; j < len * 2; j++)
      new_matrix->head_pointer[i * len + j - len] = expand_matrix[i][j];
  for (int w = 0; w < len; w++) free(expand_matrix[w]);
  free(expand_matrix);
  return new_matrix;
}
