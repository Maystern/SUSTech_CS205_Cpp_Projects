#include "matmul.h"
#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "time.h"
int main(int argc, char **argv) {
  srand(time(0));
  printf("total Test Case = %d\n", argc - 1);
  for (size_t i = 1; i < argc; i++) {
    struct timeval start, end;
    long timeuse;
    size_t matrixSize = atoi(*(argv + i));
    printf("---------------------------------------------------\n");
    printf("Case #%zd: matrixSize = %zd\n", i, matrixSize);
    Matrix *a = createMatrixRandom(matrixSize, matrixSize, -1e5, 1e5);
    Matrix *b = createMatrixRandom(matrixSize, matrixSize, -1e5, 1e5);
    Matrix *c_openblas, *c_improve;
    gettimeofday(&start, NULL);
    c_openblas = matmul_openBLAS(a, b);
    gettimeofday(&end, NULL);
    timeuse =
        1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("time of matmul_openBLAS: %.3f ms\n", timeuse / 1000.0);
    gettimeofday(&start, NULL);
    c_improve = matmul_improved(a, b);
    gettimeofday(&end, NULL);
    timeuse =
        1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("time of matmul_improve: %.3f ms\n", timeuse / 1000.0);
    printf("maximum relative error: %.2f%%\n",
           100.0 * MatrixMaxRelativeError(c_openblas, c_improve));
  }
  printf("---------------------------------------------------\n");
  return 0;
}