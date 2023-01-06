// #define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #5 for general matrix operators (+,-,*,T,==) andfiles iostream operators:" << std::endl;
    float A_Data[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    Matrix<float> A = Matrix(2, 4, 1, A_Data);
    std::cout << "A = " << A << std::endl;
    std::ifstream  fin("ROI_original.txt");
    Matrix<float> A_test;
    fin >> A_test;
    fin.close();
    std::cout << A_test << std::endl;

    std::ofstream ofile;
    ofile.open("out_test_5.txt");
    Matrix<float>m_mul = A * ~A_test;
    ofile << m_mul;
    ofile.close();
    std::cout << m_mul << std::endl;

    float B_Data[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    Matrix<float>B = Matrix(2, 4, 1, B_Data);
    std::cout << "B = " << B << std::endl;

    bool AB = (A == B);
    if (AB == 0) {
        std::cout << "A is NOT equal to B." << std::endl; 
    }

    Matrix<float> add = A + B;
    std::cout << "A + B = " << add << std::endl;
    Matrix<float> minus = A - B;
    std::cout << "A - B = " <<  minus << std::endl;
    Matrix<float> val_mul_matrix = 0.5f * A;
    std::cout << "0.5f * A = " << val_mul_matrix << std::endl;
    Matrix<float> matrix_mul_val = A * 0.5f;
    std::cout << "A * 0.5f = " << matrix_mul_val << std::endl;
    std::cout << "A = " << A << std::endl;
    return 0;
}