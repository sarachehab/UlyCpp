#include <stdio.h>

int f();


int main()
{
    printf("Hello from RISC-V\n");

    printf("Example function returned: %d\n", f(3, 10));

    return !(f(3, 10) == 3);
}
