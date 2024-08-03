

#include <stdio.h>

double pow(int i, double r);

int main()
{
    double r  = 1.1, sol = 1.4641;
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", f(4, r));

    return !(pow(4, r) == sol);
}
