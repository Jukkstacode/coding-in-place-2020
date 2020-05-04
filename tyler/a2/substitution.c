#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // get text
    if (argc == 2)
    {
        string text = argv[1];
        bool notTakenChar[26];
        
        for (int i = 0; i < 26; i++)
        {
            notTakenChar[i] = true;
        }
        
        char key[26];
        int i = 0;
        int keyVal;
        do
        {
            if (i == 26)
            {
                printf("Key must only contain 26 characters.\n");
                return 1;
            }
            
            if (text[i] >= 'a' && text[i] <= 'z')
            {
                keyVal = (int) text[i] - (int) 'a';
            }
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                keyVal = (int) text[i] - (int) 'A';
            }
            else
            {
                printf("Key must letters only.\n");
                return 1;
            }
            
            if ( notTakenChar[keyVal] )
            {
                notTakenChar[keyVal] = false;
                key[i] = keyVal;
            }
            else
            {
                printf("Key must not have repeated letters.\n");
                return 1;
            }
            i++;
        }
        while (text[i] != '\0');
        
        if (i != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        string plaintext = get_string("plaintext: ");
        int keyIdx;
        i = 0;
        do
        {
            if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
            {
                keyIdx = (int) plaintext[i] - (int) 'a';
                plaintext[i] = 'a' + key[keyIdx];
            }
            else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                keyIdx = (int) plaintext[i] - (int) 'A';
                plaintext[i] = 'A' + key[keyIdx];
                
            }
            i++;
        }
        while (plaintext[i] != '\0');
        printf("ciphertext: %s\n", plaintext);
        return 0;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
