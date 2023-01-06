#include "../headfile/Calculator.hpp"
#include "../headfile/Constant.hpp"
#include "../headfile/Exception.hpp"
#include "../headfile/NumberCheck.hpp"
#include "../headfile/BigNumber.hpp"
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
char priority[10][10] = {
    {'>', '>', '<', '<', '<', '>', '>', '<', '<', '>'},
    {'>', '>', '<', '<', '<', '>', '>', '<', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '>', '<', '>'},
    {'<', '<', '<', '<', '<', '=', '0', '<', '<', '>'},
    {'>', '>', '>', '>', '0', '>', '>', '>', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '=', '<', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '>', '<', '>'},
    {'>', '>', '>', '>', '<', '>', '>', '>', '>', '>'},
    {'<', '<', '<', '<', '<', '0', '0', '<', '<', '<'}};
// 设置优先级别表，从左到右和从上到下对于的符号为：+ - * / % ( ) # ^ 函数
calculator::calculator()
{
    /*
        初始化计算器结构体，新建一个 last 变量表示上一次计算得到的值。
    */
    variableNum = 0;
    variableId.clear();
    variables.clear();
    modify_variables("last", "0");
    call("welcome");
}
char calculator::Procede(char a, char b)
{
    /*
        对两个运算符找到其优先级别关系。
    */
    int32_t i = 9, j = 9;
    switch (a)
    {
    case '+':
        i = 0;
        break;
    case '-':
        i = 1;
        break;
    case '*':
        i = 2;
        break;
    case '/':
        i = 3;
        break;
    case '(':
        i = 4;
        break;
    case ')':
        i = 5;
        break;
    case '#':
        i = 6;
        break;
    case '%':
        i = 7;
        break;
    case '^':
        i = 8;
        break;
    }
    switch (b)
    {
    case '+':
        j = 0;
        break;
    case '-':
        j = 1;
        break;
    case '*':
        j = 2;
        break;
    case '/':
        j = 3;
        break;
    case '(':
        j = 4;
        break;
    case ')':
        j = 5;
        break;
    case '#':
        j = 6;
        break;
    case '%':
        j = 7;
        break;
    case '^':
        j = 8;
        break;
    }
    return priority[i][j];
}
void calculator::show_variables()
{
    /*
        展示所有变量及它的值，用于调试信息。
    */
    for (std::map<std::string, int32_t>::iterator it = variableId.begin(); it != variableId.end(); it++)
    {
        std::cout << it->first << " : " << variables[it->second].to_string() << std::endl;
    }
}
BigNumber calculator::getval(std::string val_str)
{
    if (val_str == "PI")
    {
        return getpi();
    }
    if (val_str == "E")
    {
        return exp(1);
    }
    /*
        将表示变量或者数字的 字符串 转换为 BigNumber 数值。
    */
    bool negative = false;
    if (val_str[0] == '-')
    {
        negative = true;
    }
    if (val_str[0] == '-' || val_str[0] == '+')
    {
        val_str = val_str.substr(1);
    }
    BigNumber resval;
    if (variableId.count(val_str) != 0)
    {
        resval = variables[variableId[val_str]];
    }
    else
    {
        resval = val_str;
    }
    if (negative)
        resval *= -1;
    return resval;
}
char calculator::getFunctionId(std::string name)
{
    /*
        将 name 表示的函数名称转换为一个字母表示的单目运算符。
    */
    if (name == "sqrt")
        return 'a';
    if (name == "trunc")
        return 'b';
    if (name == "ceil")
        return 'c';
    if (name == "floor")
        return 'd';
    if (name == "exp")
        return 'e';
    if (name == "ln")
        return 'f';
    if (name == "fac")
        return 'g';
    if (name == "sin")
        return 'h';
    if (name == "cos")
        return 'i';
    if (name == "tan")
        return 'j';
    if (name == "arctan")
        return 'k';
    if (name == "arccot")
        return 'l';
    if (name == "arcsin")
        return 'm';
    if (name == "arccos")
        return 'n';
    if (name == "abs")
        return 'o';
    return 0;
}
bool calculator::isoperator(char ch)
{
    /*
        检测符号 ch 是否为运算符。
    */
    return (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == ')' || ch == '#' || ch == '^');
}
BigNumber calculator::do_operation(BigNumber num1, BigNumber num2, char op)
{
    /*
        根据给定的运算符 op 计算 num1 op num2的值。
    */
    if (op == '+')
        return num1 + num2;
    else if (op == '-')
        return num1 - num2;
    else if (op == '*')
        return num1 * num2;
    else if (op == '/')
        return num1 / num2;
    else if (op == '%')
        return num1 % num2;
    else if (op == '^')
        return num1 ^ num2;
    throw expression_parse_error("undefined OPERATOR used.");
    return 0;
}
BigNumber calculator::do_function(BigNumber num, char op)
{
    /*
        根据给定的单目运算符 op 计算 op(num) 的值。
    */
    if (op == 'a')
        return sqrt(num);
    if (op == 'b')
        return trunc(num);
    if (op == 'c')
        return ceil(num);
    if (op == 'd')
        return floor(num);
    if (op == 'e')
        return exp(num);
    if (op == 'f')
        return ln(num);
    if (op == 'g')
        return fac(num);
    if (op == 'h')
        return sin(num);
    if (op == 'i')
        return cos(num);
    if (op == 'j')
        return tan(num);
    if (op == 'k')
        return arctan(num);
    if (op == 'l')
        return arccot(num);
    if (op == 'm')
        return arcsin(num);
    if (op == 'n')
        return arccos(num);
    if (op == 'o')
        return abs(num);
    throw expression_parse_error("undefined FUNCTION called.");
}
BigNumber calculator::calculate(std::string expression)
{
    /*
        计算表达式 expression 的值。
    */
    for (int32_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == '[' || expression[i] == '{')
        {
            expression[i] = '(';
        }
        if (expression[i] == ']' || expression[i] == '}')
        {
            expression[i] = ')';
        }
    }
    std::stack<char> stack_ch;
    std::stack<BigNumber> stack_num;
    std::string nowNum = "";
    stack_ch.push('#');
    if (expression[0] == '-' || expression[0] == '+')
    {
        expression = "0" + expression;
    }
    expression += '#';
    int32_t k = 1;
    char c = expression[0];
    while (c != '#' || stack_ch.top() != '#')
    {
        std::string newNum = "";
        if (!isoperator(c) || (c == '-' && expression[k - 2] == 'e') || (c == '-' && expression[k - 2] == '(') || (c == '+' && expression[k - 2] == '('))
        {
            while (!isoperator(c) || (c == '-' && expression[k - 2] == 'e') || (c == '-' && expression[k - 2] == '(') || (c == '+' && expression[k - 2] == '('))
            {
                newNum += c;
                c = expression[k++];
            }
            char functionId = getFunctionId(newNum);
            if (functionId)
            {
                stack_ch.push(functionId);
            }
            else
            {
                try
                {
                    stack_num.push(getval(newNum));
                }
                catch (number_calculate_error &e)
                {
                    throw e;
                }
                catch (number_parse_error &e)
                {
                    throw e;
                }
                catch (std::exception &e)
                {
                    throw expression_parse_error("undefined FUNCTION or VARIALE called.");
                }
            }
        }
        else
        {
            if (stack_ch.size() == 0)
            {
                throw expression_parse_error("Expression Parsing Error.");
            }
            switch (Procede(stack_ch.top(), c))
            {
            case '0':
                throw expression_parse_error("Bracket can NOT MATCH.");
                break;
            case '<':
                stack_ch.push(c);
                c = expression[k++];
                break;
            case '=':
                stack_ch.pop();
                if (stack_ch.size() && !isoperator(stack_ch.top()))
                {
                    if (stack_num.size() == 0)
                    {
                        throw expression_parse_error("Expression Parsing Error.");
                    }
                    BigNumber x = stack_num.top();
                    stack_num.pop();
                    stack_num.push(do_function(x, stack_ch.top()));
                    stack_ch.pop();
                }
                c = expression[k++];
                break;
            case '>':
                char op = stack_ch.top();
                stack_ch.pop();
                if (stack_num.size() <= 1)
                {
                    throw expression_parse_error("Expression Parsing Error.");
                }
                BigNumber x = stack_num.top();
                stack_num.pop();
                BigNumber y = stack_num.top();
                stack_num.pop();
                stack_num.push(do_operation(y, x, op));
                break;
            }
        }
    }
    return stack_num.top();
}
void calculator::modify_variables(std::string varName, std::string expression)
{
    /*
        将变量 varName 赋值为 expression 计算出的值。
        特别地，scale 应该设置为一个[0, ongestDigitSize] 的非负整数。
    */
    if (numTest(varName) == 0)
    {
        throw expression_parse_error("Numbers can NOT be assigned as variables.");
    }
    if (varName == "PI")
    {
        throw expression_parse_error("PI is a constant and can NOT be assigned.");
    }
    if (varName == "E")
    {
        throw expression_parse_error("E is a constant and can NOT be assigned.");
    }
    if (varName == "scale")
    {
        if (expression[0] == '-')
        {
            throw expression_parse_error("The value of \"scale\" can NOT be NEGATIVE.");
        }
        for (int32_t i = 0; i < expression.size(); i++)
        {
            if (expression[i] > '9' || expression[i] < '0')
            {
                throw expression_parse_error("The value of \"scale\" MUST be a POSITIVE INTEGER.");
            }
        }
        if (expression.size() > 8)
        {
            throw expression_parse_error("The value of \"scale\" is too LARGE.");
        }
        int32_t scale_in = 0;
        for (int32_t i = 0; i < expression.length(); i++)
            scale_in = scale_in * 10 + expression[i] - '0';
        if (scale_in > longestDigitSize)
        {
            throw expression_parse_error("The value of \"scale\" is too LARGE.");
        }
        scale = scale_in;
        return;
    }
    BigNumber varval = calculate(expression);
    if (variableId.count(varName) == 0)
    {
        variableId[varName] = variableNum++;
        variables.push_back(varval);
    }
    else
    {
        variables[variableId[varName]] = varval;
    }
}
std::string statement_format(std::string statement)
{
    std::string no_blank_statement = "";
    for (int32_t i = 0; i < statement.length(); i++)
        if (statement[i] != ' ')
        {
            no_blank_statement += statement[i];
        }
    statement = no_blank_statement;
    if (statement.length() >= 2 && statement[0] == '/' && statement[1] == '/')
    {
        return "";
    }
    return statement;
}
void calculator::call(std::string statement)
{
    /*
        对于读入的每一条赋值或者计算语句 statement 进行执行。
    */
    statement = statement_format(statement);
    if (statement == "")
        return;
    if (statement == "welcome")
    {
        std::cout << R"(---------------------------------------------------------------------------------------
Welcome using this simple calculator!
This calculator is mainly for the Project02 in CS205(C/C++) course.
This calculator is much better than that in Project01.
Course Instructor: Shiqi Yu
Author: Jiacheng Luo
Version: v1.06
If you need welcome, please print "welcome" to this information again.
If you need help, please print "help" to get some information.
If you need quit, please print "quit" or "Ctrl + C" to quit.
GitHub URL: https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator.
---------------------------------------------------------------------------------------)"
                  << std::endl;
        return;
    }
    if (statement == "help")
    {
        std::cout << R"(---------------------------------------------------------------------------------------
This is the instruction to the calculator user.
Author: Jiacheng Luo
Version: v1.06
GitHub URL: https://github.com/Maystern/SUSTech_cpp_Project02_a-better-calculator.

1. Use common decimal point notation or scientific notation to represent numbers.
    [example 1-1]
    -3.14e-1
    -0.314
    1.234
    1.234
   If your numerical representation is incorrect, an error will occur.
    [example 1-2]
    1.e30.1
    An ERROR occurred while construct numbers: Entering a number in the WRONG FORMAT.
2. Some basic operators are supported: + - * / % ^
    [example 2-1]
    1 + 1
    2
    2 - 3
    -1
    3 * 4
    12
    9 / 4
    2
    9 % 4
    1
    2 ^ 10
    1024
    When the calculation is illegal or the result is too large, an error will occur.
    [example 2-2]
    1 / 0
    An ERROR occurred while calculating: Divisor can NOT be ZERO.
    1e10000000 * 1e10000000
    An ERROR occurred while calculating: The number of SIGNIFICANT DIGITS is too LARGE.
3. Use the "scale" variable to adjust the calculation precision.
    [example 3-1]
    scale = 0
    10 / 3
    3
    scale = 3
    10 / 3
    3.333
    scale = 10
    10 / 3
    3.3333333333
   The accuracy for operator "+","-","*" will not be adjusted due to the change of "scale".
    [example 3-2]
   scale = 1
   1.12 + 1.34
   2.46
   1.12 - 1.34
   -0.22
   1.12 * 1.34
   1.5008
4. Constants that can be used in the calculator are E and PI.
    [example 4-1]
    scale = 10
    E
    2.7182818283
    PI
    3.1415926535
   When trying to modify the value of a constant, an error will occur.
   [example 4-2]
   E = 2.71
   An ERROR occurred while processing expression: E is a constant and can NOT be assigned.
5. You can use variables to register the calculation results.
    [example 5-1]
    x = 1 + 1
    y = 2 * x + 1
    x + 2 * y
    12
   Any non number can be used as a variable name.
    [example 5-2]
    1__x = 1 + 1
    hi123 = 2 * 1__x + 1
    1__x + 2 * hi123
    12
   Use the default variable "last" to calculate the last calculation result.
    [example 5-3]
    1 + 1
    2
    last ^ last
    4
   When using variables when they are undefined, an error will occur.
    [example 5-4]
    2 * tmp
    An ERROR occurred while construct numbers: Entering a number in the WRONG FORMAT. 
6. Some mathematical functions will be supported: 
    [example 6-1]
    scale = 10
    trunc(3.14)
    3
    floor(-3.14)
    -4
    ceil(3.14)
    4
    sqrt(3)
    1.7320508075
    exp(3)
    20.0855369227
    ln(3)
    1.0986122496
    fac(3)
    6
    abs(-3.145)
    3.145
    sin(3)
    0.1411200081
    cos(3)
    -0.9899924962
    tan(3)
    -0.1425465431
    arcsin(0.5)
    0.5235987756
    arccos(0.5)
    1.0471975485
    arctan(0.5)
    0.4636476090
   When the function input is illegal, an error will occur.
   [example 6-2]
    sqrt(-1)
    An ERROR occurred while calculating: NEGATIVE NUMBER encountered during sqrt().
    fac(3.1)
    An ERROR occurred while calculating: FLOAT NUMBER encountered during fac().
7.Input to ignore spaces automatically. { [ is considered as ( , } ] is considered as )
    [example 7-1]
    scale = 10
    (2 + 3) * [1 + 4] * {1 / 4}
    6.2500000000
    sqrt(sqrt{sqrt[16]})
    1.4142135623
   When brackets do not match, an error will occur.
    [example 7-2]
    (1.14))
    An ERROR occurred while processing expression: Bracket can NOT MATCH.
8.Single line comments are supported.
    [example 8-1]
    x = 1
    // x = 2
    x + 1
    2

If you need help again, please print "help" to get this information again.
---------------------------------------------------------------------------------------)"
                  << std::endl;
        return;
    }
    try
    {
        int32_t posEqual = -1;
        for (int i = 0; i < statement.length(); i++)
            if (statement[i] == '=')
            {
                posEqual = i;
                break;
            }
        if (posEqual == -1)
        {
            modify_variables("last", statement);
            std::cout << getval("last").to_string() << std::endl;
        }
        else
        {
            std::string varName = statement.substr(0, posEqual);
            std::string expression = statement.substr(posEqual + 1);
            modify_variables(varName, expression);
        }
    }
    catch (number_calculate_error &e)
    {
        std::cout << "An ERROR occurred while calculating: " << e.reason_ << std::endl;
    }
    catch (number_parse_error &e)
    {
        std::cout << "An ERROR occurred while construct numbers: " << e.reason_ << std::endl;
    }
    catch (expression_parse_error &e)
    {
        std::cout << "An ERROR occurred while processing expression: " << e.reason_ << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Expression Parsing Error." << std::endl;
    }
}