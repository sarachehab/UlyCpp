
int f();

int g(int x) {
    int count = 0;
    for (int i = 0; i < x; i++) {
        count += f();
    }
    return count;
}

int h(int x, int y) {
    return g(x) + g(y);
}


int main()
{
    return !(h(8, 7)==90);
}
