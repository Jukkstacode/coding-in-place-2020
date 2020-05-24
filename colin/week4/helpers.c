#include "helpers.h"
#include "math.h"
#include "stdio.h"

//Functions
RGBTRIPLE blurPixel(int i, int j, int height, int width, RGBTRIPLE[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //Calculate all values in "image" and replace them
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate value the pixel should be
            int pixelAverage = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            //Replace it within "image"
            image[i][j].rgbtBlue = pixelAverage;
            image[i][j].rgbtGreen = pixelAverage;
            image[i][j].rgbtRed = pixelAverage;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterate through each row in the image, flipping it
    for (int i = 0; i < height; i++)
    {
        //Store reflected version of first half of row in a temporary array
        RGBTRIPLE tmpArray[width / 2];
        for (int j = 0; j < (width / 2); j++)
        {
            tmpArray[j] = image[i][width - j - 1];
        }

        //Replace second half of row with mirror image
        for (int j = (width / 2); j < width; j++)
        {
            image[i][j] = image[i][width - j - 1];
        }

        //Replace first half of row with temporary array
        for (int j = 0; j < (width / 2); j++)
        {
            image[i][j] = tmpArray[j];
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create temporary file and store original image in it
    RGBTRIPLE tempArray[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempArray[i][j] = image[i][j];
        }
    }

    //For each cell, calculate the "blurred" value using the cells nearby and change the cell to that value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Set up the boundaries on which to do the average
            int xstart = (int) fmax(0, i - 1);
            int ystart = (int) fmax(0, j - 1);
            int xend = (int) fmin(i + 1, height - 1);
            int yend = (int) fmin(j + 1, width - 1);
            int numvals = (yend - ystart + 1) * (xend - xstart + 1);

            //iterate through values nearby and create average
            float red = 0;
            float green = 0;
            float blue = 0;

            for (int k = xstart; k <= xend; k++)
            {
                for (int l = ystart; l <= yend; l++)
                {
                    blue += (float) tempArray[k][l].rgbtBlue / numvals;
                    green += (float) tempArray[k][l].rgbtGreen / numvals;
                    red += (float) tempArray[k][l].rgbtRed / numvals;
                }
            }

            image[i][j].rgbtRed = (int) round(red);
            image[i][j].rgbtBlue = (int) round(blue);
            image[i][j].rgbtGreen = (int) round(green);

            //printf("red: %d green: %d blue: %d\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);

        }

        //printf("red: %d green: %d blue: %d\n", image[i][0].rgbtRed, image[i][0].rgbtGreen, image[i][0].rgbtBlue);

    }

    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Define Gx and Gy
    int gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    //Create a copy of the image
    RGBTRIPLE tempArray[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempArray[i][j] = image[i][j];
        }
    }

    //For each pixel, pull in the nearby variables, compute the gx and gy, and rewrite as edges
    //For each row of the image
    for (int i = 0; i < height; i++)
    {
        //For each column / pixel of the image
        for (int j = 0; j < width; j++)
        {
            //Pull in all 9 nearby pixel color values, first:
            //Create an array for the values, and two values for the pixel Gx and Gy, each holding the 3 colors
            RGBTRIPLE nearby[3][3];
            int pixelGx[3] = {0, 0, 0};
            int pixelGy[3] = {0, 0, 0};

            //printf("Pixel %d, %d\n", i, j);

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    //Set everything in the array to be black to start
                    nearby[k][l].rgbtRed = 0;
                    nearby[k][l].rgbtGreen = 0;
                    nearby[k][l].rgbtBlue = 0;

                    //Second, loop through all nearby values and pull them in,
                    //if the value is outside of the images array then skip changing that value
                    if ((i + k) != 0 && (i + k) < (height + 1) && (j + l) != 0 && (j + l) < (width + 1))
                    {
                        nearby[k][l].rgbtRed = tempArray[i + k - 1][j + l - 1].rgbtRed;
                        nearby[k][l].rgbtGreen = tempArray[i + k - 1][j + l - 1].rgbtGreen;
                        nearby[k][l].rgbtBlue = tempArray[i + k - 1][j + l - 1].rgbtBlue;
                    }
                    
                    //printf("%d-%d-%d ", nearby[k][l].rgbtRed, nearby[k][l].rgbtGreen, nearby[k][l].rgbtBlue);
                    
                    //Add into gx and gy
                    pixelGx[0] += nearby[k][l].rgbtRed * gx[k][l];
                    pixelGx[1] += nearby[k][l].rgbtGreen * gx[k][l];
                    pixelGx[2] += nearby[k][l].rgbtBlue * gx[k][l];
                    
                    pixelGy[0] += nearby[k][l].rgbtRed * gy[k][l];
                    pixelGy[1] += nearby[k][l].rgbtGreen * gy[k][l];
                    pixelGy[2] += nearby[k][l].rgbtBlue * gy[k][l];

                }
                //printf("\n");
            }
            
            //Compute the multiplication of those values with Gx and Gy
            //printf("\n");

            //printf("pixelGx sum: %d-%d-%d; ", pixelGx[0], pixelGx[1], pixelGx[2]);
            //printf("pixelGy sum: %d-%d-%d\n", pixelGy[0], pixelGy[1], pixelGy[2]);

            //Square Gx and Gy, compute the square root, and enter it into the pixel value
            image[i][j].rgbtRed = fmin(round(sqrt(pixelGx[0] * pixelGx[0] + pixelGy[0] * pixelGy[0])), 255);
            image[i][j].rgbtGreen = fmin(round(sqrt(pixelGx[1] * pixelGx[1] + pixelGy[1] * pixelGy[1])), 255);
            image[i][j].rgbtBlue = fmin(round(sqrt(pixelGx[2] * pixelGx[2] + pixelGy[2] * pixelGy[2])), 255);

            //printf("Pixel output: %d-%d-%d\n\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
        
    }
    return;
}
