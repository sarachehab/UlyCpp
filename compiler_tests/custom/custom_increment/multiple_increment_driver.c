#include <stdio.h>

int f(int x);

int main()
{
    printf("Hello from RISC-V\n");

    return !(f(1) == 3);
}
