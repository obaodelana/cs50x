#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

bool ErrorHandling(string arg);
void Cipher(string key);

int main(int argc, string argv[])
{
    // If argument is given, check if it has a correct syntax
    if (argc == 2)
    {
        if (ErrorHandling(argv[1]))
        {
            return 1;
        }

        Cipher(argv[1]);
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    return 0;
}

bool ErrorHandling(string arg)
{
    // If string does not have 26 letters, show error
    if (strlen(arg) != 26)
    {
        if (isalpha(arg[0]))
        {
            printf("Key must contain 26 characters.\n");
        }

        else
        {
            printf("Usage: ./substitution key\n");
        }

        return true;
    }

    // If string has 26 letters
    else
    {
        char empty[26] = "";

        // If it has a number, show error
        if (strchr(arg, '0') || strchr(arg, '1') || strchr(arg, '2') || strchr(arg, '3') || strchr(arg, '4') || strchr(arg, '5')
            || strchr(arg, '6') || strchr(arg, '7') || strchr(arg, '8') || strchr(arg, '9'))
        {
            printf("Incorrect key\n");
            return true;
        }

        // If it has a duplicate letter, show error
        else
        {
            for (int i = 0, n = strlen(arg); i < n; i++)
            {
                if (!strchr(empty, arg[i]))
                {
                    empty[i] = arg[i];
                }

                else
                {
                    printf("Incorrect key\n");
                    return true;
                }
            }
        }
    }

    return false;
}

void Cipher(string key)
{
    // Get plain text
    string plainText = get_string("plaintext: ");

    printf("ciphertext: ");
    fflush(stdout);

    // Go through each char
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        // If it's a letter
        if (isalpha(plainText[i]))
        {
            int index = 0;

            // If it's in lower case minus 97 from the ascii code to get the index in the alphabets
            if (islower(plainText[i]))
            {
                index = plainText[i] - 97;
                // Get the char from the key using the index and turn it into lower case
                char letter = (char) tolower(key[index]);
                printf("%c", letter);
                fflush(stdout);
            }

            // If it's in upper case minus 65 from the ascii code to get the index in the alphabets
            else
            {
                index = plainText[i] - 65;
                // Get the char from the key using the index and turn it into upper case
                char letter = (char) toupper(key[index]);
                printf("%c", letter);
                fflush(stdout);
            }
        }

        // If it isn't a letter, print it
        else
        {
            printf("%c", plainText[i]);
            fflush(stdout);
        }
    }

    printf("\n");
}