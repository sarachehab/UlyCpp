typedef int MyInt;

int g(MyInt x, int y)
{
    return x + y;
}

int f()
{
    MyInt x = 10, z = 2;
    int y = 30;
    return g(x, y) + z;
}
