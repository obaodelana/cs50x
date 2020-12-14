from sys import argv
import csv
from cs50 import SQL


def main():
    # Make sure file is given
    if len(argv) != 2:
        print("Usage: python import.py file.csv")
        exit(1)
    else:
        ImportToDB(argv[1])


def ImportToDB(csvFile: str):
    # Open databse
    db = SQL("sqlite:///students.db")
    # Open csv file
    with open(csvFile, "r") as file:
        # Convert to dictionary
        table = csv.DictReader(file)
        # Go through each row
        for row in table:
            # Turn name into substring of first, middle and last name
            fullName = row["name"].split()
            # Assign the first name accordingly
            firstName = fullName[0]
            # Assign the middle name if given
            middleName = fullName[1] if len(fullName) > 2 else None
            # Assign the last name depending on if middle name is given
            lastName = fullName[2] if len(fullName) > 2 else fullName[1]
            # House gotten from dict
            house = row["house"]
            # Birth gotten from dict
            birth = int(row["birth"])
            # Insert into db with command
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       firstName, middleName, lastName, house, birth)


main()
