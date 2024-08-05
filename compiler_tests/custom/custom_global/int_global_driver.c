#include <stdio.h>

int f();

int main(){
    printf("Function returns %d", f());
    return ! (f() == 1);
}