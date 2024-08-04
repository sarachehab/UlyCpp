int f(){
    int x = 0;
    while (x < 2){
        int y = 0;
        while (y < 3){
            if (y == 2){
                break;
            }
            y = y + 1;
        }
        x = x + 1;
    }
    return x;
}
