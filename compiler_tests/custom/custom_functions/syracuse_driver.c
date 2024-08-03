#include <stdio.h>

int f(int x);

int g(int x);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", g(28));

    return !(g(28) == 18);
}
