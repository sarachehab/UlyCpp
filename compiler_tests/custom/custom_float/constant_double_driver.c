#include <stdio.h>

double f();

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f());

    return !(f() == 3.200000);
}
