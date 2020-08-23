from cs50 import get_string


def index(text):  # index function
    # define variable
    letters = 0
    words = 1
    sentence = 0
    # create loop fo every char in string
    for i in range(0, len(text)):
        # counting letters
        if text[i].isalpha():
            letters += 1
        # counting words - if it's space and i+1 or i+2 is char, then it's a next word
        elif text[i] == " " and (text[i + 1].isalpha() or text[i + 2].isalpha()):
            words += 1
        # counting sentence - if it's one of (.?!) then it's a next sentence
        elif text[i] in [".", "?", "!"] and not text[i - 1] in [".", "?", "!"]:
            sentence += 1
        i += 1

    # index calcs
    return 0.0588 * (letters * 100 / words) - 0.296 * (sentence * 100 / words) - 15.8


def grade(index):  # grade function
    if index > 16:
        return "Grade 16+"
    elif index < 1:
        return "Before Grade 1"
    else:
        return f"Grade {round(index)}"


def main():  # define main function
    # get text from user
    text = get_string("Text: ")
    # print grade
    print(grade(index(text)))


main()