#include <stdio.h>
#include <cs50.h>

bool CheckSum(long no);
void CardType(void);

long digits[16];
int counter = 0;

int main(void)
{
    long cardNo = get_long("Number: ");
    if (CheckSum(cardNo))
    {
        CardType();
    }

    else
    {
        printf("INVALID\n");
    }
}

bool CheckSum(long no)
{
    int sum = 0;

    // Save each digit to an array
    while (no)
    {
        digits[counter++] = no % 10;
        no /= 10;
    }

    // Add every other number starting from the second to last digit
    for (int i = 1; i < counter; i += 2)
    {
        long val = digits[i] * 2;
        // If the value has two digits and the first and last digit seperately
        if (val > 9)
        {
            sum += val % 10;
            sum += val / 10;
        }

        else
        {
            sum += val;
        }
    }

    // Add numbers not previously added
    for (int i = 0; i < counter; i += 2)
    {
        sum += digits[i];
    }

    // If the last digit is 0, return true
    if (sum % 10 == 0)
    {
        return true;
    }

    return false;
}

void CardType()
{
    // VISA
    if ((counter == 13 || counter == 16) && digits[counter - 1] == 4)
    {
        printf("VISA\n");
    }

    // AMEX
    else if (counter == 15 && digits[counter - 1] == 3 && (digits[counter - 2] == 7 || digits[counter - 2] == 4))
    {
        printf("AMEX\n");
    }

    // MASTERCARD
    else if (counter == 16 && digits[counter - 1] == 5 && (digits[counter - 2] >= 1 && digits[counter - 2] <= 5))
    {
        printf("MASTERCARD\n");
    }

    else
    {
        printf("INVALID\n");
    }
}
