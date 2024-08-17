#include <stdio.h>

double x[2] = {1.0l, 2.0l};

double f(double *x);

int main()
{
    printf("function returns: %d\n", f(x));

    return !(f(x) == 2.0l);
}
