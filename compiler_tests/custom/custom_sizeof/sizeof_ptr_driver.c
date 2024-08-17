#include <stdio.h>

int f();

int main()
{
    printf("Hello from RISC-V\n");
    double y = 0;
    double *x = &y;

    printf("sizeof(x + 1) = %d\n", sizeof(x + 1));
    printf("f() = %d\n", f());

    return !(f() == sizeof(x + 1));
}
