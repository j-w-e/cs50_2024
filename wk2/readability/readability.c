#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float calculate_read_level(float sentences, float word_length);

int main(void)
{
    string text = get_string("Text: ");
    // string text = "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, \"and what is the use of a book,\" thought Alice \"without pictures or conversation?\"";

    int text_length = strlen(text);
    int words = 1;
    float letters = 0;
    float sentences = 0;

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]))
            letters++;
         else if (isspace(text[i]))
                words++;
         else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
                  sentences++;
    }
    sentences =  sentences * 100.0 / words;
    letters = (float) letters / words * 100;

    float score = calculate_read_level(sentences, letters);

    if (score < 1.5)
        printf("Before Grade 1\n");
    else if (score >= 15.5)
        printf("Grade 16+\n");
    else
        printf("Grade %.0f\n", score);

    return 0;
}

float calculate_read_level(float sentences, float word_length)
{
    return (0.0588 * word_length - 0.296 * sentences - 15.8);
}
