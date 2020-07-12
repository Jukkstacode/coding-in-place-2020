#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main (void)
{
    //open file
    FILE *file = fopen("phonebook.csv", "a"); //doing this appends to the end of the file
    //FILE *file = fopen("testcreate.csv", "w"); //doing this overwrites the file completely
    
    //get info from user
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");
    
    //append new info to file
    fprintf(file, "%s,%s\n",name, number);
    
    //close file
    fclose(file);
}