int f(int n){
    int count = 0;
    while (n != 1){
        if (n % 2 == 0){
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        count++;
    }
    return count;
}

int g(int x){
    return f(x+2);
}