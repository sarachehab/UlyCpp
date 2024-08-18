char x = 'd';

void g()
{
    x = 'e';
}

char f()
{
    g();
    return x;
}
