char *search(char *x, char c);

int main()
{
    char *s = "abcdef";

    char *p = search((char *)s, 'c');
    printf("Output is %d\n", p - s);
    return !(p == s + 2);
}
