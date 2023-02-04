# Project1: A Simple Calculator
## 需求分析

### 输入格式与输出格式

运行命令格式：`$./mul a b`，其中 $a, b$ 既可以为文件地址，也可是是实数。

输出答案格式：`x * y = z`，其中 $x, y, z$ 分别表示三个实数。

### 输入参数的约束

本项目实现了两个大实数相乘的乘法计算器。

“大实数”，就是一个实数，它可以是正数、负数或者零，并且其有效位数可以很多。

输入的“大整数”应该满足下列任意一种情况：

1. 整数：一个任意符号的长整数，可以带 $1$ 位符号位（正数也可以带符号位），如 `-1189203`，`1232`, `0`，`+123`。
2. 非科学记数法小数：形如 `整数.非负整数` 的小数，如 `-11.123`、`2.0`、`+3.14`。
3. 科学记数法小数：形如 `整数e整数` 或者 `非科学计数法小数e整数` 的小数，如 `-1.2380192e-12830`、`-12.31e128301`、`0.190123e-1238902`、`+0.008190238e123`。

正因为如此，输入命令中的大实数 $a, b$ 应满足较为宽松的限制：

1. 符号相对自由：既支持正实数，同样也支持负实数或者零，不局限于非负整数。
2. 数据范围扩大：本项目可处理数据范围足够大的大实数，不受 `C++` 内部普通数的数据类型范围（如`int`、`long long`、`__int128`、`double`、`long double`等）数据范围的限制。
3. 数据计算精度准确：本项目准确计算两个大实数的乘法，不受`C++` 内部实数数据类型（如 `float`、`double`、`long double` 等）丢失有效位数以外精度的限制。

项目提供两种输入参数 $a, b$ 的的方法：一种是**通过终端直接传入数值**；第二种是通过**终端传入一个文本文件**，项目程序读取文本文件中的内容获得数值。

如果项目当前目录中存在文本文件 `a.txt`（其中的内容是：`2`） 和 `b.txt`（其中的内容是：`3`），那么下列两种方式都可以成功运行项目程序。

- 方法 1：在项目所在终端执行命令 `$./mul 2 3`。
- 方法 2：在项目所在终端执行命令 `$./mul a.txt b.txt`。

并且运行效果都相同，都是 `2 * 3 = 6`。

![image-20220915033419196](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209150334316.png)

当输入参数给出的 $a, b$ 均满足：

> $a, b$ 为可读文本文件，且其中读出的数据（除去文本文件末尾非数字字符以外的所有文本内容）是“大实数” 或者 $a, b$ 本身就是"大实数"。

则项目程序认为输入合法，会按照 `x * y = z` 的格式，计算并输出 $a \times b$ 的值。

否则项目程序认为输入不合法，会提示下列错误：

- `The entered numbers should be missing!` 输入的参数缺失。
- `Too many numbers entered!` 输入的参数过多。
- `The input cannot be interpret as numbers!` 输入的数字格式错误，不是两个数。
- `The entered number has too many significant digits!` 为了避免由于输入整数有效位数过大（项目程序默认最大有效位数`longestSignDigit = 1e6` ）导致程序运行缓慢，当输入的数字有效位数过大时，程序会报出此错误并终止运行。
- `The filename "result.txt" cannot be entered as one of the arguments!` 作为输入参数的文件名不能是 `result.txt` ，因为该文件保存计算的答案文件。

### 输出答案的约束

形如 `x * y = z` 格式的输出，将会先写入项目文件目录下的 `result.txt`，然后在终端输出。

>  Hint：由于文件读写速度远远快于在终端上输出数字的速度，因此当终端打印结果较慢时，建议您查看项目文件目录下的 `result.txt` 文件查看结果。

对于 $x, y, z$ 中的每一个数字分别考虑，有两种输出方法：

1. 常规记数法输出：输出一个整数，或者一个形如 `整数.非负整数` 的非科学计数法小数。
2. 科学计数法输出：形如 `整数e整数` 或者 `非科学计数法小数e整数`，并且 `e` 之前的 `整数` 或者 `非科学计数法小数` 部分的 **绝对值** 在$[1, 10)$。 

如果这个数字本身的类型就是整数类型，那么我们将会直接采用常规记数法输出。

否则，项目程序会首先计算按照常规记数法输出需要的字符数，若该字符数不大于设定的最长字符数（程序中设置的默认值为 `decimalMeanLen = 20`），将优先采用常规记数法输出。否则，将会采用科学计数法输出。

另外，在输出数字时，项目程序会自动忽略小数点最后的连续 `0` 的部分，以及大整数的前导 `0`，以便于更加精简的表示输出。

## 项目思路及代码实现

**更多代码请见随报告一并提交的 `calculator.cpp`**

### 程序常数设定

本程序依赖于三个常数，`longestSignDigit` (设置有效位数长度)、`decimalMeanLen` (设置使用常规记数法输出小数时的最长字符数、`PI` (设置 $\pi$ 的值用于快速傅里叶变换`FFT`)

其默认值为：`longestSignDigit = 1e6` 、`decimalMeanLen = 20` 、`PI = acos(-1)` 。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250147343.png)

### 输入数据及预处理模块

此模块主要进行参数输入、错误检测、数据存储的过程，主要以字符串的形式输入参数，对参数进行错误检测后，将两个数字存储到程序中大实数类中，为后续的两数相乘模块进行前期准备。

#### 参数输入

主函数应当采用如下的格式，可以在运行程序时获得输入的参数：

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250148004.png)

#### 参数检测

以字符串的形式输入参数，依次进行如下检测：

1. 输入参数的个数是否恰好为 $2$ 个，是否过多或者过少。
   1. 参数过多：输出 `Too many numbers entered!`。
   2. 参数过少：输出 `The entered numbers should be missing!`
2. 如果输入参数是文件地址，首先检测该文件地址是否为 `result.txt`， 如果是，则输出 `The filename "result.txt" cannot be entered as one of the arguments!`；否则将这个文本文件打开，并读入数据作为输入参数。
3. 输入参数的格式是否为整数、小数点表示法表示的小数、科学计数法表示的小数。如果输入参数的格式出现错误，则输出 `The input cannot be interpret as numbers!`
4. 判断输入数字的实际有效位数是否过长（项目程序默认最大有效位数 `longestSignDigit = 1e6`）。如果任一输入的数字的有效位数大于 `longestSignDigit`，则输出 `The entered number has too many significant digits!`

在主函数中，可以使用这样的代码进行参数检测与错误信息输出:

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250142087.png)

这里使用到了参数合法性检测函数`paramTest`：![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250143082.png)

参数合法性检测函数`paramTest` 中使用到了 `fileTest` 函数（检测文件内文件是否存在，其内文本是否为实数）

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250149375.png)

`fileTest` 需要判断一个字符串是否能够表示为一个实数，所以需要使用到`numTest` 函数（分四种情况讨论字符串是否表示为一个实数）。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250152325.png)

`numTest` 函数基于三个函数实现，`intTest`（检测字符串是否为整数） `floatTest` （检测字符串是否为使用常规记数法表示的实数） `signDigitTest` （检测合法数字的有效位数是否超过设定值）

这三个函数分别实现如下：

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250154197.png)

#### 数据存储

参数通过检测后，将需要相乘的两个数存在大实数类 `bigReal` 中。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250225388.png)

其中 `loadFileData` 函数是将文件或者数字转换为`string` 类型，并返回。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250227291.png)

大实数类 `bigReal` 用来存储一个大实数，需要包含如下信息：

![image-20220925020246696](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250202749.png)

- 变量

  1. `bool type` 用来保存数字的类型，整数`type = 0`、小数`type = 1`。
  2. `bigInt effNum` 用来保存大实数的所有有效数字，其中 `bigInt` 是一个大整数类（后面会进一步说明）。
  3. `bigInt power` 用来保存大实数 $ 10 $ 的幂指数，其中 `bigInt` 是一个大整数类（后面会进一步说明）。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250203893.png)

  对于数字`-3.1415926e-100` 上述信息分别是：

  `type = 1` `effNum = (bigInt) ”-31415926“` `power = (bigInt) "-107"`

- 过程

  1. `void show()` 用来打印变量`type` 、`effNum` 、`power` 等，用于调试。
  2. `void setNumber(std::string num)` 传入一个 `string` 类型的参数，将当前的大实数设置成表示 `string` 所表示实数的值。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250204536.png)

- 函数

  1. `std::string to_decimal_string()` 以常规记数法方式返回需要输出的字符串。
  2. `std::string to_scinote_string()` 以科学记数法方式返回需要输出的字符串。
  3. `std::string to_string()` 判断需要使用那种方法输出字符串，并生成输出字符串。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250205027.png)

- 构造函数

  1. `bigReal(std::string number)` 传入一个 `string` 类型的参数，构造当前的大实数设置成表示`string`所表示实数的值。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250205936.png)

- 运算符

  1. `bigReal operator * (bigReal num1, bigReal num2)` 支持两个 `bigReal` 做乘法操作。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250206092.png)

大实数类 `bigReal`中所使用到的大整数类 `bigInt` 是用来存储一个大整数的，需要包含如下信息：

![image-20220925020850009](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250208066.png)

- 变量

  1. `bool sign` 用来保存大整数的符号，`sign = 0` 表示正数，`sign = 1` 表示负数。
  2. `std::vector<int>num` 用来保存大整数的数字。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250209693.png)

- 过程

  1. `void clear()` 用来清空当前这个大整数，并释放内存。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250209288.png)

  2. `void setNumber(long long number)`  传入一个 `long long` 类型的参数，将当前的大整数设置成表示 `long long` 所表示实数的值。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250210129.png)

  3. `void setNumber(std::string number)` 传入一个 `string` 类型的参数，将当前的大整数设置成表示 `string` 所表示实数的值。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250210011.png)

- 函数

  1. `bigInt& checkCarry()` 检查并且更新当前大整数的进位情况，将自己的地址传出。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250211599.png)

  2. `std::string to_string()` 以 `string` 类型输出当前大整数表示的数。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250212661.png)

- 构造函数

  1. `bigInt(long long number)` 传入一个 `long long` 类型的参数，构造当前的大实数设置成表示`long long`所表示实数的值。

  2. `bigInt(std::string number)`传入一个 `string ` 类型的参数，构造当前的大实数设置成表示 `string` 所表示实数的值。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250212406.png)

- 运算符

  1. `imbigReal& operator += (bigInt &a, const bigInt &b)` 计算大整数 $a + b$ 的值，并将其赋值到 $a$ 中。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250213999.png)

  2. `bigInt& operator *= (bigInt &a, const bigInt &b)` 计算大整数 $a \times b$ 的值，并将其赋值到 $a$ 中。该运算符的重载依赖于额外的函数`FFT` 和自定义的额外复数类`complex` （代码会在后面给出）。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250223076.png)

  3. `bigInt operator + (bigInt a, const bigInt b)`
  4. `bigInt operator - (bigInt a, bigInt b)`

  5. `bigInt operator * (bigInt a, bigInt b)`

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250219591.png)

此外，由于上面 `bigInt` 类中的数要做一些运算，我们定义了一些额外的函数：

- `int absCmp(const bigInt &a, const bigInt &b)` 比较两个大整数`bigInt`绝对值的大小，如果 $ |a| < |b| $ 则返回 `-1` ，如果 $ |a| = |b| $ 则返回 `0` ，如果 $ |a| > |b| $ 则返回 `1`。

  ![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250221643.png)

- `bigInt absSub(bigInt a, bigInt b) ` 计算两个大整数`bigInt` 绝对值差的绝对值，即$||a| - |b||$。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250221697.png)

- `bigInt absMul(bigInt a, bigInt b)` 计算两个大整数`bigInt` 绝对值的乘积，即$|a| \times |b|$。此函数依赖于手写的复数类 `complex` 和一个快速傅里叶变换函数`FFT`。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250222242.png)



### 大实数乘法模块

此模块主要进行两个大实类 `bigReal` 的数字 `num1, num2` 进行乘法，通过快速傅里叶变化来实现。

在主函数中，大整数乘法模块只需要使用如下语句即可实现：

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250232442.png)

#### 确定符号

`bool effNum.sign` 表示数字的符号，正号 `effNum.sign = 0`，负号 `effNum.sign = 1`。

为了确定大实数 `num1` 乘以 `num2` 结果 `ans` 的符号，可以列出如下的真值表：

| num1.effNum.sign | num2.effNum.sign | ans.effNum.sign |
| ---------------- | ---------------- | --------------- |
| 0                | 0                | 0               |
| 0                | 1                | 1               |
| 1                | 0                | 1               |
| 1                | 1                | 0               |

所以得到公式 `ans.effNum.sign = num1.effNum.sign ^ num2.effNum.sign `（其中`^`为异或运算）。

#### 确定类型

`bool type` 为大实数的数字类型，整数 `type = 0`、小数 `type = 1`。

- 当两个数字都是整数类型，那么答案的类型也应当是整数类型。
- 当两个数字至少有一个是小数类型，那么答案的类型也应当是小数类型。

为了确定大实数 `num1` 乘以 `num2` 结果 `ans` 的类型，可以列出如下的真值表：

| num1.type | num2.type | ans.type |
| --------- | --------- | -------- |
| 0         | 0         | 0        |
| 0         | 1         | 1        |
| 1         | 0         | 1        |
| 1         | 1         | 1        |

所以得到公式 `ans.type = num1.type | num2.type `（其中`|`符号为或运算）。

#### 确定有效位数和有效数字

` effNum` 表示大实数的有效数字。

为了确定大实数 `num1` 乘以 `num2` 结果 `ans` 的结果有效值，我们可以将两个数的有效值相乘，得到结果的有效值，即 `ans.effNum = num1.effNum * num2.effNum`，并根据实际得到的结果`ans.effNum`计算答案有效值的长度 `ans.effLen`。

考虑到这里 `num1.effNum` 和 `num2.effNum` 长度可能较长。如果采用时间复杂度为$O(n ^2)$的朴素做法，会导致项目程序在此处存在 **性能瓶颈**，因此在计算两个大整数乘法时，项目程序采用时间复杂度为$O(n \log_2 n)$的 **快速傅里叶变换算法** 进行优化。（其中 $n$ 表示数字有效值的长度）

#### 确定幂指数

大实数 `num1, num2` 可以分别表示为：

- $\text{num}_1 = \text{num}_1.\text{effNum} \times 10^{\text{num}_1.\text{power}}$
- $\text{num}_2 = \text{num}_2.\text{effNum} \times 10^{\text{num}_2.\text{power}}$

所以，大实数 `num1` 乘以 `num2` 结果 `ans` 的值可表示为：

- $\text{ans} = (\text{num}_1.\text{effNum} \times \text{num}_2.\text{effNum}) \times 10^{\text{num}_1.\text{power} + \text{num}_2.\text{power}}$

所以：`ans.power = num1.power + num2.power`

上述 2.3.2 对应下列代码的第5行，

上述 2.3.1 和 2.3.3 对应下列代码的第5行，

上述2.3.4 对应下列代码的第7行。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250227336.png)

### 数据输出模块

此模块主要进行计算结果的输出，既在终端输出，也在目录中以文件形式输出。

![1](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250233955.png)

见 2.3 节内容，这里摘抄如下：

形如 `x * y = z` 格式的输出，将会先写入项目文件目录下的 `result.txt`，然后在终端输出。

>  Hint：由于文件读写速度远远快于在终端上输出数字的速度，因此当终端打印结果较慢时，建议您查看项目文件目录下的 `result.txt` 文件查看结果。

对于 $x, y, z$ 中的每一个数字分别考虑，有两种输出方法：

1. 常规记数法输出：输出一个整数，或者一个形如 `整数.非负整数` 的非科学计数法小数。
2. 科学计数法输出：形如 `整数e整数` 或者 `非科学计数法小数e整数`，并且 `e` 之前的 `整数` 或者 `非科学计数法小数` 部分的 **绝对值** 在$[1, 10)$。 

如果这个数字本身的类型就是整数类型，那么将会直接采用常规记数法输出。

否则，项目程序会首先计算按照常规记数法输出需要的字符数，若该字符数不大于设定的最长字符数（程序中设置的默认值为 `decimalMeanLen = 20`），将优先采用常规记数法输出。否则，将会采用科学计数法输出。

另外，在输出数字时，项目程序会自动忽略小数点最后的连续 `0` 的部分，以及大整数的前导 `0`，以便于更加精简的表示输出。

## 程序实现效果

项目文件原代码请见 `calculator.cpp`，使用 `g++ calculator.cpp -o mul` 即可生成可执行程序 `mul`。

在终端输入形如 `.\mul a b` 的命令，即可复现程序。

您可以在项目程序目录下的 `result.txt` 查看运行结果，或者在直接在 `终端` 中查看结果。

接下来的例子是在项目说明文档 `project1.pdf` 所列出的 6 个例子，我们都得到了比较合理的输出。

- 例子 1 ：两个小正整数的乘法操作

  ![image-20220915191414209](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209151914289.png)

- 例子 2 ： 两个小非科学计数法表示的实数的乘法操作

  ![image-20220915191522163](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209151915208.png)

- 例子 3 ： 两个科学计数法表示的小实数的乘法操作

  ![image-20220925024628054](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209250246091.png)

- 例子 4 ：错误：输入不为数字

  ![](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209151917537.png)

- 例子 5 ： 两个稍大正整数的乘法操作

  ![](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209151918016.png)

- 例子 6 ：两个科学记数法表示的实数的乘法操作

  ![image-20220915191938886](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209151919929.png)


事实上，项目说明文档 `project1.pdf` 所列出的 6 个例子，并不足以说明项目所做的所有工作。

接下来我将会列出几个更加复杂的例子，来更好的说明项目所做的所有工作。

- 例子 7：程序支持一位符号位（正数也可以支持一位的符号位）的输入，使用有效位数更多，值域更大。

  ![image-20220916021554066](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160215105.png)

- 例子 8：程序支持使用文件打开数据。

​	如下图所示，在项目程序目录下，新建有 `num1.txt` （其中内容为`-0.31415926e+1`）`num2.txt` （其中内容为`-1e-100`）。

![image-20220916022236242](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160222292.png)

使用命令 `g++ calculator.cpp -o mul` 产生可执行文件 `mul` ，并使用命令 `\mul num1.txt num2.txt` 读入数据。可以发现在终端和 `result.txt` 中同时出现计算结果。

![image-20220916022539438](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160225508.png)

- 例子 9：项目程序认为输入不合法，可能会提示 $5$ 种错误：

  `Too many numbers entered!`

  ![image-20220916023109583](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160231630.png)

  `The entered numbers should be missing!`

  ![image-20220916023155129](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160231172.png)

  `The input cannot be interpret as numbers!`

  ![image-20220916023355598](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160233645.png)

  

  ![image-20220916023503363](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160235418.png)

  `The filename "result.txt" cannot be entered as one of the arguments!`

  ![](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160236604.png)

  `The entered number has too many significant digits!` 

  注意这里我们将`longestSignDigit` 参数的值，从默认值 `1e6` 改成了 `10` ，由于输入的`3.1415926535` 有 `11` 位有效位数，超过了最长的精度长度，所以会报错。

  ![image-20220916024345527](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160243581.png)

- 例子 10：计算两个大整数（有效位数为 `1e6` 的大整数）的乘法，由于在终端输入的方式太花费时间，这里我们采用使用文件输入的方式输入这两个大整数。

  ![image-20220916025255222](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160252299.png)

  执行计算命令`.\mul num1.txt num2.txt` 后，在终端和 `result.txt` 都很快的输出了结果。

  ![image-20220916025435778](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160254875.png)

  值得一提的是，使用 `bigReal` 类的数字进行乘法，可以通过洛谷（一个DSAA 推荐的刷题网站）的 `1e6` 级别的非负整数乘法的题目。

  ![image-20220916025950867](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160259966.png)

  所需要的改动仅仅是将代码的`int main()` 改变为： 

  ```cpp
  int main() { 
      std::string a, b;
      std::cin >> a >> b;
      bigReal num1(a), num2(b);
      std::cout << (num1 * num2).to_string() << std::endl;
      return 0;
  }
  ```

  下面是通过该题目的截图：

  ![image-20220916030209928](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160302001.png)

  源代码为：

  ![image-20220916030748869](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160307933.png)

  您可以在这里查阅本题的通过记录：https://www.luogu.com.cn/record/86711910

  这说明使用 `FFT` 进行的优化是非常有效的，这也可以说明项目程序运行对于大实数有很好的效果。

- 例子 11：程序在输出时，能根据数据的数值，自行选择输出方式是`常规记数法` 还是 `科学计数法` 。这依赖于设置的常规计数法输出的最多字符数 `decimalMeanLen` (默认值为`decimalMeanLen = 20`)

  在下面的例子中，我们更改了最多字符数 `decimalMeanLen`的值为`5`，即如按照常规记数法输出该数字的长度不大于 $5$，将采用常规记数法输出；否则将会采用科学计数法输出。

  需要指出的是，在计算按照常规记数法输出实数需要的字符数的时，算法的时间复杂度只和有效数字的长度线性相关。

  ![](https://raw.githubusercontent.com/Maystern/picbed/main/img/202209160317286.png)

上述的一些例子可以说明本项目程序的功能。

**您也可以尝试更多数据，以测试项目程序的鲁棒性。**

## 项目中出现的难题及解决方案

本次大作业是本课程的第 1 个大作业，总体而言完成任务的难度不大。

如果只采用 `C++` 中自带的简单数字类型，仅仅是完成任务，不是很有意思。

为了解决 `C++ ` 中的简单数字类型会存在的有限范围以及精度较低的问题，我设计了大实数类型，可以在 $O(n \log_2 n)$的时间复杂度内(其中 $n$ 为大实数类型的有效位数)完成两个大实数的乘法运算。

我将项目主要分成四个部分：数据输入、数据存储、数据处理、数据输出。

在数据输入部分中，最大的难题在于**支持读取文件以获取长度较长的数据**和**如何判断数据的合法性情况**。

- 支持读取文件以获取长度较长的数据方面，我先将输入的参数视为文件路径，尝试打开这个文件路径，如果不存在该文件，则将该参数视为数字，判断合法性。
- 如何判断数据的合法性情况方面，我设计了 5 种错误，方便进行数据处理前就检查出可能出现错误的情况，提高了程序的鲁棒性。

在数据存储部分中，最大的难题在于**存储大实数的有效值**。我将一个具有有限位数的大实数视为一个大整数乘以$10$的大整数幂次。存储大实数的有效值的问题就转化为存储两个大整数的问题。我还使用 `vector` 方便进行内存管理，尽量减小无效和重复的内存开销。

在数据处理部分中，最大的难题在于**如何快速计算两个大整数的乘法**。这个问题是本项目的时间瓶颈，我查阅了相关资料，采用了快速傅里叶变换的方式，代替朴素的做法，突破了瓶颈，将项目的时间复杂度瓶颈从$O(n^2)$减小到了$O(n \log_2 n)$ (其中 $n$ 为大实数类型的有效位数)并且在测试中取得了不错的效果。

在数据输出部分中，最大的难题在于**如何让实数按照合理的方式选择输出方式**。我们知道，表示大实数的方式有小数点表示法和科学记数表示法。后者对于任何的大实数都能够工作，而前者与$10$的大整数幂次这个可能很大的值有关。因此，我先尝试采用小数点表示法，如果发现输出非常大（字符数大于设定的 `decimalMeanLen` 默认值为`20`）那么采用科学记数表示法，否则有限选用小数点表示法。这样数据显示适应于使用者的阅读习惯，还是非常合理的。

## 一些问题

虽然此项目在功能上我实现了自认为比较满意的效果。但我认为自己还是在一些方面存在不足，需要在后续的学习和代码时间中进行继续学习和补充：

1. 关于码风：我对`Google C++ Style` 的理解还并不全面，或许只停留在代码格式的层面上，在后续的学习中我会学习如何写出更加规范的代码，而不是仅仅只注重解决问题。
2. 关于项目管理：由于本项目中“使用 1 个 C++ 文件进行提交”作为其中一个要求，在未来项目的探索中，为进一步维护项目，应将代码按照功能分为不同的部分，再使用makefile生成相关可执行文件。
3. 关于指针和内存管理：本项目大量的采用`vector` 进行数据处理。接下来的学习中，应该避免自己使用过多的`STL`容器，而是采用更一般的数据类型，锻炼自己对于指针和内存管理的能力。

## 后记

因为项目编程和报告撰写所花时间有限，本次项目可能存在许多瑕疵和不足，

非常欢迎您对此提出宝贵的批评与意见。

非常感谢您能看到这里！









 
