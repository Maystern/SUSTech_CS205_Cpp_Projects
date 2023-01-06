# SUSTech_cpp_Project04_matrix-multiplication-in-C

- 作者：罗嘉诚 (Jiacheng Luo)
- 学号：12112910
- 参考分数：98 / 100
- 参考评语：Awesome! 

## 项目介绍

本项目是 SUSTech CS205 C/C++ Design 的第 4 个大作业（Project04 A Matrix Multiplication in C）。

项目主要使用了 [Project3](https://github.com/Maystern/SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C) 在 `ARM` 和 `x86` 架构上实现快速矩阵乘法，并与 openBLAS 相比较，速度可以到其相同数量级。

请在这里查阅 [项目报告.pdf](https://github.com/Maystern/SUSTech_cpp_Project04_matrix-multiplication-in-C/blob/main/doc/report.pdf)

请在这里查阅 [项目报告.md](https://github.com/Maystern/SUSTech_cpp_Project04_matrix-multiplication-in-C/blob/main/doc/report.md)

请在这里查阅 [项目要求.pdf](https://github.com/Maystern/SUSTech_cpp_Project04_matrix-multiplication-in-C/blob/main/doc/project4.pdf)

可以下载所有测试得到的 [结果数据](https://github.com/Maystern/SUSTech_cpp_Project04_matrix-multiplication-in-C/blob/main/doc/cpp_data.xlsx)

## 如何运行 

项目推荐在 `Ubuntu` 环境下运行。

1. 使用命令 `git clone https://github.com/Maystern/SUSTech_cpp_Project04_matrix-multiplication-in-C.git` 将项目下载到当前目录。
2. 在当前目录下执行`cd SUSTech_cpp_Project04_matrix-multiplication-in-C` 进入项目根目录。
3. 在项目根目录执行`sh Run_Matmul.sh` 命令，该命令执行后，将在`./build`中自动使用 `cmake` 编译原代码文件，并将位于`./build/bin`目录下的生成的二进制可执行程序`matmulTest`移动至项目根目录处。
4. 您可以在项目根目录中，使用`./matmulTest matmulSizeLists` 运行所有$matmulSize \times matmulSize$ 大小的矩阵乘法，作为例子。
5. 您可以在 `src` 下的 `CMakeLists.txt` 中选择是否开启多线程优化、指令集优化、编译优化，需要重新 `build`。
