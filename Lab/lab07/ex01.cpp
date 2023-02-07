#include <iostream>
using std::endl;
using std::cout;
void displaySquare(int side = 4, char filledCharacter = '*') {
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            cout << filledCharacter;
        }
        cout << endl;
    }
}
int main() {
    displaySquare(); // default arguments 
    displaySquare(5, '#'); //non-default arguments 
    return 0;
}