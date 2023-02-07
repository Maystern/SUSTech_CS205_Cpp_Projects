#include <iostream>
using std::cout;
using std::endl;
int vabs(int * p, int n) {
    int res = 0;
    for (int i = 0; i < n; i++)
        res += p[i];
    return res;
}
int vabs(int * p, size_t n) {
    int res = 0;
    for (size_t i = 0; i < n; i++)
        res += p[i];
    return res;
}
float vabs(float * p, int n) {
    float res = 0;
    for (int i = 0; i < n; i++)
        res += p[i];
    return res;
}
float vabs(float * p, size_t n) {
    float res = 0;
    for (size_t i = 0; i < n; i++)
        res += p[i];
    return res;
}
double vabs(double * p, int n) {
    double res = 0;
    for (int i = 0; i < n; i++)
        res += p[i];
    return res;
}
double vabs(double * p, size_t n) {
    double res = 0;
    for (size_t i = 0; i < n; i++)
        res += p[i];
    return res;
}
int main() {
    int p_int[] = {1, 2, 3, 4, 5};
    float p_float[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double p_double[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << vabs(p_int, 5) << endl;
    cout << vabs(p_float, 5) << endl;
    cout << vabs(p_double, 5) << endl;
    cout << vabs(p_int, (size_t) 5) << endl;
    cout << vabs(p_float, (size_t) 5) << endl;
    cout << vabs(p_double, (size_t) 5) << endl;
    return 0;
}