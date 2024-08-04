int f(){
    int x = 0;
    int i = 0;
    while (i < 3) {
        int j = 0;
        while (j < 2) {
            x = x + 1;
            j = j + 1;
        }
        i = i + 1;
    }
    return x;
}
