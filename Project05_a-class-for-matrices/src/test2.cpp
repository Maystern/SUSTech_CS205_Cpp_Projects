#define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #2 for 3 constructors: " << std::endl;
    Matrix<float>m1;
    std::cout << "m1 = " << m1 << std::endl;
    Matrix<float>m2(2, 2, 1);
    std::cout << "m2 = " << m2 << std::endl;
    float values[6] = {1, 2, 3, 4, 5, 6};
    Matrix<float>m3(3, 2, 1, values);
    std::cout << "m3 = " << m3 << std::endl;
    return 0;
}