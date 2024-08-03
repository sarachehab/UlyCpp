double pow(int i, double r){
    if (i == 0){
        return 1;
    }
    return r*pow(i-1, r);
}