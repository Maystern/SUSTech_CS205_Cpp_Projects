#include <iostream>
#include "fac.h"
using std::cin;
using std::cout;
using std::endl;
int main() {
    int n = -1;
    while (n <= 0) {
        cout << "Please input a positive integer:";
        cin >> n;
    }
    for (int i = 1; i <= n; i++) 
    cout << i << "!" << " = " << fac(i) << endl;
    return 0;
}