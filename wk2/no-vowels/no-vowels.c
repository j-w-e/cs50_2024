#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string word, int word_length);
char leetify(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word");
        return 1;
    }

    string word = argv[1];
    int word_length = strlen(word);
    word = replace(argv[1]);

    printf("%s\n", word);
}

string replace(string word, int word_length)
{
    for (int i = 0; i < word_length; i++)
    {
        word[i] = leetify(word[i]);
    }
}

char leetify(char c)
{
    switch (tolower(c)) {
        case 'a':
            c = '6';
            break;
        case 'e':
            c = '3';
            break;
        case 'i':
            c = '1';
            break;
        case 'o':
            c = '0';
            break;
    }
    return c
}
