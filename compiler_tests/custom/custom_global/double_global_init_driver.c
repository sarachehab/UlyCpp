#include <stdio.h>

double f();

int main()
{
    printf("Function returns %f", f());
    double x = 1.2l;
    return !(f() == x);
}
