#include <stdio.h>

int f();

int main()
{
    printf("function returned with: %d", f());
    return !(f() == 1);
}
