#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
class Complex {
    private:
        float real, imag;
    public:
        Complex(float real = 0, float imag = 0) {
            this->real = real; this->imag = imag;
        }
        inline void setReal(float real) { this->real = real; }
        inline void setImag(float imag) { this->imag = imag; }
        inline float getReal() const { return this->real; }
        inline float getImag() const { return this->imag; }
        Complex operator+ (const Complex &c) const;
        Complex operator- (const Complex &c) const;
        Complex operator* (const Complex &c) const;
        Complex& operator= (const Complex &c);
        bool operator== (const Complex &c) const;
        bool operator!= (const Complex &c) const;
        friend ostream& operator << (ostream &os, const Complex& c);
        friend istream& operator >> (istream &is, Complex& c);
};
Complex Complex::operator+ (const Complex &c) const {
    Complex res;
    res.setReal(this->real + c.getReal());
    res.setImag(this->imag + c.getImag());
    return res;
}
Complex Complex::operator- (const Complex &c) const {
    Complex res;
    res.setReal(this->real - c.getReal());
    res.setImag(this->imag - c.getImag());
    return res;
}
Complex Complex::operator* (const Complex &c) const {
    Complex res;
    res.setReal(this->real * c.getReal() - this->imag * c.getImag());
    res.setImag(this->real * c.getImag() + this->imag * c.getReal());
    return res;
}
Complex& Complex::operator= (const Complex &c) {
    this->imag = c.getImag();
    this->real = c.getReal();
    return *this;
}
bool Complex::operator== (const Complex &c) const {
    if (this->imag != c.getImag() || this->real != c.getReal()) {
        return false;
    } else {
        return true;
    }
}
bool Complex::operator!= (const Complex &c) const {
    if (this->imag != c.getImag() || this->real != c.getReal()) {
        return true;
    } else {
        return false;
    }
}
ostream& operator << (ostream &os, const Complex& c) {
    float real = c.getReal(), imag = c.getImag();
    os << real;
    if (imag < 0) os << imag << "i";
    else os << "+" << imag << "i";
    return os;
}
istream& operator >> (istream &is, Complex& c) {
    float real, imag;
    is >> real >> imag;
    c.setImag(imag);
    c.setReal(real);
    return is;
}
int main() {
    Complex a, b;
    cin >> a >> b;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    a = b;
    cout << a << " " << b << endl;
    cout << (a == b) << endl;
    cout << (a != b) << endl;
    return 0;
}