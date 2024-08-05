int f(int i)
{
    int x[4] = {1, 4, 6};
    x[1] = 4 + 6;
    x[3] = 5;
    return x[i];
}
