#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Error 1: Accessing uninitialized variable
    int uninitialized_variable;
    printf("%d\n", uninitialized_variable);

    // Error 2: Memory leak
    char *leaked_memory = (char *)malloc(10);
    // Forgot to free(leaked_memory);

    // Error 3: Division by zero
    int numerator = 5;
    int denominator = 0;
    int result = numerator / denominator;

    // Error 4: Buffer overflow
    char buffer[5];
    snprintf(buffer, sizeof(buffer), "This is a longer string");

    // Error 5: Unused variable
    int unused_variable;

    return 0;
}
