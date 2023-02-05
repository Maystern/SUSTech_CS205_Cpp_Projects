#include <stdio.h>
#include <stdbool.h>
int main() {
    /*
        warnings are:
        printf("\nPrint size of the fundamental types:\n");
        printf("-----------------------------------------\n");
        printf("The sizeof(char) is: %d bytes.\n", sizeof(char));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(short) is: %d bytes.\n", sizeof(short));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(int) is: %d bytes.\n", sizeof(int));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(long) is: %d bytes.\n", sizeof(long));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(long long) is: %d bytes.\n", sizeof(long long));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(float) is: %d bytes.\n", sizeof(float));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(double) is: %d bytes.\n", sizeof(double));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(long double) is: %d bytes.\n", sizeof(long double));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
        printf("The sizeof(bool) is: %d byte.\n", sizeof(bool));
        // warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
    */
    // correct:
    printf("\nPrint size of the fundamental types:\n");
    printf("-----------------------------------------\n");
    printf("The sizeof(char) is: %ld bytes.\n", sizeof(char));
    printf("The sizeof(short) is: %ld bytes.\n", sizeof(short));
    printf("The sizeof(int) is: %ld bytes.\n", sizeof(int));
    printf("The sizeof(long) is: %ld bytes.\n", sizeof(long));
    printf("The sizeof(long long) is: %ld bytes.\n", sizeof(long long));
    printf("The sizeof(float) is: %ld bytes.\n", sizeof(float));
    printf("The sizeof(double) is: %ld bytes.\n", sizeof(double));
    printf("The sizeof(long double) is: %ld bytes.\n", sizeof(long double));
    printf("The sizeof(bool) is: %ld byte.\n", sizeof(bool));

    return 0;
   
}