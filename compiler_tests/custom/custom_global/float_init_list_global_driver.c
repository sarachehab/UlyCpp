#include <stdio.h>

float f();

int main()
{
    printf("Function returns %f", f());
    float x = 4.0;
    return !(f() == x);
}
