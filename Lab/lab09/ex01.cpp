#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const float eps = 1e-7;
class Complex {
    private:
        float real;
        float imag;
    public:
        Complex(float real = 0, float imag = 0) {
            this->real = real;
            this->imag = imag;
        }
        Complex add (const Complex &c) {
            Complex res;
            res.imag = this->imag + c.imag;
            res.real = this->real + c.real;
            return res;
        }
        Complex subtract(const Complex &c) {
            Complex res;
            res.imag = this->imag - c.imag;
            res.real = this->real - c.real;
            return res;
        }
        void display() const {
            cout << this->real;
            if (imag < 0) cout << this->imag << "i";
            else cout << "+" << this->imag << "i";
            cout << endl;
        }
};
int main() {
    Complex a(1, -4);
    Complex b(2, 3);
    a.add(b).display(); // 1 - 4i + 2 + 3i = 3 - i
    b.subtract(a).display(); // 2 + 3i - (1 - 4i) = 1 + 7i 
    return 0;
}