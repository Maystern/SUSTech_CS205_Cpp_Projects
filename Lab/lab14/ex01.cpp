#include <iostream>
#include <cstring>
#include <iomanip>
using std::exception;
using std::fixed;
using std::cout;
using std::endl;
using std::cin;
using std::setprecision;
class OutOfRangeException : public exception {   
    private:
        char errorStatement[105]; 
    public:
        OutOfRangeException(const char * errorStatement) {
            memcpy(this->errorStatement, errorStatement, sizeof(this->errorStatement));
        }
        const char * what() const throw() {
            return errorStatement;
        }
};
float calculateAverage(int score1, int score2, int score3, int score4) {
    if (score1 < 0 || score1 > 100) {
        char res[105];
        sprintf(res, "The parameter 1 is %d which out of range(0-100).", score1);
        throw OutOfRangeException(res);
    }
    if (score2 < 0 || score2 > 100) {
        char *res = new char [105];
        sprintf(res, "The parameter 2 is %d which out of range(0-100).", score2);
        throw OutOfRangeException(res);
    }
    if (score3 < 0 || score3 > 100) {
        char *res = new char [105];
        sprintf(res, "The parameter 3 is %d which out of range(0-100).", score3);
        throw OutOfRangeException(res);
    }
    if (score4 < 0 || score4 > 100) {
        char *res = new char [105];
        sprintf(res, "The parameter 4 is %d which out of range(0-100).", score4);
        throw OutOfRangeException(res);
    }
    return (score1 + score2 + score3 + score4) / 4.0;
}
int main() {
    char ch;
    do {
        cout << "Please enter marks for 4 courses:";
        int score1, score2, score3, score4;
        cin >> score1 >> score2 >> score3 >> score4;
        float res;
        try {
            res = calculateAverage(score1, score2, score3, score4);
            cout << "The average of the four courses is " << fixed << setprecision(2) << res << endl;
        } catch (OutOfRangeException e) {
            cout << e.what() << endl;
        }
        do {
            cout << "Would you want to enter another marks for 4 courses(y/n)?";
            cin >> ch;
        } while (ch != 'y' && ch != 'n');
    } while (ch == 'y');
    cout << "Bye, see you next time." << endl;
    return 0;
}