from sys import argv
from cs50 import SQL


def main():
    # Make sure file is given
    if len(argv) != 2:
        print("Usage: python rooster.py house")
        exit(1)
    else:
        CheckDB(argv[1])


def CheckDB(houseName):
    # Open db
    db = SQL("sqlite:///students.db")
    # Get dict from db based on query given
    houseTable = db.execute(f"SELECT * FROM students WHERE house = '{houseName}' ORDER BY last, first")
    # Go through each row
    for row in houseTable:
        # Check if middle name is given
        middleName = " " + row['middle'] if row['middle'] else ""
        # Print variables from dict
        print(f"{row['first']}{middleName} {row['last']}, born {row['birth']}")


main()
