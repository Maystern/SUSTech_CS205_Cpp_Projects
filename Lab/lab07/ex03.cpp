#include <iostream>
using std::cout;
using std::endl;
template <typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
}
int main() {
    int a1 = 1, b1= 2;
    cout << minimum(a1, b1) << endl;
    char a2 = 'A', b2 = 'B';
    cout << minimum(a2, b2) << endl;
    float a3 = 1.1, b3 = 1.2;
    cout << minimum(a3, b3) << endl; 
    return 0;
}