# SUSTech_cpp_Project02_a-better-calculator

- 作者：罗嘉诚 (Jiacheng Luo)
- 学号：12112910
- 参考分数：95 / 100
- 参考评语：Great work! You have worked hard and put a lot of time into the project. Hope you enjoy it. :)


## 项目描述

本项目是 SUSTech CS205 C/C++ Design 的第 2 个大作业（Project02 A Better Calculator）。

项目主要实现了高精度数值型数据（即高精度小数）的计算器。

- 高精度支持：支持在`scale` 精度下的 `+ - * / % ^` 和数学函数的数值计算。
- 运算效率高： `+ - * / %` 全部采用 $O(n \log_2 n)$ 的做法，其他数学函数的效率也不低于 $O(n^2 \log_2 n)$，可以轻松对 $10^3$ 级别有效数字的数据实现快速计算。
- 多运算符和数学函数支持：项目实现了`+ - * / % ^` 运算以及 `sqrt()` （开根号）`trunc()`（截取整数）`floor()`（向下取整）`ceil()`（向上取整）`exp()` （自然指数）`ln()` （自然对数）`fac()` （阶乘）`sin()/cos()/tan()` （三角函数）`arcsin()/arccos()/arctan()` （反三角函数）等数学函数。
- 一些人性化设计：自动忽略输入表达式的所有空格、错误信息提示、多括号输入、科学记数法输入等。

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

## 计算器使用指南

### 高精度数值型数据的表示

您可以使用 `整数e整数` 的科学记数法表示高精度数值型数据，也可以使用`整数`或者`整数.非负整数`的常规表示法表示数据。

### 高精度数值型数据的精度设置

您可以使用`scale = 正整数` 的命令重新定义计算精确到小数点后的位数，`scale` 的默认值为`0`，即默认保留整数计算。

以下关于精度的特性，您应该了解：
- 在`+` `-` `*` 运算中采用全精度。
- 在`/` 运算中精确到小数点后 `scale` 位。
- `a % b` 运算的值为 `a - (a / b) * b` 的值，精度也是按照该式进行保留。
- `trunc()` `floor()` `ceil()` 三个取整函数，保留整数。
-  `sqrt()`  `exp()`  `ln()`  `fac()`  `sin()/cos()/tan()`  `arcsin()/arccos()/arctan()` 等数学函数运算中精确到小数点后 `scale` 位。


### 高精度数值型数据支持的计算

项目实现了`+ - * / % ^` 基本算术运算以及 `sqrt()` （开根号）`trunc()`（截取整数）`floor()`（向下取整）`ceil()`（向上取整）`exp()` （自然指数）`ln()` （自然对数）`fac()` （阶乘）`sin()/cos()/tan()` （三角函数）`arcsin()/arccos()/arctan()` （反三角函数）等数学函数。

### 定义高精度数值型数据变量

您可以使用 `变量名 = 表达式` 的方式定义变量，变量可以在之后的表达式运算中被使用。

### 退出计算器

在终端中输入 `quit` 或者使用 `Ctrl + C` 都可以退出计算器。

## 项目结构和文件说明

`build` 文件用来存放 `cmake` 和 `make` 命令执行后产生的二进制文件。

`doc` 文件是用来存放一些项目文档。

`src` 文件是项目的源代码，其中包含 `cpp` 和 `headfile` 两个子目录，后者是前者对应的头文件。

项目根目录下的`COPYRIGHT`是版权声明，`README.md` 是项目的说明文件，`Run_Calculator.sh` 脚本是用来快速编译并打开计算器可执行文件。

