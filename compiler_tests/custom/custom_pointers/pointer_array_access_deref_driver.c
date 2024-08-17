
int *f(int *x);

int main()
{
    int x[2] = {1, 2};
    return !(*f(x) == x[1]);
}
