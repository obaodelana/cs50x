#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

BYTE bytes[512];
char fileName[10];
bool jpegFound = false;
int fileNo = 0;

void Search(FILE *file, FILE *img);

int main(int argc, char *argv[])
{
    // Error checking
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open given file
    FILE *file = fopen(argv[1], "r");
    // Error checking
    if (file == NULL)
    {
        printf("Cannot open image\n");
        return 2;
    }

    // Store image pointer
    FILE *img = NULL;

    // Search file for start of JPEG
    Search(file, img);

    // Close file
    fclose(file);
}

void Search(FILE *file, FILE *img)
{
    int read =  fread(bytes, 1, 512, file);
    if (read <= 0)
    {
        // Close image file if open
        if (img != NULL)
        {
            fclose(img);
        }
        return;
    }

    for (int i = 0; i < read; i++)
    {
        if (bytes[i] == 0xff && bytes[i + 1] == 0xd8 && bytes[i + 2] == 0xff && (bytes[i + 3] & 0xf0) == 0xe0)
        {
            // Set file name
            sprintf(fileName, "%03i.jpg", fileNo++);
            // Close image file if open
            if (img != NULL)
            {
                fclose(img);
            }
            // Open it for writing new image
            img = fopen(fileName, "w");
            // Allow wiriting to jpeg
            jpegFound = true;
        }

        if (jpegFound)
        {
            // Write to image byte per byte
            fwrite(&bytes[i], 1, 1, img);
        }
    }

    // Recursive function to continue to read as long as there are bytes in file
    if (read > 0)
    {
        Search(file, img);
    }
}
