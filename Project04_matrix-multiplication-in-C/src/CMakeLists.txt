add_definitions(-DUse_openMP)
# 不开启任何优化：请注释
# 使用多线程优化，-DUse_openMP
add_definitions(-DUse_x86_SIMD_mavx2)
add_definitions(-mavx2)
# 不开启任何优化：请注释
# 使用x86指令集mavx2优化，-DUse_x86_SIMD_mavx2，-mavx2
# 使用x86指令集mavx512f优化，-DUse_x86_SIMD_mavx512f，-mavx512f
# 使用arm指令集NEON优化，-DUse_arm_NEON
add_definitions(-O3)
# 不开启任何优化：请注释
# 使用 -O0 -O1 -O2 -O3 四级别优化
add_executable(matmulTest matmul.c matrix.c test.c)
target_link_libraries(matmulTest openblas)