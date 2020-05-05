#include <stdio.h>
#include <cs50.h>

int get_height(void);
void pyramid_line(int height, int i, bool direction);

int main(void)
{
    //get correct user input for height
    int height = get_height();

    //print out obstacle in Mario
    for (int i = 1; i <= height; i++)
    {
        //print first half of pyramid
        pyramid_line(height, i, 0);

        //print double space between pyramids
        printf("  ");

        //print second half of pyramid
        pyramid_line(height, i, 1);

        //make room for the next pyramid layer
        printf("\n");
    }
}

//function to get the required height of the obstacle from the user
int get_height(void)
{
    //define height and get the height from the user
    int height;
    do
    {
        height = get_int("Height: ");
    }
    //set parameters the user must enter as being an integer between 1 and 8. Note the assignment doesn't tell the user this but that would help
    while (height <1 || height > 8);

    return height;
}

//print a line of a pyramid, given the height and the layer of the pyramid to be printed, and whether the slope is up (0) or down (1)
void pyramid_line(int height, int i, bool direction)
{
    for (int j = 0; j < (height - i); j++)

        //print spaces on the "up" part of the pyramid
        if (direction == 0)
        {
            printf(" ");
        }

        //print pyramid blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
}
