// Computes the approximate grade level needed to comprehend some text.
// Uses Coleman-Liau index: 0.0588 * L - 0.296 * S - 15.8, where:
//      L is the average number of letters per 100 words in the text
//      S is the average number of sentences per 100 words in the text.

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int calculate_grade(string text);
bool is_letter(char c);
bool is_end_of_word(char c);
bool is_end_of_sentence(char c);

int main(void)
{
    // ask text to evaluate
    string text = get_string("Text: ");

    // calculate grade
    int grade = calculate_grade(text);

    // print out result
    // convert grades below 1 or above 16.
    if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", grade);
    }

    printf("\n");
}

// Calculates grade with Coleman-Liau index.
// @param text  string to evaluate
// @return      grade (int)
int calculate_grade(string text)
{
    int nr_of_letters = 0;
    int nr_of_words = 0;
    int nr_of_sentences = 0;
    char last_char = '\0';

    // parse text character by character
    int ndx = 0;
    while (text[ndx] != '\0')
    {
        // chack if character is alpha char
        if (is_letter(text[ndx]))
        {
            nr_of_letters++;
        }
        // check if character is whitespace (but not whitespace after end of sentence)
        else if (is_end_of_word(text[ndx]) && !is_end_of_sentence(last_char))
        {
            nr_of_words++;
        }
        // check if character is ending sentence
        else if (is_end_of_sentence(text[ndx]))
        {
            nr_of_words++;
            nr_of_sentences++;
        }

        // store last character
        last_char = text[ndx];
        ndx++;
    }

    // average number of letters per 100 words in the text
    float L = (float) nr_of_letters / (float) nr_of_words * 100;

    // average number of sentences per 100 words in the text
    float S = (float) nr_of_sentences / (float) nr_of_words * 100;

    // calculate grade
    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    return grade;
}

// Returns if given character is alpha character.
// @param c     character to investigate
// @return      boolean
bool is_letter(char c)
{
    return isalpha(c);
}

// Returns if given character is separating words (whitespace)
// @param c     character to investigate
// @return      boolean
bool is_end_of_word(char c)
{
    return (c == ' ');
}

// Returns if given character is ending a sentence (.!?)
// @param c     character to investigate
// @return      boolean
bool is_end_of_sentence(char c)
{
    return (c == '.' || c == '?' || c == '!');
}