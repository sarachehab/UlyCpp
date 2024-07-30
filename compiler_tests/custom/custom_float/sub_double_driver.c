#include <stdio.h>

double f(double x);

int main()
{
    double x = 1.0, y = 2.2;
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(x));

    double result = x + y;

    return !(f(x) == result);
}
