#include <cs50.h>
#include <stdio.h>

void Draw(int h);

int main(void)
{
    // Get height of pyramid
    int height = get_int("Height: ");

    // Draw pyramid
    Draw(height);
}

void Draw(int h)
{
    // If nothing to draw, stop recursion
    if (h == 0)
        return;

    // Draw pyramid of height h - 1
    Draw(h - 1);

    // Draw one more row of width h, it won't be called until after the recursion stops
    for (int i = 0; i < h; i++)
        printf("#");

    printf("\n");
}