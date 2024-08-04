int f(int x, int y) {
    int count = 0;
    int i = x;
    for (i; i < 3; i++) {
        while (y < 3){
            if (y == 2){
                break;
            }
            y = y + 1;
        }
        if (i == 2){
            continue;
        }
    }
    return i;
}
