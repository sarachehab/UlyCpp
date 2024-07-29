#include <stdio.h>

int f(double a, double b);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", f(4.0, 3.0));

    return !(f(4.0, 3.0) == 0);
}
