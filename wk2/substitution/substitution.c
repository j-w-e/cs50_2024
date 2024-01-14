#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int is_key_invalid(string key);
char encode(char c, string key);

int main(int argv, string argc[])
{
    if (argv != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int key_status = is_key_invalid(argc[1]);

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

    string plaintext = get_string("plaintext:  ");
    string ciphertext = plaintext;

    int text_length = strlen(plaintext);
    for (int i = 0; i < text_length; i++)
    {
        ciphertext[i] = encode(plaintext[i], argc[1]);
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

int is_key_invalid(string key)
{
    int keylength = strlen(key);

    if (keylength != 26)
        return 1; // if key is not 26 characters long

    int is_each_letter_used[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 26 zeros

    for (int i = 0; i < keylength; i++)
    {
        if (!isalpha(key[i]))
            return 2; // key must only contain letters
        char c = toupper(key[i]);
        int d = c - 65;
        if (is_each_letter_used[d])
            return 3;
        is_each_letter_used[d] = '1';
    }

    return 0; // key is valid
}

char encode(char c, string key)
{
    if (!isalpha(c))
        return (c);

    bool isupper = isupper(c);

    return (c);
}
