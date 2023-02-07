#include <iostream>
using std::cout;
using std::endl;
enum Day {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
enum Weather {Sunny, Rainy, Cloudy, Snowy, Windy};
struct DayInfo {
    Day day;
    Weather weather;
};
bool canTravel(DayInfo dayinfo) {
    if (dayinfo.day != Saturday && dayinfo.day != Sunday) return false;
    if (dayinfo.weather == Rainy || dayinfo.weather == Snowy) return false;
    return true;
}
int main() {
    DayInfo dayinfo = {Sunday, Sunny};
    if (canTravel(dayinfo)) {
        cout << "Let's go out!" << endl;
    } else {
        cout << "Oh Sad!" << endl;
    }
    return 0;
}