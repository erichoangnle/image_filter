#include "helpers.h"
#include <stdint.h>
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over height
    for (int i = 0; i < height; i++)
    {
        // Loop over width
        for (int j = 0; j < width; j++)
        {
            double a = image[i][j]. rgbtBlue;
            double s = image[i][j].rgbtGreen;
            double d = image[i][j].rgbtRed;
            int average = round((a + s + d) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Lopp over height
    for (int i = 0; i < height; i++)
    {
        // Lopp over width
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia values
            int sepiaRed = (int)round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int)round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int)round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Check if value greater than 255
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

            // Assign new value to pixels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over height
    for (int i = 0; i < height; i++)
    {
        // Loop over length
        for (int j = 0; j < width / 2; j++)
        {
            int temp[3];
            // Assign temp value from image[j]
            temp[0] = image[i][j].rgbtRed;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtBlue;

            // Copy to image[j]
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            // Copy to image[length - j -1]
            image[i][width - j - 1].rgbtRed = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtBlue = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy picture
    RGBTRIPLE copy[height][width];
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            copy[k][l] = image[k][l];
        }
    }

    // Loop over height
    for (int i = 0; i < height; i++)
    {
        // Loop over length
        for (int j = 0; j < width; j++)
        {
            // top line
            if (i == 0)
            {
                if (j == 0) // top left coner
                {
                    image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed
                                                 + copy[i + 1][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen
                                                   + copy[i + 1][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue
                                                  + copy[i + 1][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == width - 1) // top right corner
                {
                    image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed
                                                 + copy[i + 1][j].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen
                                                   + copy[i + 1][j].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue
                                                  + copy[i + 1][j].rgbtBlue) / 4.0);
                }
                else // middle
                {
                    image[i][j].rgbtRed = round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed
                                                 + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen
                                                   + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue
                                                  + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                }
            }
            // bottom line
            else if (i == height - 1)
            {
                if (j == 0) // bottom left corner
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed
                                                 + copy[i][j + 1].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen
                                                   + copy[i][j + 1].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue
                                                  + copy[i][j + 1].rgbtBlue) / 4.0);
                }
                else if (j == width - 1) // bottom right corner
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed
                                                 + copy[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen
                                                   + copy[i][j].rgbtGreen) / 4.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue
                                                  + copy[i][j].rgbtBlue) / 4.0);
                }
                else // middle
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                                 + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                                   + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                                  + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) / 6.0);
                }
            }
            // middle lines
            else
            {
                if (j == 0) // left edge
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j].rgbtRed
                                                 + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j].rgbtGreen
                                                   + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j].rgbtBlue
                                                  + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                }
                else if (j == width - 1) // rigtht edge
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed
                                                 + copy[i][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) / 6.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen
                                                   + copy[i][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) / 6.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue
                                                  + copy[i][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) / 6.0);
                }
                else //middle pixel
                {
                    image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed
                                                 + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed
                                                 + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 9.0);
                    image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen
                                                   + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen
                                                   + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 9.0);
                    image[i][j].rgbtBlue = round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue
                                                  + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue
                                                  + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 9.0);
                }
            }
        }
    }

    return;
}
