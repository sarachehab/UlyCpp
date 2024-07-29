#include <stdio.h>

float f(float a);

int main()
{
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(4.0));

    return !(f(4.0) == 20.799999f);
}
