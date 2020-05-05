#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int checkinput(int argc, string firstarg);
string translate(string key, string text);

int main(int argc, string argv[])
{
    /* Ensure that the user has entered 26 unique characters as a single key */
    int valid_input = checkinput(argc, argv[1]);
    if (valid_input != 0)
    {
        printf("Enter one 26 unique digit key\nError %d\n", valid_input);
        return 1;
    }

    /* Get the text to convert from the user */
    string text = get_string("plaintext: ");

    /* Convert the text using the cipher and print out the cipher text */
    string outputtext = translate(argv[1], text);
    printf("\n");

    return 0;
}

int checkinput(int argc, string firstarg)
{
    //Check to make sure only one command-line argument is sent
    if (argc != 2)
    {
        return 1;
    }

    //Check to ensure there are 26 unique letters, first converting the string to all upper case
    int i = 0;
    while (firstarg[i] != '\0')
    {
        firstarg[i] = (char) toupper(firstarg[i]);
        if (isalpha(firstarg[i]) == 0)
        {
            return 2;
        }
        i++;
    }
    
    //Check to make sure there are 26 letters
    if (i != 26)
    {
        return 3;
    }

    //Check that the letters in the key are unique, return an error if they are not
    i = 0;

    while (firstarg[i] != '\0')
    {
        int j = i + 1;
        while (firstarg[j] != '\0')
        {
            if (toupper(firstarg[i]) == toupper(firstarg[j]))
            {
                return 4;
            }
            j++;
        }
        i++;
    }

    return 0;
}

string translate(string key, string text)
{
    //Initialize variables
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    printf("ciphertext: ");

    //Loop through the alphabet to find what position in the alphabet should be replaced by the text in the key
    while (text[i] != '\0')
    {
        //Check whether the text is alphabetical, if so then substitute, if not then print as is
        if (isalpha(text[i]))
        {
            for (int j = 0; j < 26; j++)
            {
                if (alphabet[j] == toupper(text[i]))
                {
                    if (isupper(text[i]))
                    {
                        printf("%c", toupper(key[j]));
                    }
                    else
                    {
                        printf("%c", tolower(key[j]));
                    }
                }
            }
        }
        else
        {
            printf("%c", text[i]);
        }

        i++;
    }

    return 0;
}
