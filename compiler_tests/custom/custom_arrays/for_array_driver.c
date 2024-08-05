#include <stdio.h>

int f(int v);

int main()
{
    printf("function returned with: %d \n", f(0));
    printf("function returned with: %d \n", f(1));
    printf("function returned with: %d \n", f(2));
    printf("function returned with: %d \n", f(3));
    printf("function returned with: %d \n", f(4));
    printf("function returned with: %d \n", f(5));
    printf("function returned with: %d \n", f(6));
    printf("function returned with: %d \n", f(7));

    return 
        ! (
              (f(0) == 8)
            | (f(1) == 9)
            | (f(2) == 10)
            | (f(3) == 11)
            | (f(4) == 12)
            | (f(5) == 13)
            | (f(6) == 14)
            | (f(7) == 15)
        );
}
