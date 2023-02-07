#include <iostream>
#include "swap.h"
using std::endl;
using std::cout;
using std::cin;
int main() { 
    {
        int a = 1, b = 2;
        swap1(a, b);
        cout << a << " " << b << endl;
    }
    {
        int a = 1, b = 2;
        swap2(&a, &b);
        cout << a << " " << b << endl;
    }
    {
        int a = 1, b = 2;
        swap3(a, b);
        cout << a << " " << b << endl;
    }
    return 0;
}