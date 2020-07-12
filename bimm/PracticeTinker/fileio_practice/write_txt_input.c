#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main (void)
{
    FILE *readFile = fopen("diary.txt", "r");
    FILE *writeFile = fopen("diary_copy.txt","w");
    char ch;
    while ((ch = fgetc(readFile)) != EOF)
    {
        fwrite(&ch, sizeof(char), 1, writeFile);
    }
    fclose(readFile);
    fclose(writeFile);
}