#include <stdio.h>

int f(int i);

int main()
{

    printf("Function returning %d", f(0));
    return !((f(0) == 1) &&
             (f(1) == 10) &&
             (f(2) == 6) &&
             (f(3) == 5));
}
