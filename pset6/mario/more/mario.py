height = input("Height: ")

# Make sure height is a number ranging from 1 to 8
while (not height.isdigit() or int(height) not in range(1, 9)):
    height = input("Height: ")

# Make range a number
height = int(height)


def PrintHashLine(num):
    # Print height - num spaces
    print(" " * int(height - num), end="")
    # Print num amount of hashes
    print("#" * num, end="")
    # Print two spaces
    print("  ", end="")
    #  Print num amount of hashes
    print("#" * num, end="")
    # Print a new line
    print("")


for i in range(1, height + 1):
    PrintHashLine(i)