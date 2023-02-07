#include <iostream>
#include <cmath>
#include "math.h"
using std::cin;
using std::cout;
using std::endl;
class CStereoShape {
    private:
        static size_t numberOfObject;
    public:
        void addNumberOfObject() {
            numberOfObject++;
        }
        void delNumberOfObject() {
            numberOfObject--;
        }
        virtual float GetArea() {
            cout << "CStereoShape::GetArea()" << endl;
            return 0.0;
        }
        virtual float GetVolume() {
            cout << "CStereoShape::GetVolume()" << endl;
            return 0.0;
        }
        virtual void show() {
            cout << "CStereoShape::Show()" << endl;
        }
        virtual ~CStereoShape() {
            numberOfObject--;
        }
        size_t GetNumOfObject() {
            return numberOfObject;
        }
};
size_t CStereoShape::numberOfObject = 0;
class CCube: public CStereoShape {
    private:
        float length, width, height;
    public:
        void setLength(float length) {this->length = length;}
        void setWidth(float width) {this->width = width;}
        void setHeight(float height) {this->height = height;}
        float getLength() const {return length;}
        float getWidth() const {return width;}
        float getHeight() const {return height;}
        CCube(float length = 0, float width = 0, float height = 0):
            length(length), width(width), height(height) {
                addNumberOfObject();
            }
        CCube (const CCube & c) {
            length = c.getLength();
            height = c.getHeight();
            width = c.getWidth();
            addNumberOfObject();
        }
        ~CCube() {
            delNumberOfObject();
        }
        float GetArea() {
            return 2.0 * (length * width + length * height + width * height);
        }
        float GetVolume() {
            return length * width * height;
        }
        void show() {
            cout << "Cube length:" << length << "\t" << "width:" << width << "\t" << "height:" << height << endl;
            cout << "Cube area:" << GetArea() << "\t" << "volume:" << GetVolume() << endl;
        }
};
class CSphere: public CStereoShape {
    private:
        float radius;
    public:
        void setRadius(float radius) {this-> radius = radius;}
        float getRadius() const {return radius;}
        CSphere(float radius = 0): radius(radius){
            addNumberOfObject();
        }
        CSphere(const CSphere & c) {
            radius = c.getRadius();
            addNumberOfObject();
        }
        ~CSphere() {
            delNumberOfObject();
        }
        float GetArea() {
            return 4 * M_PI * radius * radius;
        }
        float GetVolume() {
            return 4.0 * M_PI * radius * radius * radius / 3.0;
        }
        void show() {
            cout << "Sphere radius:" << radius << "\t" << "area:" << GetArea() << "\t" << "volume:" << GetVolume() << endl;
        }
};
int main() {
    CStereoShape *p;
    CCube a_cube(4.0, 5.0, 6.0);
    CSphere c_sphere(7.9);
    p = &a_cube; p->show();
    p = &c_sphere; p->show();
    cout << p->GetNumOfObject() << " objects are created." << endl;
    return 0;
}