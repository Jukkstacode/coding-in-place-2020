#include "helpers.h"
#include <stdio.h>
#include <math.h>

typedef struct
{
    int  rgbtBlue;
    int  rgbtGreen;
    int  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLEint;

void addRGBsY2X(RGBTRIPLEint *x, RGBTRIPLE y);
void divideRGB(RGBTRIPLEint *x, int divisor);
void assignRGBint2Byte(RGBTRIPLE *x, RGBTRIPLEint y);
void addRGBsY2Xmult(RGBTRIPLEint *x, RGBTRIPLE y, int mult);
RGBTRIPLEint edgeVal(RGBTRIPLEint x, RGBTRIPLEint y);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int mean;
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            mean = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j] = (RGBTRIPLE) { mean, mean, mean };
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width/2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // height = 3;
    // width = 3;
    RGBTRIPLE evenRow[width], oddRow[width];
    
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int kStart = i==0 ? 0 : i-1;
            int kEnd = i<height-1 ? i+1 : i;
            int lStart = j==0 ? 0 : j-1;
            int lEnd = j<width-1 ? j+1 : j;
            int counter = 0;
            // int R, G, B;
            // R = G = B = 0;
            RGBTRIPLEint tmp = { 0, 0, 0 };
            // if (i==1 && j == 1)
            // {
            //     printf("t0:%d, %d, %d, %d\n", tmp.rgbtBlue, tmp.rgbtGreen, tmp.rgbtRed, counter);
            // }
            // printf("%d, %d, %d, %d, %d, %d, %d\n", i, j, kStart, kEnd, lStart, lEnd, counter);
            for (int k = kStart; k<=kEnd;k++)
            {
                for (int l = lStart; l<=lEnd;l++)
                {
                    // printf("1:%d, %d, %d, %d, %d\n", i, j, k, l, counter);
                    // R += image[k][l].rgbtRed;
                    // G += image[k][l].rgbtGreen;
                    // B += image[k][l].rgbtBlue;
                    addRGBsY2X(&tmp, image[k][l]);
                    // if ((i*width+j)%10000==0)
                    // {
                    //     printf("i:%d, %d, %d, %d\n", image[k][l].rgbtBlue, image[k][l].rgbtGreen, image[k][l].rgbtRed, counter);
                    // }
                    // if (i==1 && j == 1)
                    // {
                    //     printf("i:%d, %d, %d, %d\n", image[k][l].rgbtBlue, image[k][l].rgbtGreen, image[k][l].rgbtRed, counter);
                    // }
                    counter++;
                    // if ((i*width+j)%10000==0)
                    // {
                    //     printf("t:%d, %d, %d, %d\n", B, G, R, counter);
                    // }
                    // if (i==1 && j == 1)
                    // {
                    //     printf("t:%d, %d, %d, %d\n", tmp.rgbtBlue, tmp.rgbtGreen, tmp.rgbtRed, counter);
                    // }
                    // printf("2:%d, %d, %d, %d, %d\n", i, j, k, l, counter);
                }
            }
            if (i > 1)
            {
                // printf("out1:%d, %d, %d\n", i, j, i-2);
                image[i-2][j] = i%2 == 0 ? evenRow[j] : oddRow[j];
            }
            if (counter < 1)
            {
                printf("counter < 1: %d, %d, %d, %d, %d, %d, %d\n", i, j, kStart, kEnd, lStart, lEnd, counter);
                // printf("%d, %d, %d\n", i, j, counter);
                return;
            }
            divideRGB(&tmp, counter);
            // if ((i*width+j)%10000==0)
            // {
            //     printf("tf:%d, %d, %d, %d\n", B / counter, G / counter, R / counter, counter);
            // }
            // if (i == 1 && j == 1)
            // {
            //     printf("tf:%d, %d, %d, %d\n", tmp.rgbtBlue, tmp.rgbtGreen, tmp.rgbtRed, counter);
            // }
            // if ( i % 2 == 0 )
            // {
            //     evenRow[j].rgbtRed = R / counter;
            //     evenRow[j].rgbtGreen = G / counter;
            //     evenRow[j].rgbtBlue = B / counter;
            // }
            // else
            // {
            //     oddRow[j].rgbtRed = R / counter;
            //     oddRow[j].rgbtGreen = G / counter;
            //     oddRow[j].rgbtBlue = B / counter;
            // }
            if ( i % 2 == 0 )
            {
                assignRGBint2Byte(&evenRow[j], tmp);
            }
            else
            {
                assignRGBint2Byte(&oddRow[j], tmp);
            }
        }
    }
    for (int i = height-2; i<height; i++)
    {
        // printf("i: %d\n",i);
        for (int j = 0; j<width; j++)
        {
            image[i][j] = i%2 == 0 ? evenRow[j] : oddRow[j];
            // printf("out2:%d, %d\n", i, j);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // height = 4;
    // width = 4;
    // int xx = 200;
    // int yy = 400;
    RGBTRIPLE evenRow[width], oddRow[width];
    int gx[3][3], gy[3][3];
    gx[0][1] = gx[1][1] = gx[2][1] = gy[1][0] = gy[1][1] = gy[1][2] = 0;
    gx[0][2] = gx[2][2] = gy[2][0] = gy[2][2] = 1;
    gx[0][0] = gx[2][0] = gy[0][0] = gy[0][2] = -1;
    gx[1][2] = gy[2][1] = 2;
    gx[1][0] = gy[0][1] = -2;
    
    // printf("gx\n");
    // for (int i = 0; i<3; i++)
    // {
    //     for (int j = 0; j<3; j++)
    //     {
    //         printf( j != 2 ? "%d, " : "%d" ,gx[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("gy\n");
    // for (int i = 0; i<3; i++)
    // {
    //     for (int j = 0; j<3; j++)
    //     {
    //         printf( j != 2 ? "%d, " : "%d" ,gy[i][j]);
    //     }
    //     printf("\n");
    // }
    // return;
    
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int kStart = i==0 ? 0 : -1;
            int kEnd = i<height-1 ? 1 : 0;
            int lStart = j==0 ? 0 : -1;
            int lEnd = j<width-1 ? 1 : 0;
            int counter = 0;
            // int R, G, B;
            // R = G = B = 0;
            // RGBTRIPLEint tmp = { 0, 0, 0 };
            RGBTRIPLEint tmpX = { 0, 0, 0 };
            RGBTRIPLEint tmpY = { 0, 0, 0 };
            // if (i==xx && j == yy)
            // {
            //     printf("tx0:%d, %d, %d, %d\n", tmpX.rgbtBlue, tmpX.rgbtGreen, tmpX.rgbtRed, counter);
            //     printf("ty0:%d, %d, %d, %d\n", tmpY.rgbtBlue, tmpY.rgbtGreen, tmpY.rgbtRed, counter);
            // }
            // if ((i*width+j)%10000==0)
            // {
            //     printf("t0:%d, %d, %d, %d\n", B, G, R, counter);
            // }
            // printf("%d, %d, %d, %d, %d, %d, %d\n", i, j, kStart, kEnd, lStart, lEnd, counter);
            for (int k = kStart; k<=kEnd;k++)
            {
                for (int l = lStart; l<=lEnd;l++)
                {
                    // printf("1:%d, %d, %d, %d, %d\n", i, j, k, l, counter);
                    if (k != 0 || l != 0)
                    {
                        // R += image[k][l].rgbtRed;
                        // G += image[k][l].rgbtGreen;
                        // B += image[k][l].rgbtBlue;
                        addRGBsY2Xmult(&tmpX, image[i+k][j+l], gx[k+1][l+1]);
                        addRGBsY2Xmult(&tmpY, image[i+k][j+l], gy[k+1][l+1]);
                        // if ((i*width+j)%10000==0)
                        // {
                        //     printf("i:%d, %d, %d, %d\n", image[k][l].rgbtBlue, image[k][l].rgbtGreen, image[k][l].rgbtRed, counter);
                        // }
                        counter++;
                        // if ((i*width+j)%10000==0)
                        // {
                        //     printf("t:%d, %d, %d, %d\n", B, G, R, counter);
                        // }
                        // if (i==xx && j == yy)
                        // {
                        //     printf("i:%d, %d, %d, %d\n", image[i+k][j+l].rgbtBlue, image[i+k][j+l].rgbtGreen, image[i+k][j+l].rgbtRed, counter);
                        //     printf("tx:%d, %d, %d, %d, %d\n", tmpX.rgbtBlue, tmpX.rgbtGreen, tmpX.rgbtRed, gx[k+1][l+1], counter);
                        //     printf("ty:%d, %d, %d, %d, %d\n", tmpY.rgbtBlue, tmpY.rgbtGreen, tmpY.rgbtRed, gy[k+1][l+1], counter);
                        // }
                        // printf("2:%d, %d, %d, %d, %d\n", i, j, k, l, counter);
                    }
                }
            }
            if (i > 1)
            {
                image[i-2][j] = i%2 == 0 ? evenRow[j] : oddRow[j];
            }
            if (counter < 1)
            {
                printf("counter < 1: %d, %d, %d, %d, %d, %d, %d\n", i, j, kStart, kEnd, lStart, lEnd, counter);
                // printf("%d, %d, %d\n", i, j, counter);
                return;
            }
            // if ((i*width+j)%10000==0)
            // {
            //     printf("tf:%d, %d, %d, %d\n", B / counter, G / counter, R / counter, counter);
            // }
            
            // if ( i % 2 == 0 )
            // {
            //     evenRow[j].rgbtRed = R / counter;
            //     evenRow[j].rgbtGreen = G / counter;
            //     evenRow[j].rgbtBlue = B / counter;
            // }
            // else
            // {
            //     oddRow[j].rgbtRed = R / counter;
            //     oddRow[j].rgbtGreen = G / counter;
            //     oddRow[j].rgbtBlue = B / counter;
            // }
            RGBTRIPLEint tmp = edgeVal(tmpX, tmpY);
            // if (i==xx && j == yy)
            // {
            //     printf("txf:%d, %d, %d\n", tmpX.rgbtBlue, tmpX.rgbtGreen, tmpX.rgbtRed);
            //     printf("tyf:%d, %d, %d\n", tmpY.rgbtBlue, tmpY.rgbtGreen, tmpY.rgbtRed);
            //     printf("tf:%d, %d, %d\n", tmp.rgbtBlue, tmp.rgbtGreen, tmp.rgbtRed);
            // }
            
            if ( i % 2 == 0 )
            {
                assignRGBint2Byte(&evenRow[j], edgeVal(tmpX, tmpY));
            }
            else
            {
                assignRGBint2Byte(&oddRow[j], edgeVal(tmpX, tmpY));
                // if (i==xx && j == yy)
                // {
                //     printf("tOUT:%d, %d, %d\n", oddRow[j].rgbtBlue, oddRow[j].rgbtGreen, oddRow[j].rgbtRed);
                // }
            }
        }
    }
    for (int i = height-2; i<height; i++)
    {
        // printf("i: %d\n",i);
        for (int j = 0; j<width; j++)
        {
            image[i][j] = i%2 == 0 ? evenRow[j] : oddRow[j];
            // if (i==xx && j == yy)
            // {
            //     printf("tOUTi:%d, %d, %d\n", image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
            // }
        }
    }
    return;
}


// myfuncs
void addRGBsY2X(RGBTRIPLEint *x, RGBTRIPLE y)
{
    x->rgbtBlue += y.rgbtBlue;
    x->rgbtGreen += y.rgbtGreen;
    x->rgbtRed += y.rgbtRed;
}

void divideRGB(RGBTRIPLEint *x, int divisor)
{
    if ( divisor > 0 )
    {
        x->rgbtBlue = round(x->rgbtBlue / (float) divisor);
        x->rgbtGreen = round(x->rgbtGreen / (float) divisor);
        x->rgbtRed = round(x->rgbtRed / (float) divisor);
    }
    else
    {
        printf("0?\n");
    }
}

void assignRGBint2Byte(RGBTRIPLE *x, RGBTRIPLEint y)
{
    x->rgbtBlue = y.rgbtBlue > 255 ? 255 : y.rgbtBlue;
    x->rgbtGreen = y.rgbtGreen > 255 ? 255 : y.rgbtGreen;
    x->rgbtRed = y.rgbtRed > 255 ? 255 : y.rgbtRed;
}

void addRGBsY2Xmult(RGBTRIPLEint *x, RGBTRIPLE y, int mult)
{
    if (mult != 0)
    {
        x->rgbtBlue += y.rgbtBlue * mult;
        x->rgbtGreen += y.rgbtGreen * mult;
        x->rgbtRed += y.rgbtRed * mult;
    }
}

RGBTRIPLEint edgeVal(RGBTRIPLEint x, RGBTRIPLEint y)
{
    RGBTRIPLEint out;
    out.rgbtBlue = round(sqrt(pow(x.rgbtBlue,2)+pow(y.rgbtBlue,2)));
    out.rgbtGreen = round(sqrt(pow(x.rgbtGreen,2)+pow(y.rgbtGreen,2)));
    out.rgbtRed = round(sqrt(pow(x.rgbtRed,2)+pow(y.rgbtRed,2)));
    return out;
}