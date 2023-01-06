#include "../headfile/Exception.hpp"
number_parse_error::number_parse_error(const char *reason) : reason_(reason){};
// 数字格式错误的输出信息
number_calculate_error::number_calculate_error(const char *reason) : reason_(reason){};
// 数值计算错误的输出信息
expression_parse_error::expression_parse_error(const char *reason) : reason_(reason){};
// 表达式格式错误的输出信息