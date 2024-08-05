#include <stdio.h>
double f();

int main()
{
    printf("function returned with: %d", f());
    return !(f() == 1.0l);
}
