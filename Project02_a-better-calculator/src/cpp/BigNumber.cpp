#include "../headfile/BigNumber.hpp"
#include "../headfile/Constant.hpp"
#include "../headfile/Exception.hpp"
#include "../headfile/NumberCheck.hpp"
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
void BigNumber::show()
{
    /*
        用于展示数字，便于调试。
    */
    std::cout << "negative_ = " << negative_ << std::endl;
    std::cout << "digits_ = [";
    for (auto digit : digits_)
    {
        std::cout << digit << ",";
    }
    std::cout << "]" << std::endl;
    std::cout << "dotpos_ = " << dotpos_ << std::endl;
}
BigNumber &BigNumber::checkCarry()
{
    /*
        检查数字进位、前导零、和有效位数长度是否超过设定值。
    */
    while (!digits_.empty() && !digits_.back())
        digits_.pop_back();
    if (digits_.empty())
    {
        dotpos_ = 0;
        negative_ = false;
        digits_.push_back(0);
        return *this;
    }
    for (int32_t i = 1; i < digits_.size(); i++)
    {
        digits_[i] += digits_[i - 1] / 10;
        digits_[i - 1] %= 10;
    }

    while (digits_.back() >= 10)
    {
        digits_.push_back(digits_.back() / 10);
        digits_[digits_.size() - 2] %= 10;
    }
    if (digits_.size() > longestDigitSize)
    {
        throw number_calculate_error("The number of SIGNIFICANT DIGITS is too LARGE.");
    }
    return *this;
}
std::string BigNumber::to_string()
{
    /*
        将大整数转化为字符串。
    */
    std::string number = "";
    std::vector<int32_t> effnum;
    int32_t add_zero_num = dotpos_ - (int32_t)digits_.size();
    for (int32_t i = 1; i <= add_zero_num; i++)
    {
        effnum.push_back(0);
    }
    for (int32_t i = digits_.size() - 1; i >= 0; i--)
    {
        effnum.push_back(digits_[i]);
    }
    int32_t pos_dot = (int32_t)effnum.size() - dotpos_;
    for (int32_t i = 0; i < pos_dot; i++)
    {
        number += (char)(effnum[i] + '0');
    }
    if (dotpos_ != 0)
        number += '.';
    for (int32_t i = pos_dot; i < effnum.size(); i++)
    {
        number += (char)(effnum[i] + '0');
    }
    if (number[0] == '.')
        number = "0" + number;
    if (negative_)
        number = "-" + number;
    return number;
}
void BigNumber::set_BigNumber(std::string number)
{
    /*
        用 number 字符串构造当前的数字，当number不是数字的时候将会报错。
    */
    if (numTest(number))
    {
        throw number_parse_error("Entering a number in the WRONG FORMAT.");
    }
    if (number[0] == '-')
    {
        negative_ = true;
    }
    else
    {
        negative_ = false;
    }
    int32_t pos_dot = -1, pos_e = -1;
    for (int32_t i = 0; i < number.length(); i++)
    {
        if (number[i] == '.')
            pos_dot = i;
        if (number[i] == 'e')
            pos_e = i;
    }
    if (pos_e == -1)
    {
        dotpos_ = 0;
        for (int32_t i = 0; i < number.length(); i++)
        {
            if (number[i] == '.')
            {
                dotpos_ = (int32_t)number.length() - i - 1;
                break;
            }
        }

        for (int32_t i = number.size() - 1; i >= 0; i--)
        {
            if (number[i] >= '0' && number[i] <= '9')
            {
                digits_.push_back(number[i] - '0');
            }
        }
    }
    else
    {
        int32_t power = 0, power_sign = 1;
        if (number[pos_e + 1] == '-')
        {
            power_sign = -1;
        }
        for (int32_t i = pos_e + 1; i < number.length(); i++)
        {
            if (number[i] >= '0' && number[i] <= '9')
            {
                power = power * 10 + (int32_t)(number[i] - '0');
            }
        }
        power *= power_sign;
        if (power > 0)
        {
            for (int32_t i = 1; i <= power; i++)
            {
                digits_.push_back(0);
            }
        }
        for (int32_t i = pos_e - 1; i >= 0; i--)
        {
            if (number[i] >= '0' && number[i] <= '9')
            {
                digits_.push_back(number[i] - '0');
            }
        }
        if (power < 0)
        {
            dotpos_ = -power;
        }
        else
        {
            dotpos_ = 0;
        }
        if (pos_dot != -1)
        {
            dotpos_ += pos_e - pos_dot - 1;
        }
    }
    checkCarry();
}
BigNumber &BigNumber::checkScale(int32_t setted_scale)
{
    /*
        检查精度、舍弃精度到小数点后 setted_scale 位
    */
    std::reverse(digits_.begin(), digits_.end());
    for (int32_t i = 1; i <= dotpos_ - setted_scale; i++)
    {
        digits_.pop_back();
        if (digits_.empty())
        {
            this->set_BigNumber("0");
            return *this;
        }
    }
    for (int32_t i = dotpos_ + 1; i <= setted_scale; i++)
    {
        digits_.push_back(0);
    }
    dotpos_ = setted_scale;
    std::reverse(digits_.begin(), digits_.end());
    if (digits_.size() > longestDigitSize)
    {
        throw number_calculate_error("The number of SIGNIFICANT DIGITS is too LARGE.");
    }
    return *this;
}
BigNumber::BigNumber() {}
BigNumber::BigNumber(std::string number_str)
{
    /*
        用 number_str 字符串构造 BigNumber
    */
    set_BigNumber(number_str);
}
BigNumber::BigNumber(int32_t number_int32_t)
{
    /*
        用 number_int32_t 数字构造 BigNumber
    */
    set_BigNumber(std::to_string(number_int32_t));
}

int32_t BigNumberAbsCmp(BigNumber num1, BigNumber num2)
{
    /*
        比较 |num1| 和 |num2| 值的大小：
        |num1| < |num2| 返回 -1
        |num1| = |num2| 返回 0
        |num1| > |num2| 返回 1
    */
    num1.checkCarry();
    num2.checkCarry();
    bool num1_is_zero, num2_is_zero;
    if (num1.digits_.size() == 1 && num1.digits_[0] == 0)
    {
        num1_is_zero = true;
    }
    else
    {
        num1_is_zero = false;
    }
    if (num2.digits_.size() == 1 && num2.digits_[0] == 0)
    {
        num2_is_zero = true;
    }
    else
    {
        num2_is_zero = false;
    }
    if (num1_is_zero && num2_is_zero)
        return 0;
    if (!num1_is_zero && num2_is_zero)
        return 1;
    if (num1_is_zero && !num2_is_zero)
        return -1;
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    if (num1.dotpos_ < num2.dotpos_)
    {
        for (int32_t i = 1; i <= num2.dotpos_ - num1.dotpos_; i++)
        {
            num1.digits_.push_back(0);
        }
    }
    else
    {
        for (int32_t i = 1; i <= num1.dotpos_ - num2.dotpos_; i++)
        {
            num2.digits_.push_back(0);
        }
    }
    if (num1.digits_.size() > num2.digits_.size())
        return 1;
    if (num1.digits_.size() < num2.digits_.size())
        return -1;
    for (int32_t i = 0; i < num1.digits_.size(); i++)
    {
        if (num1.digits_[i] > num2.digits_[i])
            return 1;
        else if (num1.digits_[i] < num2.digits_[i])
            return -1;
    }
    return 0;
}
int32_t BigNumberCmp(BigNumber num1, BigNumber num2)
{
    /*
        比较 num1 和 num2 值的大小：
        num1 < num2 返回 -1
        num1 = num2 返回 0
        num1 > num2 返回 1
    */
    if (num1.negative_ && !num2.negative_)
    {
        return -1;
    }
    else if (!num1.negative_ && num2.negative_)
    {
        return 1;
    }
    if (num1.negative_)
    {
        return -BigNumberAbsCmp(num1, num2);
    }
    return BigNumberAbsCmp(num1, num2);
}
bool operator<(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的小于号 <
    */
    return BigNumberCmp(num1, num2) < 0;
}
bool operator<=(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的小于等于号 <=
    */
    return BigNumberCmp(num1, num2) <= 0;
}
bool operator==(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的等于号 ==
    */
    return BigNumberCmp(num1, num2) == 0;
}
bool operator!=(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的不等于号 !=
    */
    return BigNumberCmp(num1, num2) != 0;
}
bool operator>=(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的大于等于号 >=
    */
    return BigNumberCmp(num1, num2) >= 0;
}
bool operator>(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的大于号 >
    */
    return BigNumberCmp(num1, num2) > 0;
}
BigNumber BigNumberAbsSub(BigNumber num1, BigNumber num2, bool negative)
{
    /*
        计算 ||num1| - |num2|| 的值。
    */
    if (BigNumberAbsCmp(num1, num2) < 0)
    {
        std::swap(num1, num2);
    }
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    if (num1.dotpos_ < num2.dotpos_)
    {
        for (int32_t i = 1; i <= num2.dotpos_ - num1.dotpos_; i++)
        {
            num1.digits_.push_back(0);
        }
    }
    else
    {
        for (int32_t i = 1; i <= num1.dotpos_ - num2.dotpos_; i++)
        {
            num2.digits_.push_back(0);
        }
    }
    num1.dotpos_ = num2.dotpos_ = std::max(num1.dotpos_, num2.dotpos_);
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    for (int32_t i = 0; i < num2.digits_.size(); num1.digits_[i] -= num2.digits_[i], i++)
        if (num1.digits_[i] < num2.digits_[i])
        {
            int32_t j = i + 1;
            while (!num1.digits_[j])
                j++;
            while (j > i)
            {
                --num1.digits_[j];
                num1.digits_[--j] += 10;
            }
        }
    num1.negative_ = negative;
    return num1.checkCarry();
}
BigNumber BigNumberAbsAdd(BigNumber num1, BigNumber num2, bool negative)
{
    /*
        计算 |num1| + |num2| 的值。
    */
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    if (num1.dotpos_ < num2.dotpos_)
    {
        for (int32_t i = 1; i <= num2.dotpos_ - num1.dotpos_; i++)
        {
            num1.digits_.push_back(0);
        }
    }
    else
    {
        for (int32_t i = 1; i <= num1.dotpos_ - num2.dotpos_; i++)
        {
            num2.digits_.push_back(0);
        }
    }
    num1.dotpos_ = num2.dotpos_ = std::max(num1.dotpos_, num2.dotpos_);
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    if (num1.digits_.size() < num2.digits_.size())
    {
        num1.digits_.resize(num2.digits_.size());
    }
    for (int32_t i = 0; i < num2.digits_.size(); i++)
    {
        num1.digits_[i] += num2.digits_[i];
    }
    num1.negative_ = negative;
    return num1.checkCarry();
}
BigNumber operator+(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的加号 +
    */
    if (num1.negative_ == num2.negative_)
    {
        return BigNumberAbsAdd(num1, num2, num1.negative_);
    }
    if (num1.negative_)
    {
        return BigNumberAbsSub(num1, num2, BigNumberAbsCmp(num1, num2) > 0);
    }
    return BigNumberAbsSub(num1, num2, BigNumberAbsCmp(num1, num2) < 0);
}
BigNumber operator+=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的加等于号 +=
    */
    return num1 = num1 + num2;
}
BigNumber operator-(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的减号 -
    */
    num2.negative_ = 1 - num2.negative_;
    return num1 + num2;
}
BigNumber operator-=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的减等于号 -=
    */
    return num1 = num1 - num2;
}
struct complex
{
    /*
        实现一个复数类，用于 FFT。
    */
    double Real; // 实部
    double Imag; // 虚部
    complex() {}
    complex(double Real, double Imag)
    {
        /*
            使用 complex(Real, Imag) 来构造
        */
        this->Real = Real;
        this->Imag = Imag;
    }
    inline complex operator*(const complex &x) const
    {
        /*
            重载两个复数的乘号 *
        */
        return complex(Real * x.Real - Imag * x.Imag, Real * x.Imag + Imag * x.Real);
    }
    inline void operator*=(const complex &x)
    {
        /*
            重载两个复数的乘等于号 *=
        */
        *this = *this * x;
    }
    inline complex operator+(const complex &x) const
    {
        /*
            重载两个复数的加号 +
        */
        return complex(Real + x.Real, Imag + x.Imag);
    }
    inline complex operator-(const complex &x) const
    {
        /*
            重载两个复数的减号 -
        */
        return complex(Real - x.Real, Imag - x.Imag);
    }
};

void FFT(std::vector<complex> &omega, int32_t len, int32_t no_reverse)
{
    /*
        快速傅里叶变换 FFT，no_reverse = 1 表示正变换， no_reverse = -1 表示逆变换
        omega 表示多项式的系数表示法，len 表示多项式的项数。
    */
    for (int32_t i = 1, j = len / 2; i < len - 1; i++)
    {
        if (i < j)
            std::swap(omega[i], omega[j]);
        int32_t k = len / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k)
            j += k;
    }
    for (int32_t h = 2; h <= len; h <<= 1)
    {
        complex wn(cos(-no_reverse * 2.0 * acos(-1) / h), sin(-no_reverse * 2.0 * acos(-1) / h));
        for (int32_t j = 0; j < len; j += h)
        {
            complex w(1, 0);
            for (int32_t k = j; k < j + h / 2; k++)
            {
                complex u = omega[k];
                complex t = w * omega[k + h / 2];
                omega[k] = u + t;
                omega[k + h / 2] = u - t;
                w *= wn;
            }
        }
    }
    if (no_reverse == -1)
    {
        for (int32_t i = 0; i < len; i++)
            omega[i].Real = omega[i].Real / len;
    }
}

BigNumber BigNumberAbsMul(BigNumber num1, BigNumber num2, bool negative)
{
    /*
        计算 |num1| * |num2|
    */
    int32_t len1 = num1.digits_.size(), len2 = num2.digits_.size(), len = 1;
    if (len1 + len2 > longestDigitSize)
    {
        throw number_calculate_error("The number of SIGNIFICANT DIGITS is too LARGE.");
    }
    std::vector<complex> complex_num1, complex_num2;
    std::vector<complex>().swap(complex_num1);
    std::vector<complex>().swap(complex_num2);
    while (len < len1 * 2 || len < len2 * 2)
    {
        len <<= 1;
    }
    for (int32_t i = 0; i < len1; i++)
    {
        complex_num1.push_back(complex(num1.digits_[i], 0));
    }
    for (int32_t i = len1; i < len; i++)
    {
        complex_num1.push_back(complex(0, 0));
    }
    for (int32_t i = 0; i < len2; i++)
    {
        complex_num2.push_back(complex(num2.digits_[i], 0));
    }
    for (int32_t i = len2; i < len; i++)
    {
        complex_num2.push_back(complex(0, 0));
    }
    FFT(complex_num1, len, 1);
    FFT(complex_num2, len, 1);
    for (int32_t i = 0; i < len; i++)
    {
        complex_num1[i] = complex_num1[i] * complex_num2[i];
    }
    FFT(complex_num1, len, -1);
    std::vector<int32_t> sum;
    std::vector<int32_t>().swap(sum);
    for (int32_t i = 0; i < len; i++)
        sum.push_back((int32_t)(complex_num1[i].Real + 0.5));
    for (int32_t i = 0; i < len; i++)
    {
        sum[i + 1] += sum[i] / 10;
        sum[i] %= 10;
    }
    len = len1 + len2 - 1;
    while (sum[len] <= 0 && len > 0)
        len--;
    std::vector<int32_t>().swap(num1.digits_);
    for (int32_t i = 0; i <= len; i++)
        num1.digits_.push_back(sum[i]);
    num1.negative_ = negative;
    num1.dotpos_ += num2.dotpos_;
    return num1.checkCarry();
}

BigNumber operator*(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的乘号 *
    */
    return BigNumberAbsMul(num1, num2, num1.negative_ ^ num2.negative_);
}
BigNumber operator*=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的乘等于号 *=
    */
    return num1 = BigNumberAbsMul(num1, num2, num1.negative_ ^ num2.negative_);
}

typedef std::vector<int32_t> Poly; // 多项式的系数表示
inline int64_t quick_pow(int64_t a, int64_t m)
{
    /*
        快速幂用来计算整数 a ^ m
    */
    int64_t ans = 1;
    for (; m; m >>= 1, a = a * a % mod)
        if (m & 1)
            ans = ans * a % mod;
    return ans;
}
inline void NTT(Poly &a, int32_t x, int32_t type)
{
    /*
       数论变换 NNT 加速 FFT，用于计算除法。
    */
    int32_t n = 1ll << x;
    std::vector<int32_t> R;
    R.resize(n);
    for (int32_t i = 0; i < n; ++i)
        if ((R[i] = R[i >> 1] >> 1 | (i & 1) << x - 1) > i)
            std::swap(a[i], a[R[i]]);
    for (int32_t s = 1; s <= x; ++s)
    {
        int32_t len = 1ll << s, mid = len >> 1ll;
        int32_t w = quick_pow(3ll, type * (mod - 1) / len + mod - 1);
        for (int32_t k = 0; k < n; k += len)
        {
            int32_t d = 1;
            for (int32_t j = 0; j < mid; ++j)
            {
                int32_t u = a[j + k], v = (int64_t)a[j + k + mid] * d % mod;
                a[j + k] = (u + v) % mod, a[j + k + mid] = (u - v + mod) % mod;
                d = (int64_t)d * w % mod;
            }
        }
    }
    if (type == -1)
        for (int32_t i = 0, inv = quick_pow(n, mod - 2); i < n; ++i)
            a[i] = (int64_t)a[i] * inv % mod;
}
inline int32_t ceilog(int64_t x)
{
    /*
        log2(x) 向上取整。
    */
    int32_t ans = 0;
    while (1ll << ans < x)
        ans++;
    return ans;
}
Poly operator*(Poly A, Poly B)
{
    /*
        使用 NTT 重载两个多项式的卷积 A * B。
    */
    int32_t deg = A.size() + B.size() - 1;
    int32_t x = ceilog(deg);
    A.resize(1 << x), B.resize(1 << x);
    NTT(A, x, 1), NTT(B, x, 1);
    for (int32_t i = 0; i < 1 << x; ++i)
        A[i] = (int64_t)A[i] * B[i] % mod;
    NTT(A, x, -1);
    A.resize(deg);
    for (int32_t i = deg - 1; i; --i)
    {
        A[i - 1] += A[i] / 10;
        A[i] %= 10;
    }
    return A;
}

BigNumber BigNumberAbsDiv(BigNumber num1, BigNumber num2, bool negative, bool isDiv)
{
    /*
        计算 |num1| / |num2|
    */
    if (num2 == 0)
    {
        throw number_calculate_error("Divisor can NOT be ZERO.");
    }
    int32_t iteration_times = 1;
    int32_t limits = (int32_t)num1.digits_.size() - (int32_t)num2.digits_.size() + scale + 16;
    if (limits > longestDigitSize)
    {
        throw number_calculate_error("The number of SIGNIFICANT DIGITS is too LARGE.");
    }
    while (iteration_times <= limits)
    {
        iteration_times *= 2;
    }
    num1.negative_ = num2.negative_ = 0;
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    if (num1.dotpos_ < num2.dotpos_)
    {
        for (int32_t i = 1; i <= num2.dotpos_ - num1.dotpos_; i++)
        {
            num1.digits_.push_back(0);
        }
    }
    else
    {
        for (int32_t i = 1; i <= num1.dotpos_ - num2.dotpos_; i++)
        {
            num2.digits_.push_back(0);
        }
    }
    num1.dotpos_ = num2.dotpos_ = std::max(num1.dotpos_, num2.dotpos_);
    int32_t rest = num1.digits_.size() - num2.digits_.size() + (isDiv ? 0 : scale);
    Poly A, B, C;
    B.resize(2);
    B[1] = 100 / (num2.digits_[0] * 10 + (num2.digits_.size() > 1 ? num2.digits_[1] : 0));
    int32_t x = ceilog(num2.digits_.size()) + 1;
    for (int32_t s = 1; iteration_times > 0; iteration_times /= 2, s++)
    {
        C.resize(1 << s), B.resize(1 << s);
        for (int32_t i = 0; i < std::min(1 << s, (int32_t)num2.digits_.size()); ++i)
            C[i] = num2.digits_[i];
        for (int32_t i = std::min(1 << s, (int32_t)num2.digits_.size()); i < 1 << s; ++i)
            C[i] = 0;
        C = B * C;
        for (int32_t i = 1; i < C.size(); ++i)
            C[i] = -C[i];
        C[0] = 2 - C[0];
        for (int32_t i = C.size() - 1; i; --i)
        {
            C[i - 1] += (C[i] - 9) / 10;
            C[i] = (C[i] + 10) % 10;
        }
        B = B * C;
        B.resize(1 << s);
    }
    for (int32_t i = 0; i < num1.digits_.size(); i++)
        A.push_back(num1.digits_[i]);
    std::reverse(num1.digits_.begin(), num1.digits_.end());
    std::reverse(num2.digits_.begin(), num2.digits_.end());
    A = A * B;
    BigNumber ans;
    ans.negative_ = 0;
    for (int32_t i = rest; i >= 0; i--)
    {
        ans.digits_.push_back(A[i]);
    }
    ans.dotpos_ = (isDiv ? 0 : scale);
    ans = ans.checkCarry().checkScale((isDiv ? 0 : scale));
    BigNumber delta = 1;
    delta.dotpos_ = (isDiv ? 0 : scale);
    if ((delta + ans) * num2 <= num1)
    {
        ans += delta;
    }
    ans.negative_ = negative;
    return ans.checkCarry().checkScale((isDiv ? 0 : scale));
}

BigNumber operator/(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的除号 /
    */
    return BigNumberAbsDiv(num1, num2, num1.negative_ ^ num2.negative_, false);
}
BigNumber operator/=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的除等于号 /=
    */
    return num1 = BigNumberAbsDiv(num1, num2, num1.negative_ ^ num2.negative_, false);
}

BigNumber operator%(BigNumber num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的取模号 %
    */
    return (num1 - num1 / num2 * num2);
}
BigNumber operator%=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个BigNumber 类型数据的取模等于号 %=
    */
    return num1 = (num1 - num1 / num2 * num2);
}
BigNumber trunc(BigNumber num)
{
    /*
        返回对 num 截取小数部分的值。
    */
    std::reverse(num.digits_.begin(), num.digits_.end());
    int32_t digit_size = num.digits_.size();
    for (int32_t i = 1; i <= num.dotpos_ && i <= digit_size; i++)
    {
        num.digits_.pop_back();
    }
    num.dotpos_ = 0;
    std::reverse(num.digits_.begin(), num.digits_.end());
    if (num.digits_.empty())
        num = 0;
    return num;
}
BigNumber floor(BigNumber num)
{
    /*
        返回对 num 向下取整（即计算小于等于 num 的最大整数）的值。
    */
    BigNumber trunc_num = trunc(num);
    if (trunc_num == num)
        return num;
    if (num < 0)
        return trunc_num - 1;
    else
        return trunc_num;
}
BigNumber ceil(BigNumber num)
{
    /*
        返回对 num 向上取整（即计算大于等于 num 的最小整数）的值。
    */
    BigNumber trunc_num = trunc(num);
    if (trunc_num == num)
        return num;
    if (num < 0)
        return trunc_num;
    else
        return trunc_num + 1;
}
BigNumber abs(BigNumber num)
{
    /*
        返回对 num 的绝对值。
    */
    if (num.negative_)
        num.negative_ = 0;
    return num;
}
BigNumber sqrt(BigNumber num)
{
    /*
        计算 num 的开根号，当 num < 0 报错。
    */
    if (num < 0)
    {
        throw number_calculate_error("NEGATIVE NUMBER encountered during sqrt().");
    }
    if (num == 0)
        return 0;
    BigNumber num1_2("0.5");
    BigNumber cur_num, last_num = num;
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    while (true)
    {
        cur_num = (num1_2 * last_num + num1_2 * num / last_num).checkScale(scale);
        if (BigNumberAbsCmp(cur_num - last_num, eps) <= 0)
            break;
        last_num = cur_num;
    }
    if (last_num == cur_num)
        last_num = cur_num + eps;
    if (last_num < cur_num)
        std::swap(cur_num, last_num);
    if (last_num * last_num <= num)
        return last_num;
    else
        return cur_num;
}
BigNumber fac(BigNumber num)
{
    /*
        计算 num 的阶乘，当 num < 0 或者 当 num 不为整数时候报错。
    */
    if (num < 0)
    {
        throw number_calculate_error("NEGATIVE NUMBER encountered during fac().");
    }
    if (num != trunc(num))
    {
        throw number_calculate_error("FLOAT NUMBER encountered during fac().");
    }
    BigNumber res_fac = 1;
    for (int32_t i = 2; i <= num; i++)
    {
        res_fac *= i;
    }
    return res_fac;
}
BigNumber exp(BigNumber num)
{
    /*
        计算 num 的自然指数，e ^ num
    */
    scale += 2;
    if (num == 0)
        return 1;
    if (num < 0)
        return (1 / exp(0 - num)).checkScale(scale);
    int32_t count10 = num.digits_.size() - num.dotpos_;
    num.dotpos_ = num.digits_.size();
    std::string power = "1";
    for (int32_t i = 1; i <= count10; i++)
        power += '0';
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber now_item = 1, cur_exp = 1;
    for (int32_t i = 1;; i++)
    {
        now_item = now_item * num / i;
        if (BigNumberAbsCmp(now_item, eps) <= 0)
            break;
        cur_exp += now_item;
    }
    scale -= 2;
    return (cur_exp ^ (BigNumber)power).checkScale(scale);
}
BigNumber small_ln(BigNumber num)
{
    /*
        利用泰勒展开计算 ln(num) 的近似值。
    */
    BigNumber y = (num - 1) / (num + 1);
    BigNumber sqr_y = y * y;
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber now_small_ln = 2 * y;
    BigNumber now_item = 2 * y;
    for (int32_t i = 3;; i += 2)
    {
        now_item = now_item * sqr_y;
        BigNumber add_item = now_item / i;
        if (BigNumberAbsCmp(add_item, eps) <= 0)
            break;
        now_small_ln += add_item;
    }
    return now_small_ln.checkScale(scale);
}
BigNumber ln(BigNumber num)
{
    /*
        计算 ln(num) 的近似值，当 num <= 0 时报错。
    */
    if (num <= 0)
    {
        throw number_calculate_error("NON-POSITIVE NUMBER encountered during ln().");
    }
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale / 4;
    int32_t power = 0;
    while (true)
    {
        num = sqrt(num);
        power += 1;
        if (BigNumberAbsCmp(num - 1, eps) <= 0)
            break;
    }
    return (small_ln(num) * ((BigNumber)2 ^ (BigNumber)power)).checkScale(scale);
}

BigNumber get2pi()
{
    /*
        迭代计算 2pi 的近似值。
    */
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber now_pi = 4, now_item = 4;
    for (int32_t i = 1;; i++)
    {
        now_item = now_item * i / (2 * i + 1);
        if (BigNumberAbsCmp(now_item, eps) <= 0)
            break;
        now_pi += now_item;
    }
    return now_pi.checkScale(scale);
}

BigNumber getpi()
{
    /*
        迭代计算 2pi 的近似值。
    */
    scale += 2;
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber now_pi = 2, now_item = 2;
    for (int32_t i = 1;; i++)
    {
        now_item = now_item * i / (2 * i + 1);
        if (BigNumberAbsCmp(now_item, eps) <= 0)
            break;
        now_pi += now_item;
    }
    scale -= 2;
    return now_pi.checkScale(scale);
}

BigNumber get_2pi()
{
    /*
        迭代计算 0.5 * pi 的近似值。
    */
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber now_pi = 1, now_item = 1;
    for (int32_t i = 1;; i++)
    {
        now_item = now_item * i / (2 * i + 1);
        if (BigNumberAbsCmp(now_item, eps) <= 0)
            break;
        now_pi += now_item;
    }
    return now_pi.checkScale(scale);
}

BigNumber small_sin(BigNumber num)
{
    /*
        利用泰勒展开计算 sin (num) 的值。
    */
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber sqr_num = num * num;
    BigNumber now_sin = num, now_item = num;
    for (int32_t i = 3;; i += 2)
    {
        now_item = ((now_item * sqr_num / (i * (i - 1)))).checkScale(scale) * (-1);
        if (BigNumberAbsCmp(now_item, eps) <= 0)
            break;
        (now_sin += now_item).checkScale(scale);
    }
    return now_sin.checkScale(scale);
}
BigNumber sin(BigNumber num)
{
    /*
        计算 sin(num) 的值
    */
    if (num.negative_)
    {
        num.negative_ = 0;
        return 0 - sin(num);
    }
    BigNumber k2pi = get2pi();
    for (; num > k2pi;)
    {
        num -= BigNumberAbsDiv(num, k2pi, num.negative_, true) * k2pi;
    }
    return small_sin(num);
}
BigNumber cos(BigNumber num)
{
    /*
        计算 cos(num) 的值
    */
    return sin(num + get_2pi()).checkScale(scale);
}
BigNumber tan(BigNumber num)
{
    /*
        计算 tan(num) 的值
    */
    return sin(num) / cos(num).checkScale(scale);
}
BigNumber small_arctan(BigNumber num)
{
    /*
        利用泰勒展开计算 arctan (num) 的值。
    */
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    BigNumber sqr_num = num * num;
    BigNumber now_arctan = num, now_item = num;
    for (int32_t i = 3;; i += 2)
    {
        now_item = now_item * sqr_num * (-1);
        BigNumber add_item = now_item / i;
        if (BigNumberAbsCmp(add_item, eps) <= 0)
            break;
        now_arctan += add_item;
    }
    return now_arctan.checkScale(scale);
}

BigNumber arctan(BigNumber num)
{
    /*
        计算 arctan (num) 的值。
    */
    if (num.negative_)
        return 0 - arctan(0 - num);
    if (num > 1)
        return get_2pi() - arctan(1 / num);
    if (num > 0.5)
    {
        return small_arctan((std::string) "0.5") + small_arctan((num - (std::string) "0.5") / (1 + num * (std::string) "0.5"));
    }
    return small_arctan(num);
}
BigNumber arccot(BigNumber num)
{
    /*
        计算 arccot (num) 的值。
    */
    return get_2pi() - arctan(num);
}
BigNumber arcsin(BigNumber num)
{
    if (num > (std::string) "1" || num < (std::string) "-1")
    {
        throw number_calculate_error("Number is OUT of DOMAIN [-1, 1] encountered during arcsin().");
    }
    /*
        计算 arcsin (num) 的值。
    */
    return arctan(num / sqrt(1 - num * num));
}
BigNumber arccos(BigNumber num)
{
    if (num > (std::string) "1" || num < (std::string) "-1")
    {
        throw number_calculate_error("Number is OUT of DOMAIN [-1, 1] encountered during arccos().");
    }
    /*
        计算 arccos (num) 的值。
    */
    return get_2pi() - arcsin(num);
}

BigNumber operator^(BigNumber num1, BigNumber num2)
{
    /*
        重载两个大整数的阶乘符号 ^。
    */
    bool reciprocal;
    if (num2.negative_)
    {
        reciprocal = true;
        num2.negative_ = false;
    }
    else
    {
        reciprocal = false;
    }
    if (trunc(num2) == num2)
    {
        int32_t setted_scale = std::max(scale, num1.dotpos_);
        num2 = trunc(num2);
        BigNumber ans = 1;
        while (num2 != 0)
        {
            if (num2.digits_[0] % 2 == 1)
                ans = (ans * num1).checkScale(setted_scale);
            num1 = (num1 * num1).checkScale(setted_scale);
            num2 = BigNumberAbsDiv(num2, 2, false, true);
        }
        if (reciprocal)
        {
            ans = (1 / ans).checkScale(setted_scale);
        }
        return ans;
    }
    BigNumber y = num2 * ln(num1);
    BigNumber cur_proid = 1;
    BigNumber cur_item = 1;
    BigNumber eps;
    eps.negative_ = false;
    eps.digits_.push_back(1);
    eps.dotpos_ = scale;
    for (int i = 1;; i++)
    {
        cur_item = cur_item * y / i;
        if (BigNumberAbsCmp(cur_item, eps) <= 0)
            break;
        cur_proid += cur_item;
    }
    if (reciprocal)
    {
        cur_proid = (1 / cur_proid).checkScale(scale);
    }
    return cur_proid.checkScale(scale);
}
BigNumber operator^=(BigNumber &num1, BigNumber num2)
{
    /*
        重载两个大整数的阶乘等符号 ^=。
    */
    return num1 = num1 ^ num2;
}