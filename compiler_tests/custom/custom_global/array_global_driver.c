#include <stdio.h>

float f();

int main()
{
    printf("Function returns %f", f());
    return !(f() == 1.1f);
}
