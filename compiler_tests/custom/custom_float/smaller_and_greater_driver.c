#include <stdio.h>

int f(double a, double b);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", f(5.9, 3.6));

    return !(f(5.9, 3.6) == 0);
}
