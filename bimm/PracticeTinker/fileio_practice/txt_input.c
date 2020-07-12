#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main (void)
{
    FILE *apndptr = fopen("diary.txt", "a");
    if (apndptr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    char *userInputString = get_string("Enter a string: ");
    fputs(userInputString,apndptr);
    fputs("\n",apndptr);
    FILE *rdptr = fopen("diary.txt","r");
    fclose(apndptr);
    char ch;
    while ((ch = fgetc(rdptr)) != EOF)
    {
        printf("%c",ch);
    }
    fclose(rdptr);
}