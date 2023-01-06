#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <type_traits>

#include "immintrin.h"
const double eps = 1e-9;
template <class type>
class Data {
 private:
  type *data;
  size_t refcount;

 public:
  Data(size_t length);
  ~Data();
  type *getDataValue();
  void addRefCount();
  void minusRefCount();
  size_t getRefCount();
};
template <class type>
class Matrix {
 private:
  size_t rows, cols, channels, size;
  Data<type> *dataptr;
  static size_t count;
#ifdef _DEBUG_
  size_t mat_id;
#endif
 public:
  Matrix();
  Matrix(size_t rows, size_t cols, size_t channels);
  Matrix(size_t rows, size_t cols, size_t channels, const type *data);
  Matrix(const Matrix &matrix);
  ~Matrix();
  Data<type> *getDataPtr() { return dataptr; };
  size_t getRows() { return rows; };
  size_t getCols() { return cols; };
  size_t getChannels() { return channels; };
  size_t getSize() { return size; };
#ifdef _DEBUG_
  size_t getmat_id() { return mat_id; };
#endif
  type getElement(const size_t row_id, const size_t col_id,
                  const size_t channel_id);
  void setElement(const size_t row_id, const size_t col_id,
                  const size_t channel_id, type element);
  bool operator==(Matrix matrix_cmp);
  Matrix<type> &operator=(const Matrix &matrix_copy);
  Matrix<type> operator+(Matrix matrix);
  Matrix<type> operator-(Matrix matrix);
  Matrix<type> operator*(Matrix matrix);
  Matrix<type> operator~();
  Matrix<type> &submat(size_t a, size_t b, std::string fileName);
  static size_t getCount();
};
template <class type>
size_t Matrix<type>::count = 0;
template <class type>
size_t Matrix<type>::getCount() {
  return count;
}
template <class type>
Data<type>::Data(size_t length) {
  this->data = new type[length]{};
  this->refcount = 1;
}
template <class type>
Data<type>::~Data() {
  delete[] this->data;
  this->data = NULL;
}
template <class type>
type *Data<type>::getDataValue() {
  return this->data;
}
template <class type>
void Data<type>::addRefCount() {
  this->refcount++;
}
template <class type>
void Data<type>::minusRefCount() {
  this->refcount--;
}
template <class type>
size_t Data<type>::getRefCount() {
  return this->refcount;
}

template <class type>
Matrix<type>::Matrix() {
  dataptr = NULL;
  count++;
  size = 0;
#ifdef _DEBUG_
  mat_id = count;
  std::cout << "Matrix(), Matrix #" << mat_id << std::endl;
#endif
}

template <class type>
Matrix<type>::Matrix(size_t rows, size_t cols, size_t channels) {
  count++;
#ifdef _DEBUG_
  mat_id = count;
  std::cout << "Matrix<type>::Matrix(size_t rows, size_t cols, size_t "
               "channels), Matrix #"
            << mat_id << std::endl;
#endif
  this->rows = rows;
  this->cols = cols;
  this->channels = channels;
  this->size = rows * cols;
  dataptr = new Data<type>(rows * cols * channels);
  memset(dataptr->getDataValue(), 0, sizeof(type) * rows * cols * channels);
}
template <class type>
Matrix<type>::Matrix(size_t rows, size_t cols, size_t channels,
                     const type *data) {
  count++;
#ifdef _DEBUG_
  mat_id = count;
  std::cout << "Matrix(size_t rows, size_t cols, size_t channels, const type* "
               "data), Matrix #"
            << mat_id << std::endl;
#endif
  this->rows = rows;
  this->cols = cols;
  this->channels = channels;
  this->size = rows * cols;
  dataptr = new Data<type>(rows * cols * channels);
  for (size_t t = 0; t < channels; t++) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        dataptr->getDataValue()[t * size + i * cols + j] =
            data[t * size + i * cols + j];
      }
    }
  }
}
template <class type>
Matrix<type>::~Matrix() {
  count--;
#ifdef _DEBUG_
  std::cout << "~Matrix(), Matrix #" << mat_id << std::endl;
#endif
  if (dataptr == NULL) {
#ifdef _DEBUG_
    std::cout << "Matrix #" << mat_id << " data removed" << std::endl;
#endif
  }
  if (dataptr != NULL && dataptr->getRefCount() == 1) {
#ifdef _DEBUG_
    std::cout << "Matrix #" << mat_id << " data removed" << std::endl;
#endif
    delete dataptr;
    dataptr = NULL;
  }
  if (dataptr != NULL && dataptr->getRefCount() > 1) {
#ifdef _DEBUG_
    std::cout << "Matrix #" << mat_id << " ptr removed" << std::endl;
#endif
    dataptr->minusRefCount();
  }
}
template <class type>
Matrix<type> &Matrix<type>::operator=(const Matrix &mat_copy) {
#ifdef _DEBUG_
  std::cout << "Matrix<type> & Matrix<type>::operator=(const Matrix & mat_copy)"
            << std::endl;
#endif
  if (this == &mat_copy) return *this;
  if (dataptr != NULL) {
    dataptr->minusRefCount();
    delete dataptr;
  }
  rows = mat_copy.rows;
  cols = mat_copy.cols;
  size = mat_copy.size;
  channels = mat_copy.channels;
  if (mat_copy.dataptr) {
    dataptr = mat_copy.dataptr;
    dataptr->addRefCount();
  }
  return *this;
}

template <class type>
Matrix<type>::Matrix(const Matrix &matrix) {
  count++;
#ifdef _DEBUG_
  mat_id = count;
  std::cout << "Matrix<type>::Matrix(const Matrix &matrix), Matrix #" << mat_id
            << std::endl;
#endif
  rows = matrix.rows;
  cols = matrix.cols;
  size = matrix.size;
  channels = matrix.channels;
  if (matrix.dataptr) {
    dataptr = matrix.dataptr;
    dataptr->addRefCount();
  }
}
template <class type>
std::ostream &operator<<(std::ostream &os, Matrix<type> &matrix) {
  if (matrix.getSize() == 0) {
    os << "Empty Matrix";
    return os;
  }
  for (size_t t = 0; t < matrix.getChannels(); t++) {
    os << "[";
    for (size_t i = 0; i < matrix.getRows(); i++) {
      os << "[";
      for (size_t j = 0; j < matrix.getCols(); j++) {
        os << matrix.getDataPtr()->getDataValue()[t * matrix.getSize() +
                                                  i * matrix.getCols() + j];
        if (j != matrix.getCols() - 1) os << ", ";
      }
      if (i != matrix.getRows() - 1)
        os << "],";
      else
        os << "]";
    }
    if (t != matrix.getChannels() - 1)
      os << "],";
    else
      os << "]";
  }
  return os;
}

bool ParseNumber(const char *s, double *d) {
  bool bNegtiveBase, bNegtiveExp;
  int nPreZero = 0;
  const char *p;
  int sum_i = 0;
  double sum_f = 0.0;
  int sum_exp = 0;
  double sum = 0.0;
  bNegtiveBase = bNegtiveExp = false;
  if (!s) return false;
  if ('-' == *s) {
    bNegtiveBase = true;
    s++;
  }
  for (; '0' == *s; nPreZero++, s++)
    ;
  for (; *s != '.' && *s != 'e' && *s != 'E' && *s != '\0'; s++) {
    if (*s < '0' || *s > '9') {
      return false;
    }
    sum_i = sum_i * 10 + *s - '0';
  }
  if (0 == sum_i && 0 == nPreZero) return false;
  if ('.' == *s) {
    for (p = s; *p != 'e' && *p != 'E' && *p != '\0'; p++)
      ;
    if (s == p - 1) return false;
    s = p;
    p--;
    for (; *p != '.'; p--) {
      if (*p < '0' || *p > '9') return false;
      sum_f = sum_f * 0.1 + 0.1 * (*p - '0');
    }
  }
  if ('e' == *s || 'E' == *s) {
    s++;
    if ('-' == *s) {
      bNegtiveExp = true;
      s++;
    } else if ('+' == *s) {
      bNegtiveExp = false;
      s++;
    }
    nPreZero = 0;
    for (; *s != '\0'; s++) {
      if (*s < '0' || *s > '9') {
        return false;
      }
      sum_exp = sum_exp * 10 + *s - '0';
      nPreZero++;
    }
    if (0 == sum_exp && 0 == nPreZero) return false;
  }
  sum = sum_i + sum_f;
  if (bNegtiveExp) {
    while (sum_exp > 0) {
      sum /= 10;
      sum_exp--;
    }
  } else {
    while (sum_exp > 0) {
      sum *= 10;
      sum_exp--;
    }
  }
  if (bNegtiveBase) sum = -sum;
  *d = sum;
  return true;
}
template <class type>
type string_to_type(const char *str) {
  if (std::is_same<type, float>::value || std::is_same<type, double>::value) {
    double val;
    bool is_double = ParseNumber(str, &val);
    if (is_double)
      return val;
    else
      return 0;
  } else if (std::is_same<type, int>::value ||
             std::is_same<type, short>::value) {
    int val = 0, is_negtive = 1;
    const char *p = str;
    if (*p == '-')
      is_negtive = -1, p++;
    else if (*p == '+')
      p++;
    while (*p != '\0') {
      if (*p > '9' || *p < '0') return 0;
      val = val * 10 + (*p - '0');
      p++;
    }
    return val * is_negtive;
  } else if (std::is_same<type, unsigned char>::value) {
    return *str;
  } else
    return type();
}

template <class type>
std::istream &operator>>(std::istream &is, Matrix<type> &matrix) {
  std::string str;
  getline(is, str);
  str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
  if (str == "Empty Matrix") {
    matrix = Matrix<type>();
    return is;
  }
  size_t channels = 0, rows = 0, cols = 1;
  for (size_t i = 0; i < str.length() - 1; i++)
    if (str[i] == '[' && str[i + 1] == '[') channels++;
  for (size_t i = 2; i < str.length(); i++) {
    if (str[i] == ']') break;
    if (str[i] == ',') cols++;
  }
  for (size_t i = 1; i < str.length() - 1; i++) {
    if (str[i] == ']' && str[i + 1] == ']') break;
    if (str[i] == '[') rows++;
  }
  matrix = Matrix<type>(rows, cols, channels);
  type *data = matrix.getDataPtr()->getDataValue();
  for (size_t i = 0; i < str.length(); i++)
    if (str[i] != '[' && str[i] != ']' && str[i] != ',') {
      size_t j = i;
      while (j < str.length() && str[j] != '[' && str[j] != ']' &&
             str[j] != ',') {
        j++;
      }
      j--;
      *data = string_to_type<type>(str.substr(i, j - i + 1).c_str());
      data++;
      i = j;
    }
  return is;
}

template <class type>
type Matrix<type>::getElement(const size_t row_id, const size_t col_id,
                              const size_t channel_id) {
  if (row_id >= rows || col_id >= cols || channel_id >= channels) return NULL;
  return getDataPtr()
      ->getDataValue()[channel_id * size + row_id * cols + col_id];
}

template <class type>
void Matrix<type>::setElement(const size_t row_id, const size_t col_id,
                              const size_t channel_id, type element) {
  if (row_id >= rows || col_id >= cols || channel_id >= channels) return;
  getDataPtr()->getDataValue()[channel_id * size + row_id * cols + col_id] =
      element;
}

template <class type>
bool Matrix<type>::operator==(Matrix matrix_cmp) {
  if (this->rows != matrix_cmp.getRows() ||
      this->cols != matrix_cmp.getCols() ||
      this->channels != matrix_cmp.getChannels()) {
    return false;
  }
  for (size_t t = 0; t < channels; t++) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (std::is_same<type, double>::value ||
            std::is_same<type, float>::value) {
          if (abs(dataptr->getDataValue()[t * size + i * cols + j] -
                  matrix_cmp.getDataPtr()
                      ->getDataValue()[t * size + i * cols + j]) > eps)
            return false;
        } else {
          if (dataptr->getDataValue()[t * size + i * cols + j] !=
              matrix_cmp.getDataPtr()->getDataValue()[t * size + i * cols + j])
            return false;
        }
      }
    }
  }
  return true;
}

template <class type>
Matrix<type> Matrix<type>::operator+(Matrix matrix) {
  if (this->rows != matrix.getRows() || this->cols != matrix.getCols() ||
      this->channels != matrix.getChannels()) {
    return *this;
  }
  Matrix result = Matrix(rows, cols, channels);
  for (size_t t = 0; t < channels; t++) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        result.getDataPtr()->getDataValue()[t * size + i * cols + j] =
            dataptr->getDataValue()[t * size + i * cols + j] +
            matrix.getDataPtr()->getDataValue()[t * size + i * cols + j];
      }
    }
  }
  return result;
}

template <class type>
Matrix<type> Matrix<type>::operator-(Matrix matrix) {
  if (this->rows != matrix.getRows() || this->cols != matrix.getCols() ||
      this->channels != matrix.getChannels()) {
    return *this;
  }
  Matrix result = Matrix(rows, cols, channels);
  for (size_t t = 0; t < channels; t++) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        result.getDataPtr()->getDataValue()[t * size + i * cols + j] =
            dataptr->getDataValue()[t * size + i * cols + j] -
            matrix.getDataPtr()->getDataValue()[t * size + i * cols + j];
      }
    }
  }
  return result;
}

template <class type>
Matrix<type> Matrix<type>::operator~() {
  Matrix result = Matrix(cols, rows, channels);
  for (size_t t = 0; t < channels; t++) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        result.getDataPtr()->getDataValue()[t * size + j * rows + i] =
            dataptr->getDataValue()[t * size + i * cols + j];
      }
    }
  }
  return result;
}

template <class type>
Matrix<type> operator*(type num, Matrix<type> matrix) {
  Matrix<type> result =
      Matrix<type>(matrix.getRows(), matrix.getCols(), matrix.getChannels());
  for (size_t t = 0; t < matrix.getChannels(); t++) {
    for (size_t i = 0; i < matrix.getRows(); i++) {
      for (size_t j = 0; j < matrix.getCols(); j++) {
        result.getDataPtr()
            ->getDataValue()[t * matrix.getSize() + i * matrix.getCols() + j] =
            num * matrix.getDataPtr()->getDataValue()[t * matrix.getSize() +
                                                      i * matrix.getCols() + j];
      }
    }
  }
  return result;
}

template <class type>
Matrix<type> operator*(Matrix<type> matrix, type num) {
  Matrix<type> result =
      Matrix<type>(matrix.getRows(), matrix.getCols(), matrix.getChannels());
  for (size_t t = 0; t < matrix.getChannels(); t++) {
    for (size_t i = 0; i < matrix.getRows(); i++) {
      for (size_t j = 0; j < matrix.getCols(); j++) {
        result.getDataPtr()
            ->getDataValue()[t * matrix.getSize() + i * matrix.getCols() + j] =
            num * matrix.getDataPtr()->getDataValue()[t * matrix.getSize() +
                                                      i * matrix.getCols() + j];
      }
    }
  }
  return result;
}
template <class type>
void vectorMul(type *dest, type *v1, type *v2, size_t len) {
#ifdef Use_x86_SIMD_mavx512f
  // use avx512: -mavx512f
  __m512 sum512 = _mm512_setzero_ps();
  size_t p, add_each = 512 / sizeof(type);
  for (p = 0; p + add_each - 1 < len;
       p += add_each, v1 += add_each, v2 += add_each) {
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
  size_t p, add_each = 256 / sizeof(type);
  for (p = 0; p + add_each - 1 < len;
       p += add_each, v1 += add_each, v2 += add_each) {
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
  size_t p, add_each = 128 / sizeof(type);
  for (p = 0; p + add_each < len; p += add_each) {
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
template <class type>
Matrix<type> Matrix<type>::operator*(Matrix<type> matrix) {
  if (cols != matrix.getRows() || channels != matrix.getChannels()) {
    return *this;
  }
  clock_t start, end;
  start = clock();
  Matrix result = Matrix(rows, matrix.getCols(), channels);
  // i-k-j method
  for (size_t t = 0; t < result.getChannels(); t++) {
      for (size_t i = 0; i < rows; i++) {
          for (size_t k = 0; k < matrix.getRows(); k++) {
              for (size_t j = 0; j < matrix.getCols(); j++) {
                  result.getDataPtr()->getDataValue()[t * result.getSize() +
                  i * matrix.getCols() + j] += dataptr->getDataValue()[t *
                  size + i * cols + k] *
                  matrix.getDataPtr()->getDataValue()[t * matrix.getSize() +
                  k * matrix.getCols() + j];
              }
          }
      }
  }
  // type *v1 = new type[matrix.getRows()]{};
  // type *v2 = new type[matrix.getRows()]{};
  // for (size_t t = 0; t < result.getChannels(); t++) {
  //   for (size_t i = 0; i < rows; i++) {
  //     for (size_t k = 0; k <= matrix.getRows(); k++) {
  //       v1[k] = dataptr->getDataValue()[t * size + i * cols + k];
  //     }
  //     for (size_t j = 0; j < matrix.getCols(); j++) {
  //       for (size_t k = 0; k <= matrix.getRows(); k++) {
  //         v2[k] = matrix.getDataPtr()->getDataValue()[t * matrix.getSize() +
  //                                                     k * matrix.getCols() + j];
  //       }
  //       vectorMul(result.getDataPtr()->getDataValue() + t * result.getSize() +
  //                     i * matrix.getCols() + j,
  //                 v1, v2, matrix.getRows());
  //     }
  //   }
  // }
  // delete[] v1;
  // delete[] v2;
  end = clock();
  std::cout << "general i-k-j loop in x86: The time consumed for float matrix multiplication is " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
  // std::cout << "Use_x86_SIMD_mavx2: The time consumed for float matrix multiplication is " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
  return result;
}

template <class type>
Matrix<type> &Matrix<type>::submat(size_t a, size_t b, std::string fileName) {
  if (a > size || b > size) return *this;
  size_t a_row = a / cols + 1;
  size_t a_col = a % cols + 1;
  size_t b_row = b / cols + 1;
  size_t b_col = b % cols + 1;
  size_t max_row = std::max(a_row, b_row), min_row = std::min(a_row, b_row);
  size_t max_col = std::max(a_col, b_col), min_col = std::min(a_col, b_col);
  size_t size_row = max_row - min_row + 1, size_col = max_col - min_col + 1;
  std::ifstream fin(fileName);
  Matrix ROI_matrix;
  fin >> ROI_matrix;
  fin.close();
  if (size_row * size_col != ROI_matrix.getRows() * ROI_matrix.getCols()) {
    return *this;
  }
  size_t copydata_index = 0;
  type *ROI_ptr = dataptr->getDataValue();
  for (size_t i = (min_row - 1) * cols + min_col - 1;
       i <= (max_row - 1) * cols + max_col - 1; i++) {
    size_t ptr_row = i / cols + 1, ptr_col = i % cols + 1;
    if (ptr_row >= min_row && ptr_row <= max_row && ptr_col >= min_col &&
        ptr_col <= max_col) {
      *(ROI_ptr + i) = ROI_matrix.getDataPtr()->getDataValue()[copydata_index];
      copydata_index++;
    }
  }
  return *this;
}
#endif