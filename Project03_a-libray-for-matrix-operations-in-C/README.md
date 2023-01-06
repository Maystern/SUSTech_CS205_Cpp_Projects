# SUSTech_cpp_Project03_a-libray-for-matrix-operationsin-C

- 作者：罗嘉诚 (Jiacheng Luo)
- 学号：12112910
- 参考分数：87 / 100
- 参考评语：It will be better if Matrix::rows is size_t.


## 项目描述

本项目是 SUSTech CS205 C/C++ Design 的第 3 个大作业（Project03 A Libray for Matrix Operations in C）。

项目主要使用 `C` 语言实现了一个支持 `float` 数据格式的矩阵结构体以及一些函数。

请在这里查阅 [项目报告.pdf](https://github.com/Maystern/SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C/blob/main/doc/Project3%20A%20Libray%20for%20Matrix%20Operations%20in%20C.pdf)

请在这里查阅 [项目报告.md](https://github.com/Maystern/SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C/blob/main/doc/Project3%20A%20Libray%20for%20Matrix%20Operations%20in%20C.md)

请在这里查阅 [项目要求.pdf](https://github.com/Maystern/SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C/blob/main/doc/project3.pdf)

## 如何运行 

项目推荐在 `Ubuntu` 环境下运行。

1. 使用命令 `git clone https://github.com/Maystern/SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C.git` 将项目下载到当前目录。
2. 在当前目录下执行`cd SUSTech_cpp_Project03_a-libray-for-matrix-operations-in-C` 进入项目根目录。
3. 在项目根目录执行`sh Run_Matrix.sh` 命令，该命令执行后，将在`./build`中自动使用 `cmake` 编译原代码文件，并打开位于`./build/bin`目录下的二进制可执行程序`matrix_demo`。
4. 终端中会出现一个使用该库的示例程序的执行成果，该程序在 `src` 目录下的 `main.c` 中可以查阅。
5. 如果您仅仅想获得一个动态库，请您进入 `./build/bin`目录下取用`libmatrix.so`
6. 如果您仅仅想获得一个静态库，请您修改`src` 中的`CMakeLists.txt` 将第一条语句的`ON` 更改为 `OFF`，重新进行编译后，进入 `./build/bin`目录下取用`libmatrix.a`。

