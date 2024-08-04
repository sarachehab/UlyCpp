int f(){
    int i;
    for(i = 1; i < 8; i++){
        if (i == 5) {
            continue;
        }
        i *= i;
    }
    return i;
}

