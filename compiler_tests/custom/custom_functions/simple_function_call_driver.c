#include <stdio.h>

int g();

int main()
{
    printf("Hello from RISC-V\n");

    return !(g() == 10);
}
