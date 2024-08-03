int f(int n) {
    if (n == 0) {
        return 3;
    }else if (n == 1){
        return 6;
    } else {
        return n * f(n - 1) * f(n - 2);
    }
 }
