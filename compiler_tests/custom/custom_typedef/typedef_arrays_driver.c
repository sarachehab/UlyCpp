int f(int x);

int main()
{
    for (int i = 0; i < 10; i++)
    {
        printf("f(%d): %d", i, f(i));
        if (f(i) != i)
        {
            return 1;
        }
    }
    return 0;
}
