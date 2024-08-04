

#include <stdio.h>

double pow(int i, double r);

double emulate(int i, double r)
{
    if (i == 0)
    {
        return 1.0l;
    }
    return r * pow(i - 1, r);
}

int main()
{
    double sol = 1.4641;
    printf("Hello from RISC-V\n");
    printf("Example function returned: %f\n", pow(4, 1.1l));

    return !(pow(4, 1.1l) == emulate(4, 1.1l));
}
