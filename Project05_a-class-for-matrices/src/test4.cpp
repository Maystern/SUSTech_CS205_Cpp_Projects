#define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #4 for destructor and operator = : " << std::endl;
    float values[6] = {1, 2, 3, 4, 5, 6};
    Matrix<float> m0(2, 2, 1, values);
    std::cout << "m1 = " << m0 << std::endl;
    Matrix<float>m1, m2, m3;
    m1 = m2 = m3 = m0;
    std::cout << "m1 = " << m1 << std::endl;
    std::cout << "m2 = " << m2 << std::endl;
    std::cout << "m3 = " << m3 << std::endl;
    return 0;
}