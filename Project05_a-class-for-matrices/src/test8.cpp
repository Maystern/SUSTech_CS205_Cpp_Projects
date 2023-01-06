// #define _DEBUG_
#define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
float random(float l, float r) {
    float tmp = 1.0 * rand() / RAND_MAX;
    return (r - l) * tmp + l;
}
int main(int argc, char **argv) {
    std::ofstream fout("out.txt");
    std::cout << "This is the test case #8 for matrix multiplication with optimization algorithm applied in different platforms (X86, ARM):" << std::endl;
    srand(time(0));
    printf("total Test Case = %d\n", argc - 1);
    for (int i = 1; i < argc; i++) {
        size_t matrixSize = atoi(*(argv + i));
        float *data1 = (float *) malloc(sizeof(float) * matrixSize * matrixSize);
        float *data2 = (float *) malloc(sizeof(float) * matrixSize * matrixSize);
        for (int j = 0; j < matrixSize * matrixSize; j++) {
            data1[j] = random(-1e5, 1e5);
            data2[j] = random(-1e5, 1e5);
        }
        Matrix<float> A = Matrix(matrixSize, matrixSize, 1, data1);
        Matrix<float> B = Matrix(matrixSize, matrixSize, 1, data2);
        Matrix<float> C = A * B;
        fout << C;
        free(data1);
        free(data2);
    }
    return 0;
}