# Reverse number given
card = input("Number: ")[::-1]
sum = 0
count = 0


def main():
    # If valid, state card type
    if CheckValidity():
        PrintCards()
    # Else print INVALID
    else:
        print("INVALID")


def CheckValidity():
    # Go through each letter
    for digit in card:
        # Increment counter
        global count
        global sum

        count += 1
        # If counter is even
        if count % 2 == 0:
            # Multiply the current digit by two
            newNo = int(digit) * 2
            # Get the first and second digit if number is greater than 9 and add to sum
            if newNo > 9:
                sum += newNo % 10
                sum += newNo // 10
            # Get digit if less than 9 and add to sum
            else:
                sum += newNo
        # If counter is odd, add to sum variable
        else:
            sum += int(digit)
    return (sum % 10 == 0)


# Determine the type of card
def PrintCards():
    # AMEX
    if len(card) == 15 and card[count - 1] == "3" and (card[count - 2] == "4" or card[count - 2] == "7"):
        print("AMEX")
    # MASTERCARD
    elif len(card) == 16 and card[count - 1] == "5" and int(card[count - 2]) in range(1, 6):
        print("MASTERCARD")
    # VISA
    elif (len(card) == 13 or len(card) == 16) and card[count - 1] == "4":
        print("VISA")
    # INVALID
    else:
        print("INVALID")


main()
