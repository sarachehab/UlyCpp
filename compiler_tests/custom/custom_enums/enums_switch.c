int f(int x)
{
    enum X
    {
        hello,
        its = 2,
        me
    };

    switch (x)
    {
    case hello:
        return hello;
    case its:
        return its;
    case me:
        return me;
    default:
        return 1;
    }
}
