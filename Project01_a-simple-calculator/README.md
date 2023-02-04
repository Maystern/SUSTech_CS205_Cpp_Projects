# Project1: A Simple Calculator

- 作者：罗嘉诚 (Jiacheng Luo)
- 学号：12112910
- 参考分数：93 / 100
- 参考评语：The report is good.

## 项目描述

本项目是 SUSTech CS205 C/C++ Design 的第 1 个大作业（Project1: A Simple Calculator）。

项目主要实现了高精度数值型数据（即高精度小数）的乘法计算器。

- 全精度浮点数乘法支持：使用`./mul num1 num2` 指令时，支持`num1, num2` 是浮点数，并且输出结果也为浮点数，不产生精度误差。
- 科学计数法支持：使用 `1.0e-3` 等科学计数法表示的值，可以作为输入值。
- 文件输入输出支持：使用`./mul file1 file2` 指令可以将存储于文件中的数据读入，并且计算。
- 错误判断支持：当输入数据出现问题，将打印对应的出错信息，方便调试。

您可以在这里查看项目要求：[project02要求](https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator/blob/master/doc/project2.pdf)。

您可以在这里查看我的项目pdf报告：[project02项目报告pdf](https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator/blob/master/doc/Project02%20A%20Better%20Calculator.pdf)。

您可以在这里查看我的项目md报告：[project02项目报告md](https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator/blob/master/doc/Project02%20A%20Better%20Calculator.md)。

## 如何运行

项目推荐在 `Ubuntu` 环境下运行。

1. 使用命令  `git clone https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator.git` 将项目下载到当前目录。
2. 在当前目录下执行`cd SUSTech_cpp_Project02_a-better-calculator` 进入项目根目录。
3. 在项目根目录执行`sh Run_Calculator.sh` 命令，该命令执行后，将在`./build`中自动使用 `cmake` 编译原代码文件，并打开位于`./build/bin`目录下的二进制可执行程序`calculator`。
4. 您只需要在接下去的`终端`中输入命令即可使用计算器。
5. 退出计算器，您只需要输入命令`quit` 或者 `Crtl + C` 即可。
