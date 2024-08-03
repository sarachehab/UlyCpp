#include <stdio.h>

int f();

int g(int x);

int h(int x, int y);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", h(8, 7));

    return !(h(8, 7) == 90);
}
