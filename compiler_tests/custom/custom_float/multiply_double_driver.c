#include <stdio.h>

double f(double a, double b);

int main()
{
    double a = 4.0;
    double b = 5.2;

    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(a, b));

    double x = 20.8;

    return !(f(a, b) == x);
}
