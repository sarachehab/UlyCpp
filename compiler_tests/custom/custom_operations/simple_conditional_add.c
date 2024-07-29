int f(){
    int x = 2;
    int y = 0;
    x += (y != 0) ? 0 : 100;
    return x;
}