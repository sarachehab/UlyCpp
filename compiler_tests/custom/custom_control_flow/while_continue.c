int f(int x){
    int i = 0;
    while (i < 3){
        if (i%2==0){
            i += 1;
            continue;
        }
        x += 1;
        i += 1;
    }
    return x;
}