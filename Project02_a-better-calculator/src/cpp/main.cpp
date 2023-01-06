#include "../headfile/BigNumber.hpp"
#include "../headfile/Constant.hpp"
#include "../headfile/Calculator.hpp"
#include "../headfile/Exception.hpp"
#include <iostream>
#include <exception>
int main()
{
    calculator calc; // 新建一个计算器
    while (true)
    {
        std::string s;
        getline(std::cin, s);
        if (s == "quit")
            break;
        // 当输入命令 quit 时候退出计算器。
        if (s != "") {
            calc.call(s);
        }
        // 使用计算器中封装的 call 方法处理每一条语句
    }
    return 0;
}