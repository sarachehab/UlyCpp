typedef int *x;

int f()
{
    int value = 42;
    x ptr = &value;

    *ptr = 100;

    return value;
}
