int f()
{
    double y = 0.0l;
    double *x = &y;
    return sizeof(x + 1);
}
