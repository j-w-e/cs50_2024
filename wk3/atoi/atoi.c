#include "cs50.h"
#include <ctype.h>
#include <math.h>
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
    for (int i = strlen(input) - 1; i >= 0; i--)
    {
        // TODO !
        // THIS is where I need to take each character, convert to an int
        // and then add that to the return value
        // automatically adjusting for the right tens column
    }
    printf("\n");
    return 0;
}
