
int f();

int main()
{
    int x[2];
    x[0] = 13;

    int *p = f(x);
    return !(p[0] == 13);
}
