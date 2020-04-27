#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//functions

float num_words (string s);
float avg_letters (string s);
float avg_sentences (string s);
int grade_calc (string s);

/*
Debug printfs
printf("Number of words in that string is: %.0f\n", num_words(input_text));
printf("Average number of letters in that string per 100 words is: %.2f\n", avg_letters(input_text));
printf("Average number of sentences in that string per 100 words is is: %.2f\n", avg_sentences(input_text));
*/

int main (void)
{
    //get input text
    string input_text = get_string("Text: ");

    //calculate grade and display
    if (grade_calc(input_text) < 1)
    {
        printf("Before Grade 1\n");
    }
    if (grade_calc(input_text) >= 1 && grade_calc(input_text) <= 15)
    {
        printf("Grade %i\n", grade_calc(input_text));
    }
    if (grade_calc(input_text) > 15)
    {
        printf("Grade 16+\n");
    }
}

//calculate number of words
float num_words (string s)
{
    float word_count = 1;
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] == 32)
        {
            word_count++;
        }
    }
    return word_count;
}

//calculate avg letters per 100 words
float avg_letters (string s)
{
    float letter_count = 0;
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letter_count++;
        }
    }
    return letter_count*100/num_words(s);
}

//calculate avg sentences per 100 words
float avg_sentences (string s)
{
    float sentence_count = 0;
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] ==  33 || s[i] == 46 || s[i] == 63)
        {
            sentence_count++;
        }
    }
    return sentence_count*100/num_words(s);
}

//calculate the leismann score and round it.
int grade_calc (string s)
{
    float l_avg = avg_letters(s);
    float s_avg = avg_sentences(s);
    float grade = 0.0588 * l_avg - 0.296 * s_avg - 15.8;
    grade = round(grade);
    return grade;
}
