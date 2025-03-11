#include <stdbool.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //* Set each pixel's value to average value of pixel's RGB
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Get the average value of all RGB values
            int average_value = (int)roundf((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);

            // Clamp value within color range
            average_value = (average_value > 255) ? 255 : average_value;

            // Set the new value of the pixel to average value
            image[h][w].rgbtRed = average_value;
            image[h][w].rgbtGreen = average_value;
            image[h][w].rgbtBlue = average_value;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //* Set each pixel's value to calculated sepia values
    /*  red = (.393 * orig_red) + (.769 * orig_green) + (.189 * orig_blue)
        green = (.349 * orig_red) + (.686 * orig_green) + (.168 * orig_blue)
        blue = (.272 * orig_red) + (.534 * orig_green) + (.131 * orig_blue)
    */

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Get the calculated sepia value for each color
            int sepia_red = (int)roundf((.393 * image[h][w].rgbtRed) + (.769 * image[h][w].rgbtGreen) + (.189 * image[h][w].rgbtBlue));
            int sepia_green = (int)roundf((.349 * image[h][w].rgbtRed) + (.686 * image[h][w].rgbtGreen) + (.168 * image[h][w].rgbtBlue));
            int sepia_blue = (int)roundf((.272 * image[h][w].rgbtRed) + (.534 * image[h][w].rgbtGreen) + (.131 * image[h][w].rgbtBlue));

            // Clamp each value within color range
            sepia_red = (sepia_red > 255) ? 255 : sepia_red;
            sepia_green = (sepia_green > 255) ? 255 : sepia_green;
            sepia_blue = (sepia_blue > 255) ? 255 : sepia_blue;

            // Set the sepia values to each color
            image[h][w].rgbtRed = sepia_red;
            image[h][w].rgbtGreen = sepia_green;
            image[h][w].rgbtBlue = sepia_blue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //* Swap the values in opposite of position in array
    // Middle index of each row
    int middle = width / 2;

    for (int h = 0; h < height; h++)
    {
        for (int m = 0; m < middle; m++)
        {
            // Variables for temporary storage when swapping values
            RGBTRIPLE temp_value = image[h][m];

            // Swap the values
            image[h][m] = image[h][width - m - 1];
            image[h][width - m - 1] = temp_value;
        }
    }

    return;
}

// Integral Image Structure
typedef struct
{
    uint8_t rgbtRed;
    uint8_t rgbtGreen;
    uint8_t rgbtBlue;
} integral_image;

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a 2d array for containing cumulative sums
    integral_image II[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //* Compute cumulative sum
            // Fill current element with middle pixel's color value
            II[h][w].rgbtRed = image[h][w].rgbtRed;
            II[h][w].rgbtGreen = image[h][w].rgbtGreen;
            II[h][w].rgbtBlue = image[h][w].rgbtBlue;

            // Add top pixel's color value
            if (h > 0)
            {
                II[h][w].rgbtRed += image[h - 1][w].rgbtRed;
                II[h][w].rgbtGreen += image[h - 1][w].rgbtGreen;
                II[h][w].rgbtBlue += image[h - 1][w].rgbtBlue;
            }

            // Add bottom pixel's color value
            if (w > 0)
            {
                II[h][w].rgbtRed += image[h][w - 1].rgbtRed;
                II[h][w].rgbtGreen += image[h][w - 1].rgbtGreen;
                II[h][w].rgbtBlue += image[h][w - 1].rgbtBlue;
            }

            // Subtract top corner pixel's color value
            if (h > 0 && w > 0)
            {
                II[h][w].rgbtRed -= image[h - 1][w - 1].rgbtRed;
                II[h][w].rgbtGreen -= image[h - 1][w - 1].rgbtGreen;
                II[h][w].rgbtBlue -= image[h - 1][w - 1].rgbtBlue;
            }
        }
    }

    return;
}
