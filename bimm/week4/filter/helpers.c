#include "helpers.h"
#include <stdio.h> //added to mess with printf
#include <math.h>

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
    RGBTRIPLE blurCalcArray[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blurCalcArray[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int vertstart = (int) fmax(0, i - 1);
            int horzstart = (int) fmax(0, j - 1);
            int vertend = (int) fmin(i + 1, height - 1);
            int horzend = (int) fmin(j + 1, width - 1);
            int dims = ((vertend + 1) - vertstart) * ((horzend + 1) - horzstart);
            
            float bblur = 0;
            float gblur = 0;
            float rblur = 0;
            
            for (int m = vertstart; m <= vertend; m++)
            {
                for (int n = horzstart; n <=horzend; n++)
                {
                    bblur += (float) blurCalcArray[m][n].rgbtBlue/dims;
                    gblur += (float) blurCalcArray[m][n].rgbtGreen/dims;
                    rblur += (float) blurCalcArray[m][n].rgbtRed/dims;
                }
            }
            image[i][j].rgbtBlue = (int) round(bblur);
            image[i][j].rgbtGreen = (int) round(gblur);
            image[i][j].rgbtRed = (int) round(rblur);
        }
    }



    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE sobelCalcArray[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sobelCalcArray[i][j] = image[i][j];
        }
    }
    //initialize the sobel kernels
    //create scanning array for each pixel
    //calculate Gx and Gy
    //calculate the final (int) value and max at 255
    return;
}
