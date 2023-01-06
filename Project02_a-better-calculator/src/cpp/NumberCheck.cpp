#include "../headfile/NumberCheck.hpp"
#include <cmath>
#include <string>
#include <iostream>
bool intTest(std::string num, bool sign)
{
	/*
		检测字符串num是否为整数，
		输入参数sign = false 表示对符号无限制，sign = true 表示符号必须为正号（或者0）
		返回值为true，则表示数字为满足sign限制的整数，
		返回值为false，则表示不是。
	*/
	if (num == "-" || num == "+")
		return false;
	if (num.length() == 0)
		return false;
	if (sign == true && num[0] == '-')
		return false;
	if (!(num[0] == '+' || num[0] == '-' || isdigit(num[0])))
		return false;
	for (int32_t i = 1; i < num.length(); i++)
		if (!isdigit(num[i]))
			return false;
	return true;
}
bool floatTest(std::string num)
{
	/*
		检测字符串num是否为采用常规记数法表示的小数，
		返回值为true，则表示时采用常规记数法表示的小数，
		返回值为false，则表示不是。
	*/
	if (num.length() == 0)
		return false;
	int32_t pos_dot;
	for (int32_t i = 0; i < num.length(); i++)
		if (num[i] == '.')
		{
			pos_dot = i;
			break;
		}
	std::string part1 = num.substr(0, pos_dot), part2 = num.substr(pos_dot + 1);
	return (intTest(part1, false) && intTest(part2, true));
}
int32_t numTest(std::string num)
{
	/*
		检测一个字符串 num 是否为数字，即满足如下格式：
		1. 整数：一个长整数，如-1189203，1232
		2. 小数1：整数.非负整数，如-11.123, 2.0
		3. 小数2：整数e整数，如1e-12390
		4. 小数3：小数e整数，如-1.2380192e-12830，-12.31e128301，0.190123e-1238902，0.008190238e123
		如果字符串 num 不满足上述两种格式，返回1;
		否则返回0.
	*/
	int32_t num_e = 0, pos_e = -1;
	int32_t num_dot = 0, pos_dot = -1;
	for (int32_t i = 0; i < num.length(); i++)
	{
		if (num[i] == 'e')
			num_e++, pos_e = i;
		if (num[i] == '.')
			num_dot++, pos_dot = i;
	}
	if (num_e > 1 || num_dot > 1)
		return 1;
	if (num_e == 0 && num_dot == 0 && intTest(num, false))
	{
		return 0;
	}
	if (num_e == 0 && num_dot == 1)
	{
		std::string part1 = num.substr(0, pos_dot), part2 = num.substr(pos_dot + 1);
		if (intTest(part1, false) && intTest(part2, true))
		{
			return 0;
		}
	}
	if (num_e == 1 && num_dot == 0)
	{
		std::string part1 = num.substr(0, pos_e), part2 = num.substr(pos_e + 1);
		if (intTest(part1, false) && intTest(part2, false))
		{
			return 0;
		}
	}
	if (num_e == 1 && num_dot == 1)
	{
		if (pos_e < pos_dot)
			return 1;
		std::string part1 = num.substr(0, pos_e), part2 = num.substr(pos_e + 1);
		if (floatTest(part1) && intTest(part2, false))
		{
			return 0;
		}
	}
	return 1;
}