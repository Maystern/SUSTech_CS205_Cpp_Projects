# SUSTech_CS205_cpp_Projects

## 课程简介
本课程是南方科技大学 SUSTech CS205 C/C++程序设计 (C/C++ Program Design) 课程，该课程包含五个项目：

- Project01 a simple calculator
- Project02 a better calculator
- Project03 a libray for matrix operations in C
- Project04 matrix multiplication in C
- Project05 a class for matrices

| 项目  | 得分 | 中位数 | 平均数 | 评价                                                     |
| --------- | -------- | -------- | -------- | ------------------------------------------------------------ |
| Project 1 | 93    | 85       | 83.95    | The report is good.                                          |
| Project 2 | 95    | 88       | 84.38    | Great work! You have worked hard and <br/>put a lot of time into the project. Hope you enjoy it. :) |
| Project 3 | 87    | 82       | 80.32    | It will be better if Matrix::rows is size_t.                 |
| Project 4 | 98    | 85       | 83.39    | Awesome!                                                     |
| Project 5 | 90    | 83       | 78.71    | 在循环里高频次调用getDataValue ()，可能很伤效率。<br/>getDataValue()里面只有一行代码，是inline，编译器可能优化掉。<br/>但最好还是只调用一次，将返回值存在一个局部变量里。. |
| Average | 92.60    | 84.60    | 82.15    | -                                                            |

## 课程成绩

| 项目         | 权重 | 得分 |
| ------------ | ---- | ---- |
| Quiz         | 5%   | 98.3 |
| Lab Exercise | 5%   | 100  |
| Project      | 65%  | 92.6 |
| Exam         | 25%  | 70   |

- Final: 88

![image-20230304011234674](https://raw.githubusercontent.com/Maystern/picbed/main/image-20230304011234674.png)

## 项目说明

### Project 1: A Simple Calculator

Implement a calculator which can multiply two numbers.

1. When you run the program as follows, it will output the expression and the result. **The two numbers should be input through the command line arguments**. If the two numbers are integers, the program will multiply them in integer format.

    ```bash
    $./mul 2 3
    2 * 3 = 6
    ```
2. If the input contains some non-integer numbers, the program will try to interpret the input as floating-point numbers.

    ```bash
    ./mul 3.1416 2
    3.1416 * 2 = 6.2832
    ./mul 3.1415 2.0e-2
    3.1415 * 0.02 = 0.062832
    ```
3. It can tell that the input is not a number.
    ```bash
    ./mul a  2
    The input cannot be interpret as numbers!
    ```
4. If you input some big integers, what will happen? Please describe some possible solutions, and try to implement them.

    ```bash
    ./mul 1234567890 1234567890
    ```
5. If you input some big floating-point numbers, what will happen? Please describe some possible solutions, and try to implement them.

    ```bash
    ./mul 1.0e200 1.0e200
    ```

6. Some others which can improve the program.

### Project 2: A Better Calculator

Please implement a much better calculator than that in Project 1. The programming language can be C or C++.

1. When you run your program and input an express in a line as follows, it can output the correct results. The operator precedence (order of operations) should be correct.
    ```
    2+3
    5
    5+2*3
    11
    ```
2. Use parentheses to enforce the priorities.
    ```
    (5+2)*3
    21
    ```
3. Variables can be defined as follows.
    ```
    x=3
    y=6
    x+2*y
    15
    ```
4. Some math functions can be supported.
    ```
    sqrt(3.0)
    1.7
    ```
5. It can support arbitrary precision.
    ```
    999999999999999999999999999.222222222 + 1.0
    1000000000000000000000000000.222222222
    ```
6. More features can be found in the calculator BC in Unix-like systems. You can visit this page for more information. https://www.gnu.org/software/bc/manual/html_mono/bc.html

7. Please use CMake to manage the source files if there are several.

8. Hosting your source code at GitHub.com is an option. You are strongly recommended to create a repository at GitHub.com to hold your source code for this project. Git is a good tool for version control. If so, you can just put a link in the report of the project, and do not need to upload the source code to Blackboard. If you do not host your source code at GitHub.com, please upload your source with your report to Blackboard.



### Project 3: A Libray for Matrix Operations in C

1. The programming language can only be C, not C++. Please save your source code into `*.c` files, and compile them using a C compiler such as gcc (not g++). Try to use Makefile or CMake to manage your source code.

2. Design a `struct` for matrices, and the `struct` should contain the data of a matrix, the number of columns, the number of rows, etc. 

3. Only `float` elements in a matrix are supported. You do not need to implement some other types.

4. Implement some functions to 
    * create a matrix, `createMatrix()`.
    * delete a matrix, `deleteMatrix()`.
    * copy a matrix (copy the data from a matrix to another), `copyMatrix()`.
    * add two matrices, `addMatrix()`.
    * subtraction of two matrices, `subtractMatrix()`
    * add a scalar to a matrix.
    * subtract a scalar from a matrix.
    * multiply a matrix with a scalar.
    * multiply two matrices.
    * find the minimal and maximal values of a matrix.
    * some other functions needed

5. The designed functions should be safe and easy to use. Suppose you are designing a library for others to use. You do not need to focus on the optimization in this project, ease of use is more important. 

### Project 4: Matrix Multiplication in C

Please implement matrix multiplication in C and try your best to improve its speed. The project is an improvement of Project 3. You can reuse the source code in Project 3, but should present your improvements and different parts in the report.


1. Implement a function `matmul_plain()` in a straightforward way using several loops as the benchmark.

2. Implement a function `matmul_improved()` using SIMD, OpenMP and other technologies to improve the speed. You can compare it with `matmul_plain(`)`. 

3. Test the performance using 16x16, 128x128, 1Kx1K, 8Kx8K and 64Kx64K matrices. You can generate some matrics with random values to test your function.

4. Compare your implementation with the matrix multiplication in OpenBLAS (https://www.openblas.net/). The results by your implementation should be the same or very similar with those by OpenBLAS. Can your implementation be as fast as OpenBLAS?

5. [Optional] Test your program on X86 and ARM platforms, and describe the differences.

### Project 5: A Class for Matrices

Please use C++ to implement a class.

1. Design a class for matrices, and the class should contain the data of a matrix and related information such the number of rows, the number of columns, the number of channels, etc.

2. The class should support different data types. It means that the matrix elements can be `unsigned char`, `short`, `int`, `float`, `double`, etc.

3. Do not use memory hard copy if a matrix object is assigned to another. Please carefully handle the memory management to avoid memory leaks and to release memory multiple times.

4. Implement some frequently used operators including but not limited to `=`, `==`, `+`, `-`, `*`, etc. Surely the matrix multiplication in Project 4 can be included.

5. Implement region of interest (ROI) to avoid memory hard copy.

6. [Optional] Test your program on X86 and ARM platforms, and describe the differences.

7. [Tip] Class `cv::Mat` is a good example for this project. https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html 





