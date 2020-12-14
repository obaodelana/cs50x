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
    # Go throguh e
    for t in text:
        if t.isalpha() and t != " ":
            letters += 1
        if t == " ":
            words += 1
        if t in sentenceEnd:
            sentences += 1
    words += 1
    PrintGrade(letters, words, sentences)


def PrintGrade(letters, words, sentences):
    l = (letters / words) * 100
    s = (sentences / words) * 100
    grade = round(0.0588 * l - 0.296 * s - 15.8)
    if grade >= 16:
        grade = "Grade 16+"
    elif grade < 1:
        grade = "Before Grade 1"
    else:
        grade = "Grade: " + str(grade)
    print(grade)


main()
