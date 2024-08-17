int **x;

int f()
{
    int p = 5;
    int *q = &p;
    x = &q;
    **x = 10;
    return p;
}
