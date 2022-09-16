// Encrypts messages using substitution (i.e. using a 26 character map).
// The program accepts a single command-line argument, a 26-character-long string.

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool is_valid_argument(string s);
bool is_unique(string s);
string get_ciphertext(string plain, string key);
char get_cipherchar(char c, string key);

// Accepts 1 command-line argument, a 26 character long string (map)
int main(int argc, string argv[])
{
    // test argument
    if (argc != 2)
    {
        // more or less then 1 argument was given
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // test if argument contains 26 alpha characters
    if (!is_valid_argument(argv[1]))
    {
        // argument was not valid
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // test if argument contains unique characters
    if (!is_unique(argv[1]))
    {
        // argument contains duplicates
        printf("Key must contain 26 unique characters.\n");
        return 1;
    }

    // get plaintext from user
    string plain = get_string("plaintext: ");

    // calculate ciphertext
    string cipher = get_ciphertext(plain, argv[1]);

    // print ciphertext
    printf("ciphertext: %s", cipher);
    printf("\n");

    return 0;
}


// Checks if argument is valid (i.e. contains 26 alpha characters)
// @param s     string to check
// @return      boolean
bool is_valid_argument(string s)
{
    // check length
    if (strlen(s) != 26)
    {
        // length is not ok
        return false;
    }

    // check all characters are alpha
    int i = 0;
    while (s[i] != '\0')
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
        i++;
    }

    return true;
}

// Checks if given string contains distinct characters only
// @param s     string to check
// @return      boolean
bool is_unique(string s)
{
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (s[i] == s[j])
            {
                // duplicate found
                return false;
            }
        }
    }
    return true;
}

// Converts plaintext to ciphertext using substitution
// @param plain string to convert
// @param key   key (integer to shift with)
// @return      ciphertext (string)
string get_ciphertext(string plain, string key)
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

// Calculates cipher of a character using substitution.
// @param c     character to convert
// @param key   26 character-long map
// @return      encrypted character
char get_cipherchar(char c, string key)
{
    int i = 0;
    if (isupper(c))
    {
        i = (int) c - 65;
        return toupper(key[i]);
    }
    else if (islower(c))
    {
        i = (int) c - 97;
        return tolower(key[i]);
    }
    else
    {
        return c;
    }
}