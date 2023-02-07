#include <iostream>
using std::cout;
using std::endl;
using std::cin;
const int N = 105;
char *match(char *s, char ch);
char *match(char *s, char ch) {
    char *p = s;
    while (*p != '\0') {
        if (*p == ch) return p;
        p++;
    }
    return NULL;
}
int main() {
    cout << "Please input a string:" << endl;
    char str[N];
    cin.getline(str, N);
    cout << "Please input a character:" << endl;
    char ch;
    cin >> ch;
    char *ans = match(str, ch);
    if (ans == NULL) {
        cout << "Not Found" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}