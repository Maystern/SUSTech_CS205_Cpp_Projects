set(BUILD_SHARED_LIBS ON)
# 当设置为 OFF 编译成静态库 libmatrix.a
# 当设置成 ON 编译成动态库 libmatrix.so
add_library(matrix matrix.h matrix.c)
add_executable(matrix_demo main.c)
target_link_libraries(matrix_demo matrix m)