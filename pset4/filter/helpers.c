#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int GetAverageColor(int h, int w, RGBTRIPLE image[h][w], int leftCol, int rightCol, int downRow, int upRow, char *color);
int SobelOperator(int kernel[3][3]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Get the average of the three colors and set the RGB values to it
        for (int j = 0; j < width; j++)
        {
            int averageColor = (int) round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = averageColor;
            image[i][j].rgbtGreen = averageColor;
            image[i][j].rgbtBlue = averageColor;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Swap horizontal pixels up until the middle
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a duplicate, so as not to alter results
    RGBTRIPLE duplicate[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j].rgbtRed = image[i][j].rgbtRed;
            duplicate[i][j].rgbtGreen = image[i][j].rgbtGreen;
            duplicate[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the columns to the right and left of the pixel
            int leftCol = j - 1, rightCol = j + 1;
            // Get the rows above and beneath the pixel
            int upRow = i - 1, downRow = i + 1;

            // Make sure they are not out of the image
            if (leftCol < 0)
            {
                leftCol++;
            }

            if (rightCol > width - 1)
            {
                rightCol--;
            }

            if (upRow < 0)
            {
                upRow++;
            }

            if (downRow > height - 1)
            {
                downRow--;
            }

            // Set each pixel to the average of the pixels 1 column and row around them
            image[i][j].rgbtRed = GetAverageColor(height, width, duplicate, leftCol, rightCol, downRow, upRow, "Red");
            image[i][j].rgbtGreen = GetAverageColor(height, width, duplicate, leftCol, rightCol, downRow, upRow, "Green");
            image[i][j].rgbtBlue = GetAverageColor(height, width, duplicate, leftCol, rightCol, downRow, upRow, "Blue");
        }
    }
}

int GetAverageColor(int h, int w, RGBTRIPLE image[h][w], int leftCol, int rightCol, int downRow, int upRow, char *color)
{
    float sum = 0;
    int count = 0;

    // Get each pixel around given pixel and add the RGB value
    for (int r = upRow; r <= downRow; r++)
    {
        for (int c = leftCol; c <= rightCol; c++)
        {
            if (strcmp(color, "Red") == 0)
            {
                sum += image[r][c].rgbtRed;
            }

            else if (strcmp(color, "Green") == 0)
            {
                sum += image[r][c].rgbtGreen;
            }

            else if (strcmp(color, "Blue") == 0)
            {
                sum += image[r][c].rgbtBlue;
            }

            count++;
        }
    }

    return (int) round(sum / count);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a duplicate, so as not to alter results
    RGBTRIPLE duplicate[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j].rgbtRed = image[i][j].rgbtRed;
            duplicate[i][j].rgbtGreen = image[i][j].rgbtGreen;
            duplicate[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Array of bytes storing the valuues of a channel
            int redBox[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
            int greenBox[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
            int blueBox[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

            // Get the columns to the right and left of the pixel
            int leftCol = j - 1, rightCol = j + 1;
            // Get the rows above and beneath the pixel
            int upRow = i - 1, downRow = i + 1;

            // bools for checking if 3x3 pixels is out of image
            bool topMost = false, leftMost = false;

            // Make sure they are not out of the image
            if (leftCol < 0)
            {
                leftCol++;
                leftMost = true;
            }

            if (rightCol > width - 1)
            {
                rightCol--;
            }

            if (upRow < 0)
            {
                upRow++;
                topMost = true;
            }

            if (downRow > height - 1)
            {
                downRow--;
            }

            // Starting value to row and col
            int startingRow = upRow, startingCol = leftCol;
            // Store nearby pixels in a 2D array
            for (int r = upRow; r <= downRow; r++)
            {
                for (int c = leftCol; c <= rightCol; c++)
                {
                    // (r - starting row) makes sure it's a 3x3 array
                    // topMost and leftMost bools to add an extra one to make sure the pixel is in the middle when at the edge
                    redBox[(topMost ? 1 : 0) + r - startingRow][(leftMost ? 1 : 0) + c - startingCol] = duplicate[r][c].rgbtRed;
                    greenBox[(topMost ? 1 : 0) + r - startingRow][(leftMost ? 1 : 0) + c - startingCol] = duplicate[r][c].rgbtGreen;
                    blueBox[(topMost ? 1 : 0) + r - startingRow][(leftMost ? 1 : 0) + c - startingCol] = duplicate[r][c].rgbtBlue;
                }

            }

            // Get values
            image[i][j].rgbtRed = SobelOperator(redBox);
            image[i][j].rgbtGreen = SobelOperator(greenBox);
            image[i][j].rgbtBlue = SobelOperator(blueBox);
        }
    }
}

int SobelOperator(int kernel[3][3])
{
    int gx = 0, gy = 0;

    int gxs[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gys[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Multiply by gx and gy array and add to variables
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            gx += (kernel[r][c] * gxs[r][c]);
            gy += (kernel[r][c] * gys[r][c]);
        }
    }

    // Do the merging formula
    int newChannel = round(sqrt(pow(gx, 2) + pow(gy, 2)));
    // Make sure it isn't out of bounds
    if (newChannel > 255)
    {
        newChannel = 255;
    }
    return newChannel;
}
