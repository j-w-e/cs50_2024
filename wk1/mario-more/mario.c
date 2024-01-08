#include <cs50.h>
#include <stdio.h>

void print_blocks(int length, char c);

int main(void)
{
    int height;
    do
    {
        height = get_int("How high do you want the pyramid? ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        print_blocks(height - i - 1, ' ');
        print_blocks(i + 1, '#');
        printf("  ");
        print_blocks(i + 1, '#');
        printf("\n");
    }

    return (0);
}

void print_blocks(int length, char c)
{
    for (int i = 0; i < length; i++)
    {
        printf("%c", c);
    }
    return;
}
