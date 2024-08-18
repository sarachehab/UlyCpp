#include <stdio.h>

char *f();

int main()
{
    char *s = f();
    char *exemplar = "Hello, World!";

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] != exemplar[i])
        {
            return 1;
        }
        printf("%c", s[i]);
    }
}
