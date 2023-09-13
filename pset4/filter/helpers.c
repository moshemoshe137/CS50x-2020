#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            RGBTRIPLE pixel = image[row][col];
            int sum = pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue;
            int avg = round(sum / 3.0);
            image[row][col].rgbtRed = avg;
            image[row][col].rgbtGreen = avg;
            image[row][col].rgbtBlue = avg;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2.0; col++)
        {
            // Want to map pixel[row][col] to pixel[row][width - col] and vice-versa
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // declare a new array to hold the resultant image
    // I cannot store the results in the original image
    // as they will impact the caluclation for their neighbors 
    RGBTRIPLE new_image[height][width];
    
    //loop thru each row and col
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // initialize some values to take the average
            int Rsum = 0;
            int Bsum = 0;
            int Gsum = 0;
            float count = 0.0;
            // loop thru row and col offsets of 1, 0, and -1. 
            for (int row_offset = -1; row_offset < 2; row_offset++)
            {
                for (int col_offset = -1; col_offset < 2; col_offset++)
                {
                    if ((row + row_offset) >= 0 && (row + row_offset) < height && (col + col_offset) >= 0 && (col + col_offset) < width)
                    {
                        Rsum += image[row + row_offset][col + col_offset].rgbtRed;
                        Gsum += image[row + row_offset][col + col_offset].rgbtGreen;
                        Bsum += image[row + row_offset][col + col_offset].rgbtBlue;
                        count++;
                    }
                }
            }
            int Ravg = round(Rsum / count);
            int Gavg = round(Gsum / count);
            int Bavg = round(Bsum / count);
            new_image[row][col].rgbtRed = Ravg;
            new_image[row][col].rgbtGreen = Gavg;
            new_image[row][col].rgbtBlue = Bavg;
            
        }
    }
    
    // copy new image to the original image array
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = new_image[row][col];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // declare a new array to hold the resultant image
    // I cannot store the results in the original image
    // as they will impact the caluclation for their neighbors 
    RGBTRIPLE new_image[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int GxRSum = 0;
            int GxGSum = 0;
            int GxBSum = 0;
            int GyRSum = 0;
            int GyGSum = 0;
            int GyBSum = 0;
            
            for (int row_offset = -1; row_offset < 2; row_offset++)
            {
                for (int col_offset = -1; col_offset < 2; col_offset++)
                {
                    if ((row + row_offset) >= 0 && (row + row_offset) < height && (col + col_offset) >= 0 && (col + col_offset) < width)
                    {
                        // if you're on the grid...
                        int GxFactor = Gx[row_offset + 1][col_offset + 1];
                        int GyFactor = Gy[row_offset + 1][col_offset + 1];
                        GxRSum += (GxFactor * image[row + row_offset][col + col_offset].rgbtRed);
                        GxGSum += (GxFactor * image[row + row_offset][col + col_offset].rgbtGreen);
                        GxBSum += (GxFactor * image[row + row_offset][col + col_offset].rgbtBlue);
                        GyRSum += (GyFactor * image[row + row_offset][col + col_offset].rgbtRed);
                        GyGSum += (GyFactor * image[row + row_offset][col + col_offset].rgbtGreen);
                        GyBSum += (GyFactor * image[row + row_offset][col + col_offset].rgbtBlue);
                        
                    }
                }
            }
            int GRValue = fmin(round(sqrt(GxRSum * GxRSum + GyRSum * GyRSum)), 255);
            int GGValue = fmin(round(sqrt(GxGSum * GxGSum + GyGSum * GyGSum)), 255);
            int GBValue = fmin(round(sqrt(GxBSum * GxBSum + GyBSum * GyBSum)), 255);
            new_image[row][col].rgbtRed = GRValue;
            new_image[row][col].rgbtGreen = GGValue;
            new_image[row][col].rgbtBlue = GBValue;
        }
    }
    
    // copy new image to the original image array
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = new_image[row][col];
        }
    }
    return;
}
