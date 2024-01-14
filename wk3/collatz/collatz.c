#include <cs50.h>
#include <stdio.h>

int collatz(int number);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./collatz number\n");
        return 1;
    }

    int collatz_value = collatz(argv[1], 0);
    printf("The collatz value of %i is %i", argv[1], collatz_value);

    return 0;
}

int collatz(int number, int steps)
{
    if (number = 1)
        return (steps);

    if (number % 2)
        collatz(3 * n + 1, steps + 1);
    else 
        collatz(n / 2, steps + 1);

    return number;
}
