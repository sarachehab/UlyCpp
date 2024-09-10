typedef int MyInt;

int g(MyInt x, MyInt y)
{
    return x + y;
}

int f()
{
    MyInt x = 10, y = 32;
    return g(x, y);
}
