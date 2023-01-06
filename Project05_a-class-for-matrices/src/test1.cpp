#define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #1 for channel = 2:" << std::endl;
    float m1_values[12] = {1.f,2.f,3.f,4.f,5.f,6.f,1.f,1.f,1.f,1.f};
    Matrix<float> m1(2, 3, 2, m1_values);
    std::cout << "m1 = " << m1 << std::endl;

    float m2_values[12] = {1.f,2.f,3.f,4.f,5.f,6.f,-1.f,-1.f,-1.f,-1.f};
    Matrix<float> m2(2, 3, 2, m2_values);
    std::cout << "m2 = " << m2 << std::endl;

    Matrix<float>m3 = m1;
    std::cout << "m3 = " << m3 << std::endl;

    Matrix<float>m4;
    std::cout << "m4_before = " << m4 << std::endl;
    m4 = m1;
    std::cout << "m4_after = " << m4 << std::endl;

    Matrix<float>m_add = m1 + m2;
    std::cout << "m1 + m2 = " << m_add << std::endl;

    Matrix<float>m_mul = m1 * ~m2;
    std::cout << "m1 * ~m2 = " << m_mul << std::endl;

    return 0;
}