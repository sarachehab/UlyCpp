int f() {
    return 6;
}

int g(int x) {
    int count = 0;
    int i = 0;
    for (i = 0; i < x; i++) {
        count += f();
    }
    return count;
}

int h(int x, int y) {
    return g(x) + g(y);
}
