#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//functions
//check for letters
int checkAlpha (string s);
//repeated character function
int checkRepeat (string s);
//func apply cipher


int main (int argc, string argv[])
{
    if (argc == 2)
    {
        if (strlen(argv[1]) == 26)
        {
            if(checkRepeat(argv[1]) == 0)
            {
                if(checkAlpha(argv[1]) == 0)
                {
                    string key = argv[1];
                    string input_text = get_string("plaintext: ");
                    char cipher_text[strlen(input_text)];
                    string upper_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    string lower_alpha = "abcdefghijklmnopqrstuvwxyz";
                    int upper_key[25];
                    int lower_key[25];
                    //create the uppercase key
                    for (int i = 0; i < 26; i++)
                    {
                        if (key[i] >= 'a' && key[i] <= 'z')
                        {
                            upper_key[i] = key[i] - 32;
                        }
                        else
                        {
                            upper_key[i] = key[i];
                        }
                    }
                    //create the lowercase key
                    for (int i = 0; i < 26; i++)
                    {
                        if (key[i] >= 'a' && key[i] <= 'z')
                        {
                            lower_key[i] = key[i];
                        }
                        else
                        {
                            lower_key[i] = key[i] + 32;
                        }
                    }
                    printf("ciphertext: ");
                    //iterate through the input_text, search alphabet keys
                    for (int i = 0; i <= strlen(input_text); i++)
                    {
                        if ((input_text[i] < 'A' || input_text[i] > 'Z') && (input_text[i] < 'a' || input_text[i] > 'z'))
                            {
                                cipher_text[i] = input_text[i];
                            }
                        //TODO: Refactor to check if upper or lower case, then loop through
                        for (int j = 0; j < 26; j++)
                        {
                            if (input_text[i] == upper_alpha[j])
                            {
                                cipher_text[i] = upper_key[j];
                            }
                            if (input_text[i] == lower_alpha[j])
                            {
                                cipher_text[i] = lower_key[j];
                            }
                        }
                    }
                    printf("%s\n",cipher_text);
                    return 0;
                }
                else
                {
                    printf("Only alpha characters permitted\n");
                    return 1;
                }
            }
            else
            {
                printf("All key values must be unique\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 letters\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int checkRepeat (string s)
{
    for (int i = 0; i < 26; i++)
    {
        for(int j = i + 1; j < 26; j++)
        {
            if (s[i] == s[j])
            {
                return 1;
                break;
            }
        }
    }
    return 0;
}

int checkAlpha (string s)
{
    for (int i = 0; i < 26; i++)
    {
        if ((s[i] < 'A' || s[i] > 'Z') && (s[i] < 'a' || s[i] > 'z'))
        {
            return 1;
            break;
        }
    }
    return 0;
}
