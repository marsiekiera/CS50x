// includes
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// declare functions

int main(void)
{
    string text = get_string("Text: ");
    float letters = 0;
    float words = 1;
    float sentence = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        // count letters
        if (isalpha(text[i]) > 0)
        {
            letters = letters + 1;
        }
        // count words
        if ((isspace(text[i]) > 0 && isalpha(text[i + 1]) > 0) || (isspace(text[i]) > 0 && isalpha(text[i + 2]) > 0))
        {
            words = words + 1;
        }
        // count sentence
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentence = sentence + 1;
        }
    }
    float L = letters * 100 / words;
    float S = sentence * 100 / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }
}