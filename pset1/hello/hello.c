#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks the user for their name
    string name = get_string("What's your name? \n");
    
    // Prints hello and the user's name
    printf("hello, %s\n", name);
}