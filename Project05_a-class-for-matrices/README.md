# SUSTech_cpp_Project05_a-class-for-matrices

- Score: `90 / 100`.
- Command: `在循环里高频次调用getDataValue ()，可能很伤效率。getDataValue()里面只有一行代码，是inline，编译器可能优化掉。但最好还是只调用一次，将返回值存在一个局部变量里。`.

Please check [Project requirements](https://github.com/Maystern/SUSTech_CS205_Cpp_Projects/blob/main/Project05_a-class-for-matrices/doc/project5.pdf) here.

Please check [Project report pdf](https://github.com/Maystern/SUSTech_CS205_Cpp_Projects/blob/main/Project05_a-class-for-matrices/doc/Project%205%20A%20Class%20for%20Matrices.pdf) here.

Please check [Project report md](https://github.com/Maystern/SUSTech_CS205_Cpp_Projects/blob/main/Project05_a-class-for-matrices/doc/Project%205%20A%20Class%20for%20Matrices.md) here.

The project is recommended to run in the `Ubuntu` environment.
1. Use command `git clone https://github.com/Maystern/SUSTech_CS205_Cpp_Projects.git` to download the item into current directory.
2. In current directory, use command `cd SUSTech_CS205_Cpp_Projects/Project05_a-class-for-matrices` to access thee root directory of item.
3. Execute the `sh Run_MatrixClassTest.sh` command in the project root directory. After the command is executed, the original code file will be automatically compiled with `cmake` in `./build`, and the generated binary executable `matrixClassTest` located in the `./build/bin` directory will be moved to the project root directory.
4. You can use `./matrixClassTest`  in the item directory to run each example code.
5. Your can modify the `CMakeLists.txt` in `src` to choose whether turn on instruction set optimization or compilation optimization.
