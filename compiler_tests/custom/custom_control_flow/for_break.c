int f(int x){
    int i = 0;
    for(;i<10;i++){
        if (x % 3 == 0){
            break;
        }
        x++;
    }
    return x;
}