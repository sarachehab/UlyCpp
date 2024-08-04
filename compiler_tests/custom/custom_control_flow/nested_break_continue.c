int f(){
    int x;
    for (x = 0; x < 3; x++) {
        int y = 0;
        while (y < 3){
            if (y == 2){
                break;
            }
            y = y + 1;
        }
        if (x == 2){
            continue;
        }
    }
    return x;
}
