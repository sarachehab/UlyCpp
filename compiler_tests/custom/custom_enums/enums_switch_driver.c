int f(int x);

int main()
{
    return !(f(0) == 0 && f(2) == 2 && f(3) == 3 && f(1) == 1 && f(100) == 1);
}
