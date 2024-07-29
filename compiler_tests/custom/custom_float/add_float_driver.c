#include <stdio.h>

float f(float x);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(1.0));

    return !(f(1.0) == 2.0f);
}
