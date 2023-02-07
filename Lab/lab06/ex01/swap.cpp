#include "swap.h"
void swap1(int a, int b) {
    int t = a;
    a = b;
    b = t;
}
void swap2(int *a, int *b) {
    int *t = a;
    a = b;
    b = t;
}
void swap3(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}