# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>
# include <cmath>
const int longestSignDigit = 1e6; // 设置有效位数长度
const int decimalMeanLen = 20;    // 设置使用常规记数法输出小数时的最长字符数
const double PI = acos(-1); 	  // 设置PI的值用于快速傅里叶变换
bool intTest(std::string num, bool sign) {
	/*
	    检测字符串num是否为整数，
		输入参数sign = false 表示对符号无限制，sign = true 表示符号必须为正号（或者0）
	    返回值为true，则表示数字为满足sign限制的整数，
		返回值为false，则表示不是。
	*/
	if (num == "-" || num == "+") return false;
	if (num.length() == 0) return false;
	if (sign == true && num[0] == '-') return false;
	if (!(num[0] == '+' || num[0] == '-' || isdigit(num[0]))) return false;
	for (int i = 1; i < num.length(); i++)
		if (!isdigit(num[i])) return false;
	return true;
}
bool floatTest(std::string num) {
	/*
	    检测字符串num是否为采用常规记数法表示的小数，
	    返回值为true，则表示时采用常规记数法表示的小数，
		返回值为false，则表示不是。
	*/
	if (num.length() == 0) return false;
	int pos_dot;
	for (int i = 0; i < num.length(); i++)
		if (num[i] == '.') {
			pos_dot = i;
			break;
		}
	std::string part1 = num.substr(0, pos_dot), part2 = num.substr(pos_dot + 1);
	return (intTest(part1, false) && intTest(part2, true));
}
int signDigitTest(std::string num, int pos_e) {
	/*
	    检测大实数num的有效位数是否大于设定的最长有效位数长度longestSignDigit
		如果 num 的有效位数大于longestSignDigit的值则返回2, 否则返回0
	*/
	if (pos_e == -1) pos_e = num.length();
	int signDigit = 0, staPos = -1;
	for (int i = 0; i < pos_e; i++) {
		if (num[i] >= '1' && num[i] <= '9') {
			staPos = i;
			break;
		}
	}
	if (staPos == -1) return 0;
	for (int i = staPos; i < pos_e; i++)
		if (num[i] >= '0' && num[i] <= '9')
			signDigit++;
	if (signDigit > longestSignDigit) return 2;
	return 0;
}
int numTest(std::string num) {
	/*
	    检测一个字符串 num 是否为数字，即满足如下格式：
	    1. 整数：一个长整数，如-1189203，1232
	    2. 小数1：整数.非负整数，如-11.123, 2.0
	    3. 小数2：整数e整数，如1e-12390
	    4. 小数3：小数e整数，如-1.2380192e-12830，-12.31e128301，0.190123e-1238902，0.008190238e123
	    如果字符串 num 不满足上述两种格式，返回1;
	    如果字符串 num 表示的数字有效位数大于longestSignDigit，返回2。
	    否则返回0.
	*/
	int num_e = 0, pos_e = -1;
	int num_dot = 0, pos_dot = -1;
	for (int i = 0; i < num.length(); i++) {
		if (num[i] == 'e') num_e++, pos_e = i;
		if (num[i] == '.') num_dot++, pos_dot = i;
	}
	if (num_e > 1 || num_dot > 1) return 1;
	if (num_e == 0 && num_dot == 0 && intTest(num, false)) {
		return signDigitTest(num, pos_e);
	}
	if (num_e == 0 && num_dot == 1) {
		std::string part1 = num.substr(0, pos_dot), part2 = num.substr(pos_dot + 1);
		if (intTest(part1, false) && intTest(part2, true)) {
			return signDigitTest(num, pos_e);
		}
	}
	if (num_e == 1 && num_dot == 0) {
		std::string part1 = num.substr(0, pos_e), part2 = num.substr(pos_e + 1);
		if (intTest(part1, false) && intTest(part2, false)) {
			return signDigitTest(num, pos_e);
		}
	}
	if (num_e == 1 && num_dot == 1) {
		std::string part1 = num.substr(0, pos_e), part2 = num.substr(pos_e + 1);
		if (floatTest(part1) && intTest(part2, false)) {
			return signDigitTest(num, pos_e);
		}
	}
	return 1;
}
std::string loadFileData(char *numFile) {
	/*
		将字符串实数信息（如果检测到是可以打开的文件名，读出文件中的所有值作为返回值； 否则则直接返回这个数字）转换为string类型。
	*/
	std::string fileName = numFile, num_str = "";
	if (FILE *file = fopen(fileName.c_str(), "r")) {
		char ch;
		while (!feof(file)) {
			ch = fgetc(file);
			num_str += ch;
		}
		fclose(file);
		int endNumPos = 0;
		for (int i = 0; i < num_str.length(); i++)
			if (isdigit(num_str[i])) endNumPos = i;
		num_str = num_str.substr(0, endNumPos + 1);
	} else {
		num_str = numFile;
	}
	return num_str;
}
int fileTest(char *numFile) {
	/*
	    检测字符数组 file 表示文件是否存在，其内容是否为合法的数字：
	    1. 若 file 表示文件不存在：返回1。
	    2. 若 file 文件中的内容不是数字：返回1。
	    3. 若 file 文件中的数字有效位数大于longestSignDigit：返回2。
	    4. 若 file 文件存在且其内容是合法的数字：返回0。
	*/
	std::string fileName = numFile, num_str = "";
	if (FILE *file = fopen(fileName.c_str(), "r")) {
		char ch;
		while (!feof(file)) {
			ch = fgetc(file);
			num_str += ch;
		}
		fclose(file);
		int endNumPos = 0;
		for (int i = 0; i < num_str.length(); i++)
			if (isdigit(num_str[i])) endNumPos = i;
		num_str = num_str.substr(0, endNumPos + 1);
	} else {
		num_str = numFile;
	}
	return numTest(num_str);
}
int paramTest(int argc, char *argv[]) {
	/*
	    本函数实现参数合法性检测：
	    1. 输入参数过多：返回1
	    2. 输入参数过少：返回2
	    3. 输入参数格式错误，不为数字或者可打开的文件：返回3
	    4. 输入数据的有效位数大于longestSignDigit，返回4
	    5. 输入数据为文件名"result.txt"，返回5
	*/
	if (argc > 3) return 1;
	if (argc < 3) return 2;
	for (int i = 1; i < argc; i++) {
		if ((std::string) argv[i] == "result.txt") return 5;
		int fileState = fileTest(argv[i]);
		if (fileState == 0) continue;
		if (fileState == 1) return 3;
		if (fileState == 2) return 4;
	}
	return 0;
}
struct bigInt {
	/*
		实现一个有符号大整数类 bigInt，支持加、乘操作。
	*/
	bool sign; // 大整数的符号，sign = true 表示该整数为负数，sign = false 表示该整数的0或者负数
	std::vector<int>num; // 大整数的有效值
	bigInt& checkCarry() {
		/*
		    检查进位、去除前导0，返回bigInt本身
			请注意，0在此处表示为 +0
		*/
		while (!num.empty() && !num.back()) num.pop_back();
		if (num.empty()) {
			sign = 0;
			num.push_back(0);
			return *this;
		}
		for (int i = 1; i < num.size(); i++) {
			num[i] += num[i - 1] / 10;
			num[i - 1] %= 10;
		}
		while (num.back() >= 10) {
			num.push_back(num.back()/10);
			num[num.size() - 2] %= 10;
		}
		return *this;
	}
	void clear() {
		/*
			清除大整数本身并释放空间。
		*/
		sign = 0;
		std::vector<int>().swap(num);
	}
	void setNumber(long long number) {
		/*
			将该大整数的值设为 long long 数 number的值。
		*/
		clear();
		if (number == 0) {
			sign = 0;
			num.push_back(0);
			return;
		}
		if (number < 0ll)
			sign = 1, number = -number;
		else
			sign = 0;
		while (number > 0) {
			num.push_back(number % 10);
			number /= 10;
		}
		checkCarry();
	}
	void setNumber(std::string number) {
		/*
			将该大整数的值设为 string 数 number的值。
		*/
		clear();
		if (number[0] != '-' && number[0] != '+') number = "+" + number;
		if (number[0] == '-') sign = 1;
		else sign = 0;
		for (int i = 1; i < number.size(); i++) {
			num.push_back(number[i] - '0');
		}
		reverse(num.begin(), num.end());
		checkCarry();
	}
	bigInt(long long number) {
		/*
			构造该大整数的值为 long long 数 number的值
		*/
		setNumber(number);
	}
	bigInt(std::string number) {
		/*
			构造该大整数的值为 string 数 number的值
		*/
		setNumber(number);
	}
	std::string to_string() {
		/*
			以string类型格式将表示的整数返回
		*/
		std::string tmp = "";
		for (int i = 0; i < num.size(); i++)
			tmp += num[i] + '0';
		reverse(tmp.begin(), tmp.end());
		if (sign) tmp = "-" + tmp;
		return tmp;
	}
};
int absCmp(const bigInt &a, const bigInt &b) {
	/*
	    比较两个bigInt的绝对值的大小:
	    1. |a| < |b| 返回 -1
	    2. |a| = |b| 返回 0
	    3. |a| > |b| 返回 1
	*/
	if (a.num.size() > b.num.size()) return 1;
	if (a.num.size() < b.num.size()) return -1;
	for (int i = (int) a.num.size() - 1; i >= 0; i--) {
		if (a.num[i] > b.num[i]) return 1;
		if (a.num[i] < b.num[i]) return -1;
	}
	return 0;
}
bigInt absSub(bigInt a, bigInt b) {
	/*
	    求两个bigInt绝对值差的绝对值，即 ||a| - |b||
	*/
	if (absCmp(a, b) < 0) std::swap(a, b);
	for (int i = 0; i < b.num.size(); a.num[i] -= b.num[i], i++)
		if (a.num[i] < b.num[i]) {
			int j = i + 1;
			while (!a.num[j]) j++;
			while (j > i) {
				--a.num[j];
				a.num[--j] += 10;
			}
		}
	return a.checkCarry();
}
struct complex {
	/*
		手动实现一个复数类，支持复数加减乘三种操作。
	*/
	double r; // 表示复数的实部
	double i; // 表示复数的虚部
	complex() { }
	complex(double x, double y) {
		r = x;
		i = y;
	}
	inline complex operator *(const complex&x)const {
		return complex(r*x.r - i*x.i,r*x.i + i*x.r );
	}
	inline void operator *=(const complex&x) {
		*this = *this * x;
	}
	inline complex operator +(const complex&x)const {
		return complex(r + x.r,i + x.i);
	}
	inline complex operator -(const complex&x)const {
		return complex(r - x.r,i - x.i);
	}
};
void FFT(std::vector<complex> &y, int len, int on) {
	/*
		快速傅里叶变换，用于实现快速乘法。
	*/
	for (int i = 1, j = len / 2; i < len - 1; i++) {
		if (i < j) std::swap(y[i], y[j]);
		int k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
	for (int h = 2; h <= len; h <<= 1) {
		complex wn(cos(-on * 2.0 * PI / h), sin(-on * 2.0 * PI / h));
		for (int j = 0; j < len; j += h) {
			complex w(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				complex u = y[k];
				complex t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w *= wn;
			}
		}
	}
	if (on == -1) {
		for (int i = 0; i < len; i++)
			y[i].r = y[i].r / len;
	}
}
bigInt absMul(bigInt a, bigInt b) {
	/*
	    采用快速傅里叶变换实现两个大整数 bigInt 绝对值的相乘，即 |a| * |b|，返回一个大整数 bigInt。
	*/
	int len1 = a.num.size(), len2 = b.num.size(), len = 1;
	std::vector<complex>x1, x2;
	std::vector<complex>().swap(x1);
	std::vector<complex>().swap(x2);
	while (len < len1 * 2 || len < len2 * 2)
		len <<= 1;
	for (int i = 0; i < len1; i++)
		x1.push_back(complex(a.num[i], 0));
	for (int i = len1; i < len; i++)
		x1.push_back(complex(0, 0));
	for (int i = 0; i < len2; i++)
		x2.push_back(complex(b.num[i], 0));
	for (int i = len2; i < len; i++)
		x2.push_back(complex(0, 0));
	FFT(x1, len, 1);
	FFT(x2, len, 1);
	for (int i = 0; i < len; i++)
		x1[i] = x1[i] * x2[i];
	FFT(x1, len, -1);
	std::vector<int>sum;
	std::vector<int>().swap(sum);
	for (int i = 0; i < len; i++)
		sum.push_back((int)(x1[i].r + 0.5));
	for (int i = 0; i < len; i++) {
		sum[i + 1] += sum[i] / 10;
		sum[i] %= 10;
	}
	len = len1 + len2 - 1;
	while (sum[len] <= 0 && len > 0) len--;
	std::vector<int>().swap(a.num);
	for (int i = 0; i <= len; i++)
		a.num.push_back(sum[i]);
	a.sign = 0;
	return a.checkCarry();
}
bigInt& operator += (bigInt &a, const bigInt &b) {
	/*
		计算 a + b 并将其值存放到a中
	*/
	if (a.sign == b.sign) {
		if (a.num.size() < b.num.size()) a.num.resize(b.num.size());
		for (int i = 0; i < b.num.size(); i++) a.num[i] += b.num[i];
		return a.checkCarry();
	} else {
		if (a.sign == 1) {
			int sign;
			if (absCmp(a, b) <= 0) sign = 0;
			else sign = 1;
			a = absSub(b, a);
			a.sign = sign;
			return a;
		} else {
			int sign;
			if (absCmp(a, b) >= 0) sign = 0;
			else sign = 1;
			a = absSub(a, b);
			a.sign = sign;
			return a;
		}
	}
}
bigInt& operator *= (bigInt &a, const bigInt &b) {
	/*
		计算 a * b 并将值存放到a中
	*/
	int sign = a.sign ^ b.sign;
	a = absMul(a, b);
	a.sign = sign;
	return a;
}
bigInt operator + (bigInt a, const bigInt b) {
	// 计算 a + b
	return a += b;
}
bigInt operator - (bigInt a, bigInt b) {
	// 计算 a - b
	b.sign = 1 - b.sign;
	return a += b;
}
bigInt operator * (bigInt a, bigInt b) {
	// 计算 a * b
	return a *= b;
}
struct bigReal {
	/*
		实现一个有符号大实数类 bigReal，支持乘法操作。
	*/
	bool type; 			// 保存大实数的数据类型，type = 0 表示是整数， type = 1 表示是小数。
	bigInt effNum = 0;	// 保存所有有效位数表示的大整数。
	bigInt power = 0;	// 保存该大实数的幂次值。
	void show() {
		/*
			将 bigReal 内部值输出，用于调试方便。
		*/
		std::cout << "sign = " << effNum.sign << std::endl;
		std::cout << "type = " << type << std::endl;
		std::cout << "effNum = " << effNum.to_string() << std::endl;
		std::cout << "power = " << power.to_string() << std::endl;
	}
	std::string to_decimal_string() {
		/*
			将 bigReal 按照常规记数法输出。
		*/
		if (effNum.num.size() == 1 && effNum.num[0] == 0) return "0";
		std::string res = "";
		int pow = 0;
		for (int i = (int) power.num.size() - 1; i >= 0; i--)
			pow = pow * 10 + power.num[i];
		if (power.sign == 0) {
			for (int i = (int) effNum.num.size() - 1; i >= 0; i--)
				res += '0' + effNum.num[i];
			for (int i = 1; i <= pow; i++)
				res += '0';
		} else {
			std::vector<int>tmp;
			std::vector<int>().swap(tmp);
			for (int i = 0; i < effNum.num.size(); i++)
				tmp.push_back(effNum.num[i]);
			for (int i = 1; i <= pow - ((int)effNum.num.size() - 1); i++)
				tmp.push_back(0);
			int pos;
			for (int i = 0; i < pow; i++)
				if (tmp[i] != 0 || i == pow - 1) {
					pos = i;
					break;
				}
			for (int i = pos; i < pow; i++) res += tmp[i] + '0';
			res += '.';
			for (int i = pow; i < tmp.size(); i++)
				res += tmp[i] + '0';
			reverse(res.begin(), res.end());
		}
		if (effNum.sign == 1) res = "-" + res;
		return res;
	}
	std::string to_scinote_string() {
		/*
			将 bigReal 按照科学记数法输出。
		*/
		if (effNum.num.size() == 1 && effNum.num[0] == 0) return "0";
		bigInt pow = power + effNum.num.size() - 1;
		std::string res = "";
		bool check_no_dot = true;
		for (int i = (int) effNum.num.size() - 2; i >= 0; i--)
			if (effNum.num[i] != 0)
				check_no_dot = false;
		res = std::to_string(effNum.num[effNum.num.size() - 1]);
		if (!check_no_dot) {
			res += '.';
			int pos = 0;
			for (int i = 0; i <= (int) effNum.num.size() - 2; i++)
				if (effNum.num[i] != 0) {
					pos = i;
					break;
				}
			for (int i = (int) effNum.num.size() - 2; i >= pos; i--)
				res += effNum.num[i] + '0';
		}
		res += 'e';
		res += pow.to_string();
		if (effNum.sign == 1) res = "-" + res;
		return res;
	}
	std::string to_string() {
		/*
			自动选择将 bigReal 是按常规记数法还是科学记数法输出。
		*/
		if (effNum.num.size() == 1 && effNum.num[0] == 0) return "0";
		if (type == 0) return effNum.to_string();
		bigInt pow = power, ws = 0;
		if (power.sign == 0) {
			ws = effNum.num.size() + pow;
		} else {
			pow.sign = 0;
			if (absCmp(pow, effNum.num.size()) >= 0) ws = pow + 2;
			else ws = effNum.num.size() + 1;
			int cnt = 0;
			for (int i = 0; i < (int) effNum.num.size() - 1; i++) {
				if (effNum.num[i] != 0) break;
				cnt++;
			}
			if (absCmp(pow, cnt) <= 0) ws = ws - pow;
			else ws = ws - cnt;
		}
		if (absCmp(ws, decimalMeanLen) <= 0) return to_decimal_string();
		else return to_scinote_string();
	}
	void setNumber(std::string num) {
		/*
			将一个用string表示的大实数存储到当前大实数中
		*/
		int num_e = 0, pos_e = -1;
		int num_dot = 0, pos_dot = -1;
		for (int i = 0; i < num.length(); i++) {
			if (num[i] == 'e') num_e++, pos_e = i;
			if (num[i] == '.') num_dot++, pos_dot = i;
		}
		if (num_e == 0 && num_dot == 0) {
			type = 0;
			effNum.setNumber(num);
		} else {
			type = 1;
			if (num_e == 0 && num_dot == 1) {
				std::string tmp = "";
				for (int i = 0; i < num.length(); i++)
					if (num[i] != '.') tmp += num[i];
				effNum.setNumber(tmp);
				power.setNumber(-num.length() + (pos_dot + 1));
			}
			if (num_e == 1 && num_dot == 0) {

				effNum.setNumber(num.substr(0, pos_e));
				power.setNumber(num.substr(pos_e + 1));
			}
			if (num_e == 1 && num_dot == 1) {
				std::string tmp = "";
				for (int i = 0; i < pos_e; i++)
					if (num[i] != '.') tmp += num[i];
				effNum.setNumber(tmp);
				power.setNumber(-pos_e + (pos_dot + 1));
				bigInt powerAdd = 0;
				powerAdd.setNumber(num.substr(pos_e + 1));
				power += powerAdd;
			}
		}
	}
	bigReal(std::string number) {
		/*
			将一个用string表示的大实数构造到当前大实数中
		*/
		setNumber(number);
	}
};

bigReal operator * (bigReal num1, bigReal num2) {
	/*
		计算两个大实数 bigReal 的乘法
	*/
	num1.type |= num2.type;
	num1.effNum *= num2.effNum;
	num1.power += num2.power;
	return num1;
}

int main(int argc, char* argv[]) {
	
	// 参数错误检测，并输出错误信息。
	int paramState = paramTest(argc, argv);
	switch (paramState) {
		case 1:
			std::cout << "Too many numbers entered!" << std::endl;
			break;
		case 2:
			std::cout << "The entered numbers should be missing!" << std::endl;
			break;
		case 3:
			std::cout << "The input cannot be interpret as numbers!" << std::endl;
			break;
		case 4:
			std::cout << "The entered number has too many significant digits!" << std::endl;
			break;
		case 5:
			std::cout << "The filename \"result.txt\" cannot be entered as one of the arguments!" << std::endl;
			break;
	}
	if (paramState != 0) return 0;
	
	// 数据存储
	bigReal num1(loadFileData(argv[1]));
	bigReal num2(loadFileData(argv[2]));
	
	// 数据处理，计算两个大实数的乘法
	bigReal num3 = num1 * num2;
	
	// 数据输出
	FILE *file = fopen("result.txt", "w");
	fprintf(file, "%s * %s = %s\n", num1.to_string().c_str(), num2.to_string().c_str(), num3.to_string().c_str());
	fclose(file);
	std::cout << num1.to_string() << " * " << num2.to_string() << " = " << num3.to_string() << std::endl;
	return 0;
}
