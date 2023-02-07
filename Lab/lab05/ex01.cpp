#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main() {
    int *a = new int [5];
    for (int i = 0; i < 5; i++)
        cin >> a[i];
    int *p = a + 4;
    for (int i = 0; i < 5; i++, p--) {
        cout << *p << " ";
    }
    cout << endl;
    return 0;
}