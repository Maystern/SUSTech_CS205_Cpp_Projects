add_definitions(-_DEBUG_)
# 不开启debug模式，请注释
add_definitions(-DUse_x86_SIMD_mavx2)
add_definitions(-mavx2)
# 不开启任何优化：请注释
# 使用x86指令集mavx2优化，-DUse_x86_SIMD_mavx2，-mavx2
# 使用x86指令集mavx512f优化，-DUse_x86_SIMD_mavx512f，-mavx512f
# 使用arm指令集NEON优化，-DUse_arm_NEON
add_definitions(-O3)
# 不开启任何优化：请注释
# 使用 -O0 -O1 -O2 -O3 四级别优化
add_executable(matrixClassTest test.cpp)