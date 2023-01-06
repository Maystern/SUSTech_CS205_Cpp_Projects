#define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #3 for copy constructor: " << std::endl;
    float values[4] = {1, 2, 3, 4};
    Matrix<float> m1(2, 2, 1, values);
    std::cout << "m1 = " << m1 << std::endl;
    Matrix<float>m2(m1);
    std::cout << "m2 = " << m2 << std::endl;
    Matrix<float>m3 = m1;
    std::cout << "m3 = " << m3 << std::endl;
    return 0;
}