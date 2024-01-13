#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float count_sentences(string text, int text_length);
float word_length(string text, int text_length);
float calculate_read_level(float sentences, float word_length);

int main(void)
{
    string text = get_string("Text: ");
    int text_length = strlen(text);

    // function to calculate the number of sentences per 100 words
    float sentences = count_sentences(text, text_length);

    // function to calculate average word length per 100 words
    float letters = word_length(text, text_length);

    float score = calculate_read_level(sentences, letters);

    if (score < 1.5)
        printf("Before Grade 1\n");
    else if (score >= 15.5)
        printf("Grade 16+\n");
    else
        printf("Grade %.0f\n", score);

    return 0;
}

float count_sentences(string text, int text_length)
{
    int sentences = 1; // Start at one, because even if there is no punctuation, there is one sentence
    int words = 1;
    for (int i = 0; i < text_length - 1; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            if (i > 0 & text[i - 1] != '.')
                sentences++;
        } else if (isspace(text[i]))
        {
            words++;
        }
    }

    return (sentences * 100.0 / words);
}

float word_length(string text, int text_length)
{
    int letters = 0;
    int spaces = 0;

    for (int i = 0; i < text_length - 1; i++)
    {
        if (isalpha(text[i]))
            letters++;
         else if (isspace(text[i]))
            spaces++;
    }

    if (isalpha(text[text_length - 1]))
    {
        letters++;
        spaces++;
    }
    else if (ispunct(text[text_length - 1]) || isspace(text[text_length - 1]))
    {
        spaces++;
    }

    return ( (float) letters / spaces * 100);
}

float calculate_read_level(float sentences, float word_length)
{
    return (0.0588 * word_length - 0.296 * sentences - 15.8);
}
