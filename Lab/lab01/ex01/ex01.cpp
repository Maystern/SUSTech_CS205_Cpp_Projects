#include <iostream>
#include <cstdio>
#include <iomanip>
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
int main() {
    float num1 = 0.1f, num2 = 0.2f, num3 = 0.3f;
    // use "cout"
    cout << fixed << setprecision(2) << num1 << endl;
    cout << fixed << setprecision(2) << num2 << endl;
    cout << fixed << setprecision(2) << num3 << endl;
    // use "printf"
    printf("%.2f\n", num1);
    printf("%.2f\n", num2);
    printf("%.2f\n", num3);
    return 0;
}