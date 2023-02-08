#include <iostream>
using std::cout;
using std::endl;
class Car {
    friend class Driver;
    private:
        enum {Off, On};
        enum {Minvel, Maxvel = 200};
        int mode;
        int velocity;
    public:
        Car(int m = On, int v = 50): mode(m), velocity(v) {}
        bool velup(int v);
        bool veldown(int v);
        bool ison() const;
        int getvel() const;
        void showinfo() const;
};
class Driver {
    public:
        bool velup(Car& car, int v);
        bool veldown(Car& car, int v);
        void setmode(Car& car);
        bool ison(Car& car) const;
};
bool Car::velup(int v) {
    if (velocity + v > 200) {
        cout << "The velocity is " << velocity + v << ". It is out of Maxvel." << endl;
        return false;
    }
    velocity += v;
    return true;
}
bool Car::veldown(int v) {
    if (velocity - v < 0) {
        cout << "The velocity is " << velocity - v << ". It is below Minvel." << endl;
        return false;
    }
    velocity -= v;
    return true;
}
bool Car::ison() const { return mode == On; }
int Car::getvel() const { return velocity; }
void Car::showinfo() const {
    cout << "The information of car:mode is " << (ison() ? "On" : "Off") << ", velocity is " << velocity << endl;
}
bool Driver::velup(Car& car, int v) {
    if (car.velocity + v > 200) {
        cout << "The velocity is " << car.velocity + v << ". It is out of Maxvel." << endl;
        return false;
    }
    car.velocity += v;
    return true;
}
bool Driver::veldown(Car& car, int v) {
    if (car.velocity - v < 0) {
        cout << "The velocity is " << car.velocity - v << ". It is below Minvel." << endl;
        return false;
    }
    car.velocity -= v;
    return true;
}
void Driver::setmode(Car& car) {
    if (car.mode == car.On) car.mode = car.Off;
    else car.mode = car.On;
}
bool Driver::ison(Car& car) const {
    return car.mode == car.On;
}
int main() {
    Car car;
    car.showinfo();
    car.velup(120);
    cout << "Increase velocity by car, its mode is " << (car.ison() ? "On" : "Off") << ", velocity is " << car.getvel() << endl;
    cout << "Set the mode of car by driver:" << endl;
    Driver driver;
    cout << "The mode if car is:" << (driver.ison(car) ? "On" : "Off") << '.' << endl;
    driver.setmode(car);
    car.showinfo();
    driver.veldown(car, 100);
    cout << "Decrese velocity by driver: mode is " << (car.ison() ? "On" : "Off") << ", velocity is " << car.getvel() << endl;
    cout << "Increse velocity by driver:";
    driver.velup(car, 150);
    return 0;
}