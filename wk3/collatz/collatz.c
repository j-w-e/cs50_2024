#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int collatz(int n, int steps);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./collatz number\n");
        return 1;
    }

    int number = atoi(argv[1]);
    int collatz_value = collatz(number, 0);
    printf("The collatz value of %i is %i\n", number, collatz_value);

    return 0;
}

int collatz(int n, int steps)
{
    if (n == 1)
        return (steps);

    if (n % 2)
        steps = collatz(3 * n + 1, steps + 1);
    else
        steps = collatz(n / 2, steps + 1);

    return steps;
}
