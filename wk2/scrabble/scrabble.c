#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int LETTER_VALUES[] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

int score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    /* string word2 = get_string("Player 2: "); */
    printf("That scores %i\n", score(word1));
    return 0;
}

int score(string word)
{
    int word_length = strlen(word);
    int score = 0;

    for (int i = 0; i < word_length; i++)
    {
        char letter = toupper(word[i]);
        score += LETTER_VALUES[letter - 65];
    }
    return (score);
}
