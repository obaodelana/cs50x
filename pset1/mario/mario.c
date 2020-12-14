#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    // Get user input and make sure it's within range of 1 - 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Loop (height) number of times
    for (int i = 1; i <= height; i++)
    {
        // Add (height - current index) number of spaces
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Add (current index) number of hashes
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Add two spaces
        printf("  ");

        // Add (current index) number of hashes
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }

        // New line
        printf("\n");
    }
}