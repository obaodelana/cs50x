#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <cs50.h>

void GetTextInfo(string txt);
void CalculateGrade(int letters, int words, int sentences);

int main(void)
{
    // Get user input and pass it into a function
    string passageText = get_string("Text: ");
    GetTextInfo(passageText);
}

// Calculate the number of words, letters and sentences in the string
void GetTextInfo(string txt)
{
    int letters = 0, words = 0, sentences = 0;

    for (int i = 0, n = strlen(txt); i < n; i++)
    {
        // If it contains a character it's a letter
        if (isalpha(txt[i]))
        {
            letters++;
        }

        // If the char is a space it means it's a new word
        if (txt[i] == ' ')
        {
            words++;
        }

        // If it has a period, exclamation or question mark, it's the end of a sentence
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentences++;
        }
    }
    // Last word
    words++;

    CalculateGrade(letters, words, sentences);
}

// Calculate the grade using Coleman-Liau index
void CalculateGrade(int letters, int words, int sentences)
{
    float l = (float) letters / words * 100;
    float s = (float) sentences / words * 100;

    float index = (0.0588 * l) - (0.296 * s) - 15.8;
    int grade = (int) round(index);

    if (grade > 16)
    {
        printf("Grade 16+\n");
    }

    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", grade);
    }
}