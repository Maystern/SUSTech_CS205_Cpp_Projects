#pragma once
#include <exception>
class number_parse_error : public std::exception
{
   /*
      数字格式错误类
   */
public:
   const char *reason_; // 错误原因
   number_parse_error(const char *reason);
};
class number_calculate_error : public std::exception
{
   /*
     数值计算错误类
   */
public:
   const char *reason_; // 错误原因
   number_calculate_error(const char *reason);
};
class expression_parse_error : public std::exception
{
   /*
     表达式格式错误类
   */
public:
   const char *reason_; // 错误原因
   expression_parse_error(const char *reason);
};