#include <stdio.h>

int main() {
    int x = 42;       // Declare an integer variable
    int *ptr = &x;    // Declare a pointer and assign the address of x to it

    printf("Value of x: %d\n", x);           // Print the value of x directly
    printf("Value of x using pointer: %d\n", *ptr);  // Dereference the pointer to access the value of x

    return 0;
}