#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop for exery single pixel
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // Calculation of the average value for gray scale
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int average = round(sum / 3);
            // Pointer for each color
            BYTE *pb;
            BYTE *pg;
            BYTE *pr;
            pb = &image[i][j].rgbtBlue;
            pg = &image[i][j].rgbtGreen;
            pr = &image[i][j].rgbtRed;
            //Assign an average value to each color
            *pb = average;
            *pg = average;
            *pr = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop for exery single pixel
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // New values for each color
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            //Max value of each new color
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Pointer for each color
            BYTE *pb;
            BYTE *pg;
            BYTE *pr;
            pb = &image[i][j].rgbtBlue;
            pg = &image[i][j].rgbtGreen;
            pr = &image[i][j].rgbtRed;
            //Assign a new color
            *pb = sepiaBlue;
            *pg = sepiaGreen;
            *pr = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all rows image
    for (int i = 0, h = height; i < h; i++)
    {
        // Loop for columns up to half the image width
        for (int j = 0, w = width - 1; j <= w / 2; j++)
        {
            // Pointer for each pixel
            RGBTRIPLE *po;
            RGBTRIPLE *pr;

            po = &image[i][j];
            pr = &image[i][w - j];
            // Temp pixel
            RGBTRIPLE tmp = image[i][j];
            // Swap the pixels
            *po = *pr;
            *pr = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Define temporary arrays - size the same as image
    RGBTRIPLE tmp[height][width];

    // Loop for exery single pixel
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            float sumBlue = 0;
            float sumGreen = 0;
            float sumRed = 0;
            int qtyBlue = 0;
            int qtyGreen = 0;
            int qtyRed = 0;
            // Loop for pixel [i][j] and surrounding pixels
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    // Conditions for pixels at the edges
                    if (k >= 0 && m >= 0 && k < h && m < w)
                    {
                        sumBlue = sumBlue + image[k][m].rgbtBlue;
                        qtyBlue = qtyBlue + 1;
                        sumGreen = sumGreen + image[k][m].rgbtGreen;
                        qtyGreen = qtyGreen + 1;
                        sumRed = sumRed + image[k][m].rgbtRed;
                        qtyRed = qtyRed + 1;
                    }
                }
            }
            int averageBlue = round(sumBlue / qtyBlue);
            int averageGreen = round(sumGreen / qtyGreen);
            int averageRed = round(sumRed / qtyRed);

            BYTE *pb;
            BYTE *pg;
            BYTE *pr;

            pb = &image[i][j].rgbtBlue;
            pg = &image[i][j].rgbtGreen;
            pr = &image[i][j].rgbtRed;

            BYTE *tmpBlue;
            BYTE *tmpGreen;
            BYTE *tmpRed;

            tmpBlue = &tmp[i][j].rgbtBlue;
            tmpGreen = &tmp[i][j].rgbtGreen;
            tmpRed = &tmp[i][j].rgbtRed;
            // temporary arrays, with all new colors
            *tmpBlue = averageBlue;
            *tmpGreen = averageGreen;
            *tmpRed = averageRed;
        }
    }

    // Assigning temporary values to the output image.
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            BYTE *pb;
            BYTE *pg;
            BYTE *pr;

            pb = &image[i][j].rgbtBlue;
            pg = &image[i][j].rgbtGreen;
            pr = &image[i][j].rgbtRed;

            BYTE *tmpBlue;
            BYTE *tmpGreen;
            BYTE *tmpRed;

            tmpBlue = &tmp[i][j].rgbtBlue;
            tmpGreen = &tmp[i][j].rgbtGreen;
            tmpRed = &tmp[i][j].rgbtRed;

            *pb = *tmpBlue;
            *pg = *tmpGreen;
            *pr = *tmpRed;
        }
    }
    return;
}
