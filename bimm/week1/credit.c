#include <cs50.h>
#include <stdio.h>
#include <signal.h>
//raise(SIGINT); If you want to set a breakpoint

int main(void)
{
    long test_cc = 0;
    test_cc = get_long("Number:\n");
    long test_cc_for_digits = test_cc;
    long test_cc2 = test_cc;
    int scanned_digit = 0;
    int second_checksum = 0;
    int x_digit = 0;
    int modulo_x_digit = 0;
    int first_checksum = 0;
    int checksum = 0;
    int d_counter = 0;
    int loop_counter = 0;
    int first_digit = 0;
    int first_two_digits = 0;
    long divisor = 1;

    /*Get the first and second digits and store them*/

    while (test_cc_for_digits > 0) D
    {
        scanned_digit = test_cc_for_digits % 10;
        test_cc_for_digits = test_cc_for_digits / 10;
        d_counter++;
    }
    
//calculate how many times you need to loop to get first two digits
    loop_counter = d_counter - 2; 
    while (loop_counter >= 1) //get the divisor
    {
        divisor = divisor * 10;
        loop_counter--;
    }
    // get the first and first two digits
    first_two_digits = test_cc / divisor; 
    first_digit = first_two_digits / 10;

    /* Calculating the first part of the checksum */
    
//divide by 10 prior to the loop so we start on the second last digit
    test_cc = test_cc / 10; 
    while (test_cc > 0)
    {
        scanned_digit = test_cc % 10;
	//multiply the current digit by 2
        x_digit = scanned_digit * 2; 
	//store the remainder of the divide by 10.
        modulo_x_digit = x_digit % 10; 
	//if the multiplied digit is greated than 10, we can just add a 1 since it'll never be more than 18
        while (x_digit >= 10) 

        {
            first_checksum = first_checksum + 1; 
            x_digit = 0;
        }
	// add the digits to the modulo
        first_checksum = first_checksum + modulo_x_digit; 
	//move on to the next reqd digit
        test_cc = test_cc / 100; 

    }

    /* Calculating the second part of the checksum */
    //sum the digits
    while (test_cc2 > 0) 
    {
        scanned_digit = test_cc2 % 10; 
        second_checksum = second_checksum + scanned_digit;
        test_cc2 = test_cc2 / 100;
    }
    //calculate the final checksum
    checksum = first_checksum + second_checksum; 

    /* Detect the type of card, I got lazy here and I don't care */

    if (checksum % 10 == 0 && (first_two_digits == 37 || first_two_digits ==  34))
    {
        printf("AMEX\n");
    }
    else if (checksum % 10 == 0 && (first_two_digits == 51 || first_two_digits ==  52 || first_two_digits == 53 || first_two_digits ==  54 || first_two_digits ==  55))
    {
        printf("MASTERCARD\n");
    }
    else if (checksum % 10 == 0 && (d_counter == 13 || d_counter == 16) && first_digit == 4) 
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}