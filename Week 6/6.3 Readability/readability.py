#  Computes the approximate grade level needed to comprehend some text.
#  Uses Coleman-Liau index: 0.0588 * L - 0.296 * S - 15.8, where:
#       L is the average number of letters per 100 words in the text
#       S is the average number of sentences per 100 words in the text.

from cs50 import get_string
import re
import sys


def main():

    # ask text to evaluate
    text = get_string("Text: ")
    if len(text) == 0:
        sys.exit(1)

    # calculate grade
    grade = calculate_grade(text)

    # print out result
    # convert grades below 1 or above 16.
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print("Grade {}".format(grade))

    sys.exit(0)


def calculate_grade(text):
    """
    Calculates grade with Coleman-Liau index.

    @param text  string to evaluate
    @return      grade (int)
    """

    # calculate counts
    nr_of_letters = len(re.findall(r'\w', text))
    nr_of_words = len(re.findall(r'[\S]+\s', text)) + 1
    nr_of_sentences = len(re.findall(r'\w+[\.\!\?]', text))

    # average number of letters per 100 words in the text
    L = nr_of_letters / nr_of_words * 100

    # average number of sentences per 100 words in the text
    S = nr_of_sentences / nr_of_words * 100

    # calculate grade
    grade = round(0.0588 * L - 0.296 * S - 15.8)

    return grade


if __name__ == "__main__":
    main()