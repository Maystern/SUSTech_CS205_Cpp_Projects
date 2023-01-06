// #define _DEBUG_
// #define Use_x86_SIMD_mavx2
// #define Use_x86_SIMD_mavx512f
// #define Use_arm_NEON
#include "matrix.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
int main() {
    std::cout << "This is the test case #5 for ROI:" << std::endl;
    std::ifstream fin("ROI_original.txt");
    Matrix<float> ROI_original;
    fin >> ROI_original;
    fin.close();
    std::cout << "ROI_original = " << ROI_original << std::endl;
    ROI_original.submat(6, 9, "ROI_revised.txt");
    std::ofstream ofile("ROI_final.txt");
    ofile << ROI_original;
    ofile.close();
    std::cout << "ROI_final = " << ROI_original << std::endl;
    return 0;
}