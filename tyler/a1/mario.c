// include header
#include <cs50.h>
#include <stdio.h>

// functions
// makes a pyramid of height h
void pyramid(int h);
// prints the nth step of an h high pyramid
void print_step(int n, int h);

//main
int main(void)
{
    // init var
    int height;
    //get a height integer between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);
    // make the pyramid
    pyramid(height);
}

void pyramid(int h)
{
    // make the pyramid layer by layer
    for(int i=0; i<h; i++)
    {
        print_step(i, h);
    }
}

//print each layer of the pyramid
void print_step(int n, int h)
{
    // start with the rquired white space
    for(int j=0; j<h-n-1;j++)
    {
        printf(" ");
    }
    // print the leading #'s
    for(int j=0; j<n+1;j++)
    {
        printf("#");
    }
    // print the empty space in the middle
    printf("  ");
    // print he trailing #'s
    for(int j=0; j<n+1;j++)
    {
        printf("#");
    }
    printf("\n");
}
