#include <stdio.h>
#include <cs50.h>

//Set boolean values
#define TRUE 1
#define FALSE 0

//set up functions
long get_card_number(void);
bool validity_test(long cardnumber, long maxlength);
string card_issuer(long cardnumber, long maxlength);
int getdigit(long cardnumber, long spot_in_cardnumber);
long getlength(long cardnumber, long maxlength);

int main(void)
{
    //Prompt for user input
    long cardnumber = get_card_number();

    //Set global variable for maximum card length
    long maxlength = 10000000000000000;

    //Check if valid number
    bool number_valid = validity_test(cardnumber, maxlength);

    //Determine card type
    string test_outcome;
    if (number_valid == TRUE)
    {
        test_outcome = card_issuer(cardnumber, maxlength);
    }
    else
    {
        test_outcome = "INVALID";
    }

    //Return answer
    printf("%s\n", test_outcome);

}

//Get the card number from the user and ensures it is valid, otherwise re-prompts user
long get_card_number(void)
{
    long cardnumber = get_long("Number: ");
    return cardnumber;
}

//Check whether the credit card is a legitimate card number
bool validity_test(long cardnumber, long maxlength)
{
    //create the value to hold the total checksum
    int checksum = 0;

    //multiply by two and add together every second digit starting from the second to last
    for (long i = 10; i < maxlength; i *= 100)
    {
        if ((getdigit(cardnumber, i) * 2) >= 10)
        {
            checksum += 1 + ((getdigit(cardnumber, i) * 2) % 10);
        }
        else
        {
            checksum += getdigit(cardnumber, i) * 2;
        }
    }

    //add to sum of every second digit starting from last
    for (long i = 1; i < maxlength; i *= 100)
    {
        checksum += getdigit(cardnumber, i);
    }

    //check whether that value has a zero at the end, return validity
    if ((checksum % 10 == 0) && ((cardnumber / maxlength) == 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//Determine who issued the card and return VISA, MASTERCARD, AMEX, or INVALID if card fits none of their descriptors
string card_issuer(long cardnumber, long maxlength)
{
    //Create a space to hold the issuer of the card, starting with default of INVALID, as well as a constant with the maximum length of any card
    string cardissuer = "INVALID";

    //check if VISA
    if (((getdigit(cardnumber, 1000000000000000) == 4) && (getlength(cardnumber, maxlength) == 1000000000000000)) 
        || ((getdigit(cardnumber, 1000000000000) == 4) && (getlength(cardnumber, maxlength) == 1000000000000)))
    {
        cardissuer = "VISA";
    }
    //check if MASTERCARD
    else if (getdigit(cardnumber, 1000000000000000) == 5)
    {
        if (getdigit(cardnumber, 100000000000000) >= 1 && getdigit(cardnumber, 100000000000000) <= 5)
        {
            cardissuer = "MASTERCARD";
        }
    }
    //check if AMEX
    else if (getdigit(cardnumber, 100000000000000) == 3)
    {
        if (getdigit(cardnumber, 10000000000000) == 4 || getdigit(cardnumber, 10000000000000) == 7)
        {
            cardissuer = "AMEX";
        }
    }
    //if none of those card types, return that it's invalid
    else
    {
        cardissuer = "INVALID";
    }

    return cardissuer;
}

//find the digit specified in a card number
int getdigit(long cardnumber, long spot_in_cardnumber)
{
    //Find and return the digit
    int digit;

    digit = (cardnumber % (spot_in_cardnumber * 10)) / spot_in_cardnumber;
    return digit;
}

//find the length of a card number
long getlength(long cardnumber, long maxlength)
{
    bool foundlength = FALSE;
    long length = maxlength;

    while (foundlength == FALSE)
    {
        if ((cardnumber / length) >= 1)
        {
            foundlength = TRUE;
        }

        length /= 10;
    }
    return length * 10;
}
