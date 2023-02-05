#include <iostream>
using std::cout;
using std::endl;
long long mul(int num1, int num2) {
    return (long long) num1 * num2;
}
int main() {
    int num1 = 56789;
    int num2 = 23456789;
    cout << mul(num1, num2) << endl;
    return 0;
}