# include <bits/stdc++.h>
using namespace std;
int main() {
    freopen("num2.txt", "w", stdout);
    srand(time(NULL));
    cout << rand() % 9 + 1;
    for (int i = 2; i <= 1000000; i++)
        cout << rand() %10;
    return 0;
}