from sys import argv
import csv


def main():
    # Make sure appropriate arguments are given
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    else:
        # If so, open files
        OpenFiles(argv[1], argv[2])


def OpenFiles(csvName, dnaName):
    # Open files
    csvFile = open(csvName, "r")
    dnaFile = open(dnaName, "r")

    # Read sequence file
    sequence = dnaFile.read()
    # Read csv table
    table = csv.reader(csvFile, delimiter=",")

    # Check for a match
    CheckTable(table, STRCount(sequence, next(table)))

    # Close files
    csvFile.close()
    dnaFile.close()


# Get the highest sequence repetition in STR given (first row)
def STRCount(sequence, row):
    # Sequence list
    sequenceList = []
    # Check each col in the row, excluding the first col
    for col in row[1: len(row)]:
        # Amount of times an STR repeats
        repetition = 0
        # All STR repetitions
        repetitionList = []
        i = 0
        # Go through each sequence character
        while i < len(sequence):
            # Get a string starting from i to i + column's length
            # If it is equal to the col (STR)
            if sequence[i: i + len(col)] == col:
                # That's a repetiton
                repetition += 1
                # Increment i leaving the already checked chars
                i += len(col)
            # It it isn't
            else:
                # Increment i normally
                i += 1
                # And if it is the end of  repetition
                if repetition > 0:
                    # Add to the repetion list
                    repetitionList.append(repetition)
                    # Reset repetition counter
                    repetition = 0
        # After checking an STR in the sequence
        # Add the max repetition
        if len(repetitionList) > 0:
            sequenceList.append(max(repetitionList))
    # Return highest sequence repetition
    return sequenceList


def CheckTable(table, sequenceStr):
    # Check each row
    for row in table:
        rowStr = []
        # Add each STR in the row to a list
        for i in range(1, len(row)):
            rowStr.append(int(row[i]))
        # Check if the list is equals to the sequence given
        if rowStr == sequenceStr:
            # Print name
            print(row[0])
            # Exit function
            return True
    # If after checking each row, there's no match, return false
    print("No match")
    return False


main()
