#pragma once
#include <vector>
#include <string>
class BigNumber
{
private:
    void set_BigNumber(std::string);
public:
    BigNumber &checkCarry();
    BigNumber &checkScale(int32_t setted_scale);
    bool negative_;             // 是否为负数，是为 true 否为 false
    std::vector<int32_t> digits_;   // 所有的有效数字
    int32_t dotpos_;                // 小数点所在的位置
    void show();
    std::string to_string();
    BigNumber();
    BigNumber(std::string number);
    BigNumber(int32_t number);
};
int32_t BigNumberAbsCmp(BigNumber num1, BigNumber num2);
int32_t BigNumberCmp(BigNumber num1, BigNumber num2);
BigNumber BigNumberAbsAdd(BigNumber num1, BigNumber num2, bool negative);
BigNumber BigNumberAbsSub(BigNumber num1, BigNumber num2, bool negative);
BigNumber BigNumberAbsMul(BigNumber num1, BigNumber num2, bool negative);
BigNumber BigNumberAbsDiv(BigNumber num1, BigNumber num2, bool negative, bool isDiv);
bool operator<(BigNumber num1, BigNumber num2);
bool operator<=(BigNumber num1, BigNumber num2);
bool operator==(BigNumber num1, BigNumber num2);
bool operator!=(BigNumber num1, BigNumber num2);
bool operator>=(BigNumber num1, BigNumber num2);
bool operator>(BigNumber num1, BigNumber num2);
BigNumber operator+(BigNumber num1, BigNumber num2);
BigNumber operator+=(BigNumber &num1, BigNumber num2);
BigNumber operator-(BigNumber num1, BigNumber num2);
BigNumber operator-=(BigNumber &num1, BigNumber num2);
BigNumber operator*(BigNumber num1, BigNumber num2);
BigNumber operator*=(BigNumber &num1, BigNumber num2);
BigNumber operator/(BigNumber num1, BigNumber num2);
BigNumber operator/=(BigNumber &num1, BigNumber num2);
BigNumber operator%(BigNumber num1, BigNumber num2);
BigNumber operator%=(BigNumber &num1, BigNumber num2);
BigNumber abs(BigNumber num);
BigNumber trunc(BigNumber num);
BigNumber floor(BigNumber num);
BigNumber ceil(BigNumber num);
BigNumber sqrt(BigNumber num);
BigNumber exp(BigNumber num);
BigNumber ln(BigNumber num);
BigNumber fac(BigNumber num);
BigNumber sin(BigNumber num);
BigNumber cos(BigNumber num);
BigNumber tan(BigNumber num);
BigNumber arctan(BigNumber num);
BigNumber arccot(BigNumber num);
BigNumber arcsin(BigNumber num);
BigNumber arccos(BigNumber num);
BigNumber getpi();
BigNumber operator^(BigNumber num1, BigNumber num2);
BigNumber operator^=(BigNumber &num1, BigNumber num2);