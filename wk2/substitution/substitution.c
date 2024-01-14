#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_key_invalid(string key);

int main(int argv, string argc[])
{
    if (argv != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int key_status = is_key_invalid(argc[2]);

    if (key_status)
    {
        if (key_status == 1)
            printf("Key must be 26 characters long\n");
        if (key_status == 2)
            printf("Key must contain only letters\n");
        if (key_status == 3)
            printf("Key must contain each letter only once\n");
        return 1;
    }

    printf("key is valid\n");
}

int is_key_invalid(string key)
{
    int keylength = strlen(key);

    if (keylength != 26)
        return 1; // if key is not 26 characters long

    string is_each_letter_used = "00000000000000000000000000"; // 26 zeros

    for (int i = 0; i < keylength; i++)
    {
        if (!isalpha(key[i]))
            return 2; // key must only contain letters
        char c = toupper(key[i]);
        if (is_each_letter_used[c - 65])
            return 3;
        is_each_letter_used[c - 65] = 1;
    }

    return 0; // key is valid
}