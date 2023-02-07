#include <iostream>
using std::cout;
using std::endl;
struct point{
    float x;
    float y;
    void setPointValue(int x, int y) {
        this->x = x;
        this->y = y;
    }
    point getMiddlePoint(point *p) {
        point res;
        res.x = (x + p->x) / 2.0;
        res.y = (y + p->y) / 2.0;
        return res;
    }
};

int main() {
    point A, B;
    A.setPointValue(1, 2);
    B.setPointValue(2, 3);
    point C = A.getMiddlePoint(&B);
    cout << C.x << " " << C.y << endl;  
    return 0;
}