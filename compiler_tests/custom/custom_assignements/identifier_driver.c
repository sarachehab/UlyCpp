#include <stdio.h>

int f(int x);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %d\n", f(5));

    return !(f(5) == 50);
}
