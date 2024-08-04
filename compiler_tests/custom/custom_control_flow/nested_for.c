int f(int x){
    int i;
    for (i = 0; i < 2; i++) {
        for (x = 0; x < 4; x++) {
            x = x + 1;
        }
    }
    return x;
}
