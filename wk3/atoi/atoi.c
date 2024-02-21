#include "cs50.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int value = 0;
    int input_len = strlen(input);
    if (input_len == 1)
    {
        value = input[0] - 48;
    }
    else
    {
        value = input[input_len - 1] - 48;
        input[input_len - 1] = '\0';
        value = value + 10 * convert(input);
    }

    return value;
}
