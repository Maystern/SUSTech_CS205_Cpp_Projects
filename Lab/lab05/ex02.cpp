#include <iostream>
using std::cout;
using std::endl;
int main() {
    int *a = (int*) malloc(sizeof(int) * 5);
    int *p = a;
    for (int i = 0; i < 5; i++, p++) {
        *p = i;
    }
    for (int i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    // modify the element out of range and print them
    for (int i = 5; i < 10; i++, p++) {
        *p = i;
    }
    for (int i = 5; i < 10; i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}