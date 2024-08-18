#include "../../include/context/context.hpp"

char *Context::cancel_pointer_pairs(const char *sequence)
{
    static char buffer[256]; // Buffer to hold the remaining characters
    int star_count = 0;
    int ampersand_count = 0;

    // Count the number of * and & characters
    for (int i = 0; sequence[i] != '\0'; i++)
    {
        if (sequence[i] == '*')
        {
            star_count++;
        }
        else if (sequence[i] == '&')
        {
            if (star_count > 0)
            {
                star_count--; // Cancel out a *
            }
            else
            {
                ampersand_count++; // Unmatched &
            }
        }
    }

    // Construct the result with remaining unmatched characters
    int index = 0;
    for (int i = 0; i < star_count; i++)
    {
        buffer[index++] = '*';
    }
    for (int i = 0; i < ampersand_count; i++)
    {
        buffer[index++] = '&';
    }
    buffer[index] = '\0'; // Null-terminate the string

    return buffer;
}
