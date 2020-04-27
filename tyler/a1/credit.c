// include header
#include <cs50.h>
#include <stdio.h>

// functions
string validate_cc(long ccnum);
int sum_digits(int x);
string get_card_type(long ccnum);

//main
int main(void)
{
    // get cc number
    long ccnum = get_long("Number:");
    // validate the cc number and print the return
    printf("%s\n", validate_cc(ccnum));
}

string validate_cc(long ccnum)
{
    // cehck first if the number has the rught number of digits and leading digits to be valid
    string card_type = get_card_type(ccnum);
    
    if (card_type[0] == 'I')
    {
        // if the cc number is invalid at this point end here
        return card_type;
    }
    else
    {
        int i = 0; //ith digit off the cc number from right
        int sum_mult2_digits = 0; // sum of the products digits
        int sum_no_mult = 0; // sum of the other digits
        int digit; // placeholder for the current digit
        while (ccnum) // loop through all digits in the cc number
        {
            digit = ccnum % 10; // get the right most digit
            ccnum /= 10; // remove the right most digit
            if (i % 2 == 0) // check which sum to do
            {
                sum_no_mult += digit; // even digits from right (start a 0) get added
            }
            else
            {
                sum_mult2_digits += sum_digits(digit * 2); // ods get mult by 2 then have thirt digits summed 
            }
            i++;
            //printf("%ld, %d, %d, %d, %d \n", ccnum, digit, sum_no_mult, sum_mult2_digits, i);
        }
        if ((sum_no_mult + sum_mult2_digits) % 10 == 0) // check if the cc number if valid
        {
            return card_type; // if yes return card type
        }
        else
        {
            return "INVALID"; // if not return invalid
        }
    }
}

// sum the digits in the supplied integer
int sum_digits(int x)
{
    int sum = 0;
    while (x)
    {
        sum += x % 10; // add current digit
        x /= 10; // get next digit
    }
    return sum;
}

// determine what type of card this cc number corresponds to
string get_card_type(long ccnum)
{
    int first_digits = ccnum / 1000000000000;
    // visa, 13 or 16 digits starting with 4
    if (first_digits == 4 || first_digits / 1000 == 4)
    {
        return "VISA";
    }
    // amex, 15 digits starting with 34 or 37
    else if (first_digits / 10 == 34 || first_digits / 10 == 37)
    {
        return "AMEX";
    }
    // mastercard, 16 digits stating with 51 to 55
    else if (first_digits / 100 < 56 && first_digits / 100 >= 51)
    {
        return "MASTERCARD";        
    }
    else
    {
        return "INVALID";    
    }
}
