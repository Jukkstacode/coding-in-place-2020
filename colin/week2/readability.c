#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int find_coleman_liau(int numberofletters, int numberofwords, int numberofsentences);

int main(void)
{
    /*Get user input of text to determine reading level */
    string text = get_string("Text: ");
    printf("Text: %s\n", text);

    /*Determine number of letters */
    int numberofletters = count_letters(text);

    /*Determine number of words */
    int numberofwords = count_words(text);

    /*Determine number of sentences */
    int numberofsentences = count_sentences(text);

    /*Find and print Coleman-Liau index of the text */
    int colemanliau = find_coleman_liau(numberofletters, numberofwords, numberofsentences);

    if (colemanliau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (colemanliau >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", colemanliau);
    }

}

int count_letters(string text)
{
    int num_letters = 0;
    int i = 0;

    //Count the number of characters in the "text" that are letters
    while (text[i] != '\0')
    {
        if (isalpha(text[i]) != 0)
        {
            num_letters++;
        }
        i++;
    }

    return num_letters;
}

int count_words(string text)
{
    //Initialize variables, starting words off at 1 word
    int num_words = 1;
    int i = 0;

    //Run through text, check if there's a space, if so assume 1 additional word is in the text
    while (text[i] != '\0')
    {
        if (isspace(text[i]) != 0)
        {
            num_words++;
        }
        i++;
    }

    return num_words;
}

int count_sentences(string text)
{
    //initialize variables, assume start with 1 sentence
    int num_sentences = 0;
    int i = 0;

    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            num_sentences++;
        }
        i++;
    }

    return num_sentences;
}

int find_coleman_liau(int numberofletters, int numberofwords, int numberofsentences)
{
    float index = 0.0588 * (float) numberofletters / (float) numberofwords * 100 - 0.296 * (float) numberofsentences /
                  (float) numberofwords * 100 - 15.8;
    int colemanliau = roundf(index);
    return colemanliau;
}
