int f(int v)
{
    int i;
    int x[8];
    int acc;
    for(i=8; i<16; i++){
        x[i-8]=i;
    }
    return x[v];
}
