#include <stdio.h>

float f();

void test(double a)
{
    printf("Test function produced value: %f\n", (float)a + 3.2f);
}

int main()
{
    printf("Hello from RISC-V\n");

    test(5.5);
    printf("Example function returned: %f\n", f());

    float result = 4.2f + 5.1f;

    return !(f() == result);
}
