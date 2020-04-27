#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int desired_level;
    int current_level = 1;
    int num_dots = 0;
    int num_bricks = 0;
    
    do
    {
        desired_level = get_int("How high is your pyramid?\n");
    }
    while(desired_level < 1 || desired_level > 8);
    
    while (desired_level >= current_level) 
    {
        while(num_dots < desired_level - current_level)
        {
            printf(" ");
            num_dots++;
        }
        while (num_bricks < current_level)
        {
            printf("#");
            num_bricks++;
        }
        current_level++;
        printf("\n");
        num_dots = 0;
        num_bricks = 0;
    }
}
        