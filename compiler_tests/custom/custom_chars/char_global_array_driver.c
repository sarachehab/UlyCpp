#include <stdio.h>

char f();

int main()
{

    return !((f(0) == 'h') && (f(1) == 'e') && (f(2) == 'l'));
}
