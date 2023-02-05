#include <iostream>
#include "fib.hpp"
using std::cin;
using std::cout;
using std::endl;
int main() {
    int n = -1;
    while (n <= 0) {
        cout << "Please input a positive integer:";
        cin >> n;
    }
    for (int i = 1; i <= n; i++) {
        cout << fib(i) << '\t';
        if (i % 10 == 0 && i != n) cout << endl;
    }
    cout << endl;
    return 0;
}