#include <stdio.h>

int f();

int main(){

    printf("Function returning %d", f());
    return !(f() == 4);
}