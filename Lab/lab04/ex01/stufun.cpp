#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include "stuinfo.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::sort;
using std::fixed;
using std::setprecision;
void inputstu(stuinfo stu[] , int n) {
    cout << "Please input information of " << n << " students:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << i << "'s name:";
        do {
            cin.getline(stu[i].name, 20);
        } while (strlen(stu[i].name) == 0);
        cout << "Student " << i << "'s scores:";
        stu[i].ave = 0;
        for (int j = 0; j < 3; j++) {
            cin >> stu[i].score[j];
            stu[i].ave += stu[i].score[j];
        }
        stu[i].ave /= 3.0;
    }
}
void showstu(stuinfo stu[] , int n) {
    cout << "The information of " << n << " students you input are:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << i << " name: " << stu[i].name << ", scores: ";
        for (int j = 0; j < 3; j++)
            cout << (int) stu[i].score[j] << " ";
        cout << endl;
    }
}
bool cmp(stuinfo stu1, stuinfo stu2) {
    return stu1.ave > stu2.ave;
}
void sortstu(stuinfo stu[] , int n) {
    sort(stu, stu + n, cmp);
    cout << "The descending order of the students:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Student " << i << " name: " << stu[i].name << ", scores: ";
        for (int j = 0; j < 3; j++)
            cout << (int) stu[i].score[j] << " ";
        cout << " average: " << fixed << setprecision(4) << stu[i].ave << endl;
    }
}
bool findstu(stuinfo stu[] , int n, char ch[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(stu[i].name, ch) == 0) return true;
    }
    return false;
}