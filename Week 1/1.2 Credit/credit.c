// Prompts the user for a credit card number and then reports whether it is a valid American Express, MasterCard, or Visa card number.

#include <stdio.h>
#include <cs50.h>
#include <math.h>

string get_type(long cc_num);
bool is_amex(long cc_num);
bool is_mc(long cc_num);
bool is_visa(long cc_num);
bool is_valid(long cc_num);
int nthdigit(long x, int n);
int number_of_digits(long x);
int sum_of_digits(int x);
const string AMEX = "AMEX";
const string MC = "MASTERCARD";
const string VISA = "VISA";
const string INVALID = "INVALID";

int main(void)
{
    long cc_num;

    // get user input
    cc_num = get_long("Credit card number: \n");

    // get issuer by digit count and starting digits
    string cc_type = get_type(cc_num);
    if (cc_type != INVALID)
    {
        // validate number via Luhns's Algorithm
        bool cc_valid = is_valid(cc_num);
        if (cc_valid)
        {
            printf("%s\n", cc_type); // if valid, print issuer name
        }
        else
        {
            printf("%s\n", INVALID); // else print Invalid
        }
    }
    else
    {
        printf("%s\n", INVALID); // if issuer not identified, then print Invalid
    }

}

/*
    Gets type (issuer name).
    @param cc_num   credit card number
    @return         issuer name or "INVALID"
*/
string get_type(long cc_num)
{
    if (is_amex(cc_num))
    {
        return AMEX;
    }
    else if (is_mc(cc_num))
    {
        return MC;
    }
    else if (is_visa(cc_num))
    {
        return VISA;
    }
    else
    {
        return INVALID;
    }
}

/*
    Checks whether credit card issuer is Amex, by checking digit count and starting digit(s).
    @param cc_num   credit card number
    @return         bool
*/
bool is_amex(long cc_num)
{
    if (cc_num >= 34 * pow(10, 13) && (cc_num <= 35 * pow(10, 13) - 1))     // 15 digits starting with 34
    {
        return true;
    }
    else if (cc_num >= 37 * pow(10, 13) && (cc_num <= 38 * pow(10, 13) - 1)) // 15 digits starting with 37
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Checks whether credit card issuer is MasterCard, by checking digit count and starting digit(s).
    @param cc_num   credit card number
    @return         bool
*/
bool is_mc(long cc_num)
{
    if (cc_num >= 51 * pow(10, 14) && (cc_num <= 52 * pow(10, 14) - 1))     // 16 digits starting with 51
    {
        return true;
    }
    else if (cc_num >= 52 * pow(10, 14) && (cc_num <= 53 * pow(10, 14) - 1)) // 16 digits starting with 52
    {
        return true;
    }
    else if (cc_num >= 53 * pow(10, 14) && (cc_num <= 54 * pow(10, 14) - 1)) // 16 digits starting with 53
    {
        return true;
    }
    else if (cc_num >= 54 * pow(10, 14) && (cc_num <= 55 * pow(10, 14) - 1)) // 16 digits starting with 54
    {
        return true;
    }
    else if (cc_num >= 55 * pow(10, 14) && (cc_num <= 56 * pow(10, 14) - 1)) // 16 digits starting with 55
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Checks whether credit card issuer is Visa, by checking digit count and starting digit(s).
    @param cc_num   credit card number
    @return         bool
*/
bool is_visa(long cc_num)
{
    if (cc_num >= 4 * pow(10, 12) && (cc_num <= 5 * pow(10, 12) - 1))     // 13 digits starting with 4
    {
        return true;
    }
    else if (cc_num >= 4 * pow(10, 15) && (cc_num <= 5 * pow(10, 15) - 1)) // 16 digits starting with 4
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Checks credit card validity via Luhn's Algorithm.
    @param cc_num   credit card number
    @return         bool
*/
bool is_valid(long cc_num)
{
    int sum = 0;
    int digit;
    int digit_count = number_of_digits(cc_num);
    for (int n = 2; n <= digit_count; n += 2)
    {
        digit = nthdigit(cc_num, n - 1); // get every second digit, righ-to-left, starting with second digit
        int digit_times_two = 2 * digit; // multiply by 2
        int sum_digits = sum_of_digits(digit_times_two); // get sum of digits
        sum = sum + sum_digits; // add up sum of digits
    }
    for (int n = 1; n <= digit_count; n += 2)
    {
        digit = nthdigit(cc_num, n - 1); // get every second digit, righ-to-left, starting with first digit
        sum = sum + digit; // add sum of digits together
    }
    return (sum % 10 == 0); // valid if divisible by 10 (sum ends with 0)
}

/*
    Returns n-th digit of a number, right to left. Zero based (rightmost digit is 0th).
    @param x        number too look in
    @param n        zero based index
    @return         n-th digit (integer)
*/
int nthdigit(long x, int n)
{
    while (n--)
    {
        x /= 10;
    }
    return (x % 10);
}

int number_of_digits(long x)
{
    return (x == 0) ? 1  : (log10(x) + 1);
}

/*
    Returns number of digits in a number.
    @param x        number too look in
    @return         digit count
*/
int sum_of_digits(int x)
{
    int sum = 0, m;
    while (x > 0)
    {
        m = x % 10;
        sum = sum + m;
        x = x / 10;
    }
    return sum;
}
