#include <iostream>
#include <assert.h>
#include <iomanip>
using std::exception;
using std::fixed;
using std::cout;
using std::endl;
using std::cin;
using std::setprecision;
float calculateAverage(int score1, int score2, int score3, int score4) {
    assert(score1 >= 0 && score1 <= 100);
    assert(score2 >= 0 && score2 <= 100);
    assert(score3 >= 0 && score3 <= 100);
    assert(score4 >= 0 && score4 <= 100);
    return (score1 + score2 + score3 + score4) / 4.0;
}
int main() {
    char ch;
    do {
        cout << "Please enter marks for 4 courses:";
        int score1, score2, score3, score4;
        cin >> score1 >> score2 >> score3 >> score4;
        float res = calculateAverage(score1, score2, score3, score4);
        cout << "The average of the four courses is " << fixed << setprecision(2) << res << endl;
        do {
            cout << "Would you want to enter another marks for 4 courses(y/n)?";
            cin >> ch;
        } while (ch != 'y' && ch != 'n');
    } while (ch == 'y');
    cout << "Bye, see you next time." << endl;
    return 0;
}