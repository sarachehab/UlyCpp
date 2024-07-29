#include <stdio.h>

int f();

int main()
{
    printf("Hello from RISC-V\n");

    return !(f() == 1);
}
