#include "helpers.h"
#include <stdio.h> //added to mess with printf

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop across evert pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate average of three values
            int avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3;
            //update the associated rgb values to the average value 
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop across every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            //read the value of the pixel at i,j and store in a temp pixel
            RGBTRIPLE temp_pixel;
            temp_pixel = image[i][j];
            //set the pixel at i,j equal to the pixel at the opposite side
            image[i][j] = image[i][(width - 1 - j)];
            //set the opposite side pixel equal to temp
            image[i][(width - 1 - j)] = temp_pixel;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int bblur = 0;
    int gblur = 0;
    int rblur = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //bottom row apparently? I thought this would be the top row
            if (i == 0)
            {
                //bottom left corner
                if (i == 0 && j == 0)
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x2 2d array around the target pixel to get averages
                    for (int m = i; m <= i+1; m++)
                    {
                        for (int n = j; n <= j+1; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    image[i][j].rgbtBlue = (bblur/4);
                    image[i][j].rgbtGreen = (gblur/4);
                    image[i][j].rgbtRed = (rblur/4);
                }
                //bottom right corner
                else if (i == 0 && j == width - 1)
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x2 2d array around the target pixel to get averages
                    for (int m = i; m <= i+1; m++)
                    {
                        for (int n = j-1; n <= j; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    image[i][j].rgbtBlue = (bblur/4);
                    image[i][j].rgbtGreen = (gblur/4);
                    image[i][j].rgbtRed = (rblur/4);
                }
                //bottom row
                else
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x3 2d array around the target pixel to get averages
                    for (int m = i; m <= i+1; m++)
                    {
                        for (int n = j-1; n <= j+1; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    image[i][j].rgbtBlue = (bblur/6);
                    image[i][j].rgbtGreen = (gblur/6);
                    image[i][j].rgbtRed = (rblur/6);
                }
                }
                
            else if (i == height - 1)
            {
                //top left corner
                if (i == height - 1 && j == 0)
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x2 2d array around the target pixel to get averages
                    for (int m = i-1; m <= i; m++)
                    {
                        for (int n = j; n <= j+1; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    
                    image[i][j].rgbtBlue = (bblur/4);
                    image[i][j].rgbtGreen = (gblur/4);
                    image[i][j].rgbtRed = (rblur/4);
                }
                //top right corner
                else if (i == height - 1 && j == width - 1)
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x2 2d array around the target pixel to get averages
                    for (int m = i-1; m <= i; m++)
                    {
                        for (int n = j-1; n <= j; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    
                    image[i][j].rgbtBlue = (bblur/4);
                    image[i][j].rgbtGreen = (gblur/4);
                    image[i][j].rgbtRed = (rblur/4);
                }
                //top row
                else
                {
                    bblur = 0;
                    gblur = 0;
                    rblur = 0;
                    //iterate through the 2x3 2d array around the target pixel to get averages
                    for (int m = i-1; m <= i; m++)
                    {
                        for (int n = j-1; n <= j+1; n++)
                        {
                            bblur += image[m][n].rgbtBlue;
                            gblur += image[m][n].rgbtGreen;
                            rblur += image[m][n].rgbtRed;
                        }
                    }
                    image[i][j].rgbtBlue = (bblur/6);
                    image[i][j].rgbtGreen = (gblur/6);
                    image[i][j].rgbtRed = (rblur/6); 
                }
            }
            //left column
            else if (j == 0)
            {
                bblur = 0;
                gblur = 0;
                rblur = 0;
                //iterate through the 2x3 2d array around the target pixel to get averages
                for (int m = i-1; m <= i+1; m++)
                {
                    for (int n = j; n <= j+1; n++)
                    {
                        bblur += image[m][n].rgbtBlue;
                        gblur += image[m][n].rgbtGreen;
                        rblur += image[m][n].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = (bblur/6);
                image[i][j].rgbtGreen = (gblur/6);
                image[i][j].rgbtRed = (rblur/6); 
            }
            //right column
            else if (j == width - 1)
            {
                bblur = 0;
                gblur = 0;
                rblur = 0;
                //iterate through the 2x3 2d array around the target pixel to get averages
                for (int m = i-1; m <= i+1; m++)
                {
                    for (int n = j - 1; n <= j; n++)
                    {
                        bblur += image[m][n].rgbtBlue;
                        gblur += image[m][n].rgbtGreen;
                        rblur += image[m][n].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = (bblur/6);
                image[i][j].rgbtGreen = (gblur/6);
                image[i][j].rgbtRed = (rblur/6); 
            }
            //most of the gd image
            else
            {
                bblur = 0;
                gblur = 0;
                rblur = 0;
                //iterate through the 2d array around the target pixel to get averages
                for (int m = i-1; m <= i+1; m++)
                {
                    for (int n = j-1; n <= j+1; n++)
                    {
                        bblur += image[m][n].rgbtBlue;
                        gblur += image[m][n].rgbtGreen;
                        rblur += image[m][n].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = (bblur/9);
                image[i][j].rgbtGreen = (gblur/9);
                image[i][j].rgbtRed = (rblur/9);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
