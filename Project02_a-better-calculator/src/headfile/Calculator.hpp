#pragma once
#include "BigNumber.hpp"
#include <map>
#include <stack>
#include <vector>
struct calculator
{
    int32_t variableNum;                       // 计算器中存储的变量的个数
    std::map<std::string, int32_t> variableId; // 变量名称对其值存储位置
    std::vector<BigNumber> variables;          // 存储变量的值
    calculator();
    char Procede(char a, char b);
    void show_variables();
    BigNumber getval(std::string val_str);
    char getFunctionId(std::string name);
    bool isoperator(char ch);
    BigNumber do_operation(BigNumber num1, BigNumber num2, char op);
    BigNumber do_function(BigNumber num, char op);
    BigNumber calculate(std::string expression);
    void modify_variables(std::string varName, std::string expression);
    void call(std::string statement);
};