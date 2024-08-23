enum try
{
    hello,
    its,
    me
};

int f()
{
    enum try x;
    x = its;
    return x;
}
