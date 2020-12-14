def main():
    # Get input
    text = input("Text: ")
    GetGrade(text)


def GetGrade(text):
    # Characters that denote end of sentence
    sentenceEnd = [".", "!", "?"]
    letters = 0
    words = 0
    sentences = 0
    # Go throguh each character
    for t in text:
        # If it's a letter and has no spaces, increment the letter variable
        if t.isalpha() and t != " ":
            letters += 1
        # If it is a space, increment the word variable
        if t == " ":
            words += 1
        # If it is a sentence end increment the sentence variable
        if t in sentenceEnd:
            sentences += 1
    # Incrememnt for last word
    words += 1
    # Print grade given variables
    PrintGrade(letters, words, sentences)


def PrintGrade(letters, words, sentences):
    # Formula stuff
    l = (letters / words) * 100
    s = (sentences / words) * 100
    grade = round(0.0588 * l - 0.296 * s - 15.8)
    # If 16 or above, print 'Grade 16+'
    if grade >= 16:
        grade = "Grade 16+"
    # If less than one print 'Before Grade 1'
    elif grade < 1:
        grade = "Before Grade 1"
    # Else print current grade
    else:
        grade = "Grade: " + str(grade)
    print(grade)


main()
