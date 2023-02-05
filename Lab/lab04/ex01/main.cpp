#include "stuinfo.hpp"
#include "iostream"
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
const int n = 5;
int main() {
    stuinfo stu[n];
    inputstu(stu, n);
    showstu(stu, n);
    cout << endl;
    sortstu(stu, n);
    cout << endl;
    cout << "Please input the name you want to find:";
    char name[20];
    do {
        cin.getline(name, 20);
    } while (strlen(name) == 0);
    if (findstu(stu, n, name)) {
        cout << name << " is in the students list." << endl;
    } else {
        cout << name << " is not in the student list." << endl;
    }
    return 0;
}