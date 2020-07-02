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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Define temporary arrays - size the same as image
    RGBTRIPLE tmpG[height][width];

    // Loop for each pixel
    for (int i = 0, h = height; i < h; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // t - top, m - middle, b - bottom, l - left, r - right
            // Blue surrounding pixels
            int tlB;
            int tmB;
            int trB;
            int mlB;
            int mrB;
            int blB;
            int bmB;
            int brB;
            // Green surrounding pixels
            int tlG;
            int tmG;
            int trG;
            int mlG;
            int mrG;
            int blG;
            int bmG;
            int brG;
            // Red surrounding pixels
            int tlR;
            int tmR;
            int trR;
            int mlR;
            int mrR;
            int blR;
            int bmR;
            int brR;
            //Border pixels exceptions
            if (i == 0)
            {
                // Left-top corner pixel
                if (j == 0)
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = 0;
                    tmB = 0;
                    trB = 0;
                    mlB = 0;
                    mrB = image[i][j + 1].rgbtBlue;
                    blB = 0;
                    bmB = image[i + 1][j].rgbtBlue;
                    brB = image[i + 1][j + 1].rgbtBlue;
                    // Green surrounding pixels value
                    tlG = 0;
                    tmG = 0;
                    trG = 0;
                    mlG = 0;
                    mrG = image[i][j + 1].rgbtGreen;
                    blG = 0;
                    bmG = image[i + 1][j].rgbtGreen;
                    brG = image[i + 1][j + 1].rgbtGreen;
                    // Red surrounding pixels color value
                    tlR = 0;
                    tmR = 0;
                    trR = 0;
                    mlR = 0;
                    mrR = image[i][j + 1].rgbtRed;
                    blR = 0;
                    bmR = image[i + 1][j].rgbtRed;
                    brR = image[i + 1][j + 1].rgbtRed;
                }
                // Right-Top Corner pixel
                else if (j == w - 1)
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = 0;
                    tmB = 0;
                    trB = 0;
                    mlB = image[i][j - 1].rgbtBlue;
                    mrB = 0;
                    blB = image[i + 1][j - 1].rgbtBlue;
                    bmB = image[i + 1][j].rgbtBlue;
                    brB = 0;
                    // Green surrounding pixels value
                    tlG = 0;
                    tmG = 0;
                    trG = 0;
                    mlG = image[i][j - 1].rgbtGreen;
                    mrG = 0;
                    blG = image[i + 1][j - 1].rgbtGreen;
                    bmG = image[i + 1][j].rgbtGreen;
                    brG = 0;
                    // Red surrounding pixels color value
                    tlR = 0;
                    tmR = 0;
                    trR = 0;
                    mlR = image[i][j - 1].rgbtRed;
                    mrR = 0;
                    blR = image[i + 1][j - 1].rgbtRed;
                    bmR = image[i + 1][j].rgbtRed;
                    brR = 0;
                }
                // Top Row pixels
                else
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = 0;
                    tmB = 0;
                    trB = 0;
                    mlB = image[i][j - 1].rgbtBlue;
                    mrB = image[i][j + 1].rgbtBlue;
                    blB = image[i + 1][j - 1].rgbtBlue;
                    bmB = image[i + 1][j].rgbtBlue;
                    brB = image[i + 1][j + 1].rgbtBlue;
                    // Green surrounding pixels value
                    tlG = 0;
                    tmG = 0;
                    trG = 0;
                    mlG = image[i][j - 1].rgbtGreen;
                    mrG = image[i][j + 1].rgbtGreen;
                    blG = image[i + 1][j - 1].rgbtGreen;
                    bmG = image[i + 1][j].rgbtGreen;
                    brG = image[i + 1][j + 1].rgbtGreen;
                    // Red surrounding pixels color value
                    tlR = 0;
                    tmR = 0;
                    trR = 0;
                    mlR = image[i][j - 1].rgbtRed;
                    mrR = image[i][j + 1].rgbtRed;
                    blR = image[i + 1][j - 1].rgbtRed;
                    bmR = image[i + 1][j].rgbtRed;
                    brR = image[i + 1][j + 1].rgbtRed;
                }
            }
            else if (i == h - 1)
            {
                //Bottom-Left Corner pixel
                if (j == 0)
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = 0;
                    tmB = image[i - 1][j].rgbtBlue;
                    trB = image[i - 1][j + 1].rgbtBlue;
                    mlB = 0;
                    mrB = image[i][j + 1].rgbtBlue;
                    blB = 0;
                    bmB = 0;
                    brB = 0;
                    // Green surrounding pixels value
                    tlG = 0;
                    tmG = image[i - 1][j].rgbtGreen;
                    trG = image[i - 1][j + 1].rgbtGreen;
                    mlG = 0;
                    mrG = image[i][j + 1].rgbtGreen;
                    blG = 0;
                    bmG = 0;
                    brG = 0;
                    // Red surrounding pixels color value
                    tlR = 0;
                    tmR = image[i - 1][j].rgbtRed;
                    trR = image[i - 1][j + 1].rgbtRed;
                    mlR = 0;
                    mrR = image[i][j + 1].rgbtRed;
                    blR = 0;
                    bmR = 0;
                    brR = 0;
                }
                //Bottom-Right Corner pixel
                else if (j == w - 1)
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = image[i - 1][j - 1].rgbtBlue;
                    tmB = image[i - 1][j].rgbtBlue;
                    trB = 0;
                    mlB = image[i][j - 1].rgbtBlue;
                    mrB = 0;
                    blB = 0;
                    bmB = 0;
                    brB = 0;
                    // Green surrounding pixels value
                    tlG = image[i - 1][j - 1].rgbtGreen;
                    tmG = image[i - 1][j].rgbtGreen;
                    trG = 0;
                    mlG = image[i][j - 1].rgbtGreen;
                    mrG = 0;
                    blG = 0;
                    bmG = 0;
                    brG = 0;
                    // Red surrounding pixels color value
                    tlR = image[i - 1][j - 1].rgbtRed;
                    tmR = image[i - 1][j].rgbtRed;
                    trR = 0;
                    mlR = image[i][j - 1].rgbtRed;
                    mrR = 0;
                    blR = 0;
                    bmR = 0;
                    brR = 0;
                }
                // Bottom Row pixels
                else
                {
                    // t - top, m - middle, b - bottom, l - left, r - right
                    // Blue surrounding pixels value
                    tlB = image[i - 1][j - 1].rgbtBlue;
                    tmB = image[i - 1][j].rgbtBlue;
                    trB = image[i - 1][j + 1].rgbtBlue;
                    mlB = image[i][j - 1].rgbtBlue;
                    mrB = image[i][j + 1].rgbtBlue;
                    blB = 0;
                    bmB = 0;
                    brB = 0;
                    // Green surrounding pixels value
                    tlG = image[i - 1][j - 1].rgbtGreen;
                    tmG = image[i - 1][j].rgbtGreen;
                    trG = image[i - 1][j + 1].rgbtGreen;
                    mlG = image[i][j - 1].rgbtGreen;
                    mrG = image[i][j + 1].rgbtGreen;
                    blG = 0;
                    bmG = 0;
                    brG = 0;
                    // Red surrounding pixels color value
                    tlR = image[i - 1][j - 1].rgbtRed;
                    tmR = image[i - 1][j].rgbtRed;
                    trR = image[i - 1][j + 1].rgbtRed;
                    mlR = image[i][j - 1].rgbtRed;
                    mrR = image[i][j + 1].rgbtRed;
                    blR = 0;
                    bmR = 0;
                    brR = 0;
                }
            }
            // Left column pixels
            else if (j == 0)
            {
                // t - top, m - middle, b - bottom, l - left, r - right
                // Blue surrounding pixels value
                tlB = 0;
                tmB = image[i - 1][j].rgbtBlue;
                trB = image[i - 1][j + 1].rgbtBlue;
                mlB = 0;
                mrB = image[i][j + 1].rgbtBlue;
                blB = 0;
                bmB = image[i + 1][j].rgbtBlue;
                brB = image[i + 1][j + 1].rgbtBlue;
                // Green surrounding pixels value
                tlG = 0;
                tmG = image[i - 1][j].rgbtGreen;
                trG = image[i - 1][j + 1].rgbtGreen;
                mlG = 0;
                mrG = image[i][j + 1].rgbtGreen;
                blG = 0;
                bmG = image[i + 1][j].rgbtGreen;
                brG = image[i + 1][j + 1].rgbtGreen;
                // Red surrounding pixels color value
                tlR = 0;
                tmR = image[i - 1][j].rgbtRed;
                trR = image[i - 1][j + 1].rgbtRed;
                mlR = 0;
                mrR = image[i][j + 1].rgbtRed;
                blR = 0;
                bmR = image[i + 1][j].rgbtRed;
                brR = image[i + 1][j + 1].rgbtRed;
            }
            // Right column pixels
            else if (j == w - 1)
            {
                // t - top, m - middle, b - bottom, l - left, r - right
                // Blue surrounding pixels value
                tlB = image[i - 1][j - 1].rgbtBlue;
                tmB = image[i - 1][j].rgbtBlue;
                trB = 0;
                mlB = image[i][j - 1].rgbtBlue;
                mrB = 0;
                blB = image[i + 1][j - 1].rgbtBlue;
                bmB = image[i + 1][j].rgbtBlue;
                brB = 0;
                // Green surrounding pixels value
                tlG = image[i - 1][j - 1].rgbtGreen;
                tmG = image[i - 1][j].rgbtGreen;
                trG = 0;
                mlG = image[i][j - 1].rgbtGreen;
                mrG = 0;
                blG = image[i + 1][j - 1].rgbtGreen;
                bmG = image[i + 1][j].rgbtGreen;
                brG = 0;
                // Red surrounding pixels color value
                tlR = image[i - 1][j - 1].rgbtRed;
                tmR = image[i - 1][j].rgbtRed;
                trR = 0;
                mlR = image[i][j - 1].rgbtRed;
                mrR = 0;
                blR = image[i + 1][j - 1].rgbtRed;
                bmR = image[i + 1][j].rgbtRed;
                brR = 0;
            }
            // All middle pixels
            else
            {
                // t - top, m - middle, b - bottom, l - left, r - right
                // Blue surrounding pixels value
                tlB = image[i - 1][j - 1].rgbtBlue;
                tmB = image[i - 1][j].rgbtBlue;
                trB = image[i - 1][j + 1].rgbtBlue;
                mlB = image[i][j - 1].rgbtBlue;
                mrB = image[i][j + 1].rgbtBlue;
                blB = image[i + 1][j - 1].rgbtBlue;
                bmB = image[i + 1][j].rgbtBlue;
                brB = image[i + 1][j + 1].rgbtBlue;
                // Green surrounding pixels value
                tlG = image[i - 1][j - 1].rgbtGreen;
                tmG = image[i - 1][j].rgbtGreen;
                trG = image[i - 1][j + 1].rgbtGreen;
                mlG = image[i][j - 1].rgbtGreen;
                mrG = image[i][j + 1].rgbtGreen;
                blG = image[i + 1][j - 1].rgbtGreen;
                bmG = image[i + 1][j].rgbtGreen;
                brG = image[i + 1][j + 1].rgbtGreen;
                // Red surrounding pixels color value
                tlR = image[i - 1][j - 1].rgbtRed;
                tmR = image[i - 1][j].rgbtRed;
                trR = image[i - 1][j + 1].rgbtRed;
                mlR = image[i][j - 1].rgbtRed;
                mrR = image[i][j + 1].rgbtRed;
                blR = image[i + 1][j - 1].rgbtRed;
                bmR = image[i + 1][j].rgbtRed;
                brR = image[i + 1][j + 1].rgbtRed;
            }

            // Gx and Gy value for color Blue
            int GxBlue = 1 * trB - 1 * tlB + 2 * mrB - 2 * mlB + 1 * brB - 1 * blB;
            int GyBlue = 1 * blB + 2 * bmB + 1 * brB - 1 * tlB - 2 * tmB - 1 * trB;
            // Gx^2 and Gy^2 value for color Blue
            int GxBlue2 = pow(GxBlue, 2);
            int GyBlue2 = pow(GyBlue, 2);
            // No more than
            // New color values sqrt of Gx^2 + Gy^2
            int GBlue;
            if (sqrt((GxBlue2 + GyBlue2)) > 255)
            {
                GBlue = 255;
            }
            else
            {
                GBlue = round(sqrt((GxBlue2 + GyBlue2)));
            }
            // Gx and Gy value for color Green
            int GxGreen = 1 * trG - 1 * tlG + 2 * mrG - 2 * mlG + 1 * brG - 1 * blG;
            int GyGreen = 1 * blG + 2 * bmG + 1 * brG - 1 * tlG - 2 * tmG - 1 * trG;
            // Gx^2 and Gy^2 value for color Green
            int GxGreen2 = pow(GxGreen, 2);
            int GyGreen2 = pow(GyGreen, 2);
            // No more than
            // New color values sqrt of Gx^2 + Gy^2
            int GGreen;
            if (sqrt((GxGreen2 + GyGreen2)) > 255)
            {
                GGreen = 255;
            }
            else
            {
                GGreen = round(sqrt((GxGreen2 + GyGreen2)));
            }
            // Gx and Gy value for color Red
            int GxRed = 1 * trR - 1 * tlR + 2 * mrR - 2 * mlR + 1 * brR - 1 * blR;
            int GyRed = 1 * blR + 2 * bmR + 1 * brR - 1 * tlR - 2 * tmR - 1 * trR;
            // Gx^2 and Gy^2 value for color Red
            int GxRed2 = pow(GxRed, 2);
            int GyRed2 = pow(GyRed, 2);
            // No more than
            // New color values sqrt of Gx^2 + Gy^2
            int GRed;
            if (sqrt((GxRed2 + GyRed2)) > 255)
            {
                GRed = 255;
            }
            else
            {
                GRed = round(sqrt((GxRed2 + GyRed2)));
            }

            BYTE *pb;
            BYTE *pg;
            BYTE *pr;

            pb = &image[i][j].rgbtBlue;
            pg = &image[i][j].rgbtGreen;
            pr = &image[i][j].rgbtRed;

            BYTE *tmpGBlue;
            BYTE *tmpGGreen;
            BYTE *tmpGRed;

            tmpGBlue = &tmpG[i][j].rgbtBlue;
            tmpGGreen = &tmpG[i][j].rgbtGreen;
            tmpGRed = &tmpG[i][j].rgbtRed;

            *tmpGBlue = GBlue;
            *tmpGGreen = GGreen;
            *tmpGRed = GRed;
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

            BYTE *tmpGBlue;
            BYTE *tmpGGreen;
            BYTE *tmpGRed;

            tmpGBlue = &tmpG[i][j].rgbtBlue;
            tmpGGreen = &tmpG[i][j].rgbtGreen;
            tmpGRed = &tmpG[i][j].rgbtRed;

            *pb = *tmpGBlue;
            *pg = *tmpGGreen;
            *pr = *tmpGRed;
        }
    }
    return;
}
