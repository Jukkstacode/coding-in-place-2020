#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string text = get_string("Text:");
    
    int i = 0;
    int words = 0;
    int sentences = 0;
    int letters = 0;
    do
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        i++;
    }
    while (text[i] != '\0');
    words++;
    
    float L = (float) letters/ (float) words * 100.0;
    float S = (float) sentences/ (float) words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    int grade = (int) index;
    if (index - (int) index > 0.5)
    {
        grade++;
    }
    
    if (grade < 1)
    {
        grade = 1;
        printf("Grade %d\n", grade);
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
