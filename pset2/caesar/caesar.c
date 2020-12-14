#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

void Scramble(int key);

int main(int argc, string argv[])
{
    // If argument passed
    if (argc == 2)
    {
        // Check if it contains a letter
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // Change it to int
        int arg = atoi(argv[1]);

        // If it's not a number, show error
        if (arg <= 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        // If it is, scramble it
        else
        {
            // It is greater than 26, do mod on it
            if (arg > 26)
            {
                arg %= 26;
            }

            Scramble(arg);
        }
    }

    // If not argument is passed, show error
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    return 0;
}

void Scramble(int key)
{
    // Get plain text
    string plainText = get_string("plaintext: ");
    int n = strlen(plainText);

    printf("ciphertext: ");

    // Go through each char and increment by given key
    for (int i = 0; i < n; i++)
    {
        // New char
        int newAscii = plainText[i] + key;

        // If it exceed the letter range, bring it back
        if ((newAscii >= 91 && newAscii <= 96) || newAscii > 122)
        {
            newAscii -= 26;
        }

        // Print scrambled char if it is a letter
        if (isalpha(plainText[i]))
        {
            printf("%c", (char) newAscii);
        }

        // If it isn't a letter print it
        else
        {
            printf("%c", plainText[i]);
        }
    }

    printf("\n");
}