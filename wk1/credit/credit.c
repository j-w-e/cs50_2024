#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool test_number(long number);
bool check_length(long number);
void print_result(long number);

int main(void)
{
    long number = get_long("Number: ");

    if (!test_number(number))
    {
        printf("INVALID\n");
        return (0);
    }

    print_result(number);

    return (0);
}

bool test_number(long number)
{
    int sum = 0;
    long remainder = 0;
    long result = 1;

    for (int i = 0; i < 16; i++)
    {
        remainder = (number / (long) pow(10, i)) % 10;
        if (i % 2 != 0)
        {
            int product = 2 * remainder;
            if (product < 10)
                sum += 2 * remainder;
            else
                sum += product % 10 + 1;
        }
        else
        {
            sum += remainder;
        }
        result = number - remainder * (long) pow(10, i);
        if (result != 0)
            number = result;
        else
            number = number / pow(10, i);
    }

    if (sum % 10 != 0)
        return (false);
    else
        return (true);
}

void print_result(long number)
{
    if (number >= 4000000000000 & number < 5000000000000)
        printf("VISA");
    else if (number >= 340000000000000 & number < 350000000000000)
        printf("AMEX");
    else if (number >= 370000000000000 & number < 380000000000000)
        printf("AMEX");
    else if (number >= 4000000000000000 & number < 5000000000000000)
        printf("VISA");
    else if (number >= 5100000000000000 & number < 5600000000000000)
        printf("MASTERCARD");
    else
        printf("INVALID");

    printf("\n");
}
