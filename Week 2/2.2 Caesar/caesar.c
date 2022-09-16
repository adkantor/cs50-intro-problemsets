// Encrypts messages using Caesar?s cipher.
// The program accepts a single command-line argument, a non-negative integer.

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool isnumeric(string s);
string get_ciphertext(string plain, int key);
char get_cipherchar(char c, int key);
char encrypt_ascii_char(char c, int ascii_start, int ascii_end, int key);

// Accepts 1 command-line argument, a non-negative integer
int main(int argc, string argv[])
{
    // test argument
    if ((argc == 2) && (isnumeric(argv[1])))
    {
        // convert arg to integer
        int key = atoi(argv[1]);

        // get plaintext from user
        string plain = get_string("plaintext: ");

        // calculate ciphertext
        string cipher = get_ciphertext(plain, key);

        // print ciphertext
        printf("ciphertext: %s", cipher);
        printf("\n");
    }
    else
    {
        // more or less then 1 argument was given or argument was not a non-negative integer
        printf("Usage: ./caesar key\n");
        return 1;
    }

    return 0;
}


// Checks if given string is numeric (i.e. contains only digits)
// @param s     string to check
// @return      boolean
bool isnumeric(string s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
        i++;
    }
    return true;
}

// Converts plaintext to ciphertext using Caesar's cipher
// @param plain string to convert
// @param key   key (integer to shift with)
// @return      ciphertext (string)
string get_ciphertext(string plain, int key)
{
    // prepare string for result
    string s = plain;

    // encrypt character by character
    int i = 0;
    while (plain[i] != '\0')
    {
        s[i] = get_cipherchar(plain[i], key);
        i++;
    }

    return s;
}

// Calculates cipher of a character using Caesar's cipher
// @param c     character to convert
// @param key   key (integer to shift with)
// @return      shifted character
char get_cipherchar(char c, int key)
{
    if (isupper(c))
    {
        return encrypt_ascii_char(c, 65, 90, key);
    }
    else if (islower(c))
    {
        return encrypt_ascii_char(c, 97, 122, key);
    }
    else
    {
        return c;
    }
}

// Shifts a character by an integer (key) within set of charachers.
// @param c             plain character
// @param ascii_start   ascii code of first character of characterset
// @param ascii_end     ascii code of last character of characterset
// @param key           integer to offset ("rotate") with
// return               encrypted char
char encrypt_ascii_char(char c, int ascii_start, int ascii_end, int key)
{
    int ndx_plain = (int) c - ascii_start + 1;
    int set_len = ascii_end - ascii_start + 1;
    int ndx_cipher = (ndx_plain + key) % set_len;

    return ndx_cipher + ascii_start - 1;
}