# Prompts the user for a credit card number and then reports whether it is a valid American Express, MasterCard, or Visa card number.

from cs50 import get_string
import re

# constants
AMEX = "AMEX"
MC = "MASTERCARD"
VISA = "VISA"
INVALID = "INVALID"


def main():
    # get user input
    cc_num = get_string("Number: ")

    # get issuer by digit count and starting digits
    cc_type = get_type(cc_num)
    if cc_type != INVALID:
        # validate number via Luhns's Algorithm
        cc_valid = is_valid(cc_num)
        if cc_valid:
            print(f"{cc_type}")         # if valid, print issuer name
        else:
            print(f"{INVALID}")         # else print Invalid
    else:
        print(f"{INVALID}")             # if issuer not identified, then print Invalid


def get_type(cc_num):
    """
        Gets type (issuer name).

        @param cc_num   credit card number as string
        @return         issuer name or "INVALID"
    """

    if is_amex(cc_num):
        return AMEX
    elif is_mc(cc_num):
        return MC
    elif is_visa(cc_num):
        return VISA
    else:
        return INVALID


def is_amex(cc_num):
    """
        Checks whether credit card issuer is Amex, by checking digit count and starting digit(s).
        True if card number consists of 15 digits starting with 34 or 37

        @param cc_num   credit card number as string
        @return         bool
    """
    return not re.match(r'^3(4|7)[0-9]{13}$', cc_num) == None


def is_mc(cc_num):
    """
        Checks whether credit card issuer is MasterCard, by checking digit count and starting digit(s).
        True if card number consists of 16 digits starting with 51, 52, 53, 54 or 55

        @param cc_num   credit card number as string
        @return         bool
    """
    return not re.match(r'^5[1-5][0-9]{14}$', cc_num) == None


def is_visa(cc_num):
    """
        Checks whether credit card issuer is Visa, by checking digit count and starting digit(s).
        True if card number consists of 13 or 16 digits starting with 4

        @param cc_num   credit card number as string
        @return         bool
    """
    return not re.match(r'^4([0-9]{12}|[0-9]{15})$', cc_num) == None


def is_valid(cc_num):
    """
        Checks credit card validity via Luhn's Algorithm.
        @param cc_num   credit card number
        @return         bool
    """

    # get every second digit, righ-to-left, starting with second digit
    # multiply by 2
    x = [str(int(cc_num[i])*2) for i in range(len(cc_num)-2, -1, -2)]
    # add up sum of digits of numbers in list(x)
    s = sum([int(d) for n in x for d in n])
    # get every second digit, righ-to-left, starting with first digit
    y = [int(cc_num[i]) for i in range(len(cc_num)-1, -1, -2)]
    # add sum of numbers in list(y) to s
    s = s + sum(y)

    # valid if divisible by 10 (sum ends with 0)
    return (s % 10 == 0)


if __name__ == "__main__":
    main()