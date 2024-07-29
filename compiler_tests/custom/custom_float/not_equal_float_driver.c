#include <stdio.h>

int f(float a, float b);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(4.0, 5.2));

    return !(f(4.0, 5.2) == 1);
}
