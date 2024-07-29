#include <stdio.h>

int f(double a);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", f(4.2));

    return !(f(4.2) == 1);
}
