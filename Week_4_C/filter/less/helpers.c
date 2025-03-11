#include "helpers.h"
#include <math.h>
#include <stdbool.h>

//* Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Compute the average of current pixel's color values
            int average = (int) roundf(
                (image[h][w].rgbtRed + 
                image[h][w].rgbtGreen + 
                image[h][w].rgbtBlue) / 3.0);

            //! Clamp average value in 0 to 255
            average = (average > 255) ? 255 : average;

            // Assign average to current pixel's color values
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }

    return;
}

//* Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //* Set each pixel's value to calculated sepia values
    /*  red = (.393 * orig_red) + (.769 * orig_green) + (.189 * orig_blue)
        green = (.349 * orig_red) + (.686 * orig_green) + (.168 * orig_blue)
        blue = (.272 * orig_red) + (.534 * orig_green) + (.131 * orig_blue)
    */

    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Compute sepia values of each color
            int rgbtRed = (int) roundf(
                (.393 * image[h][w].rgbtRed) +
                (.769 * image[h][w].rgbtGreen) +
                (.189 * image[h][w].rgbtBlue)); 

            int rgbtGreen = (int) roundf(
                (.349 * image[h][w].rgbtRed) +
                (.686 * image[h][w].rgbtGreen) +
                (.168 * image[h][w].rgbtBlue)); 

            int rgbtBlue = (int) roundf(
                (.272 * image[h][w].rgbtRed) +
                (.534 * image[h][w].rgbtGreen) +
                (.131 * image[h][w].rgbtBlue));
            
            //! Clamp sepia values to 255
            rgbtRed = (rgbtRed > 255) ? 255 : rgbtRed;
            rgbtGreen = (rgbtGreen > 255) ? 255 : rgbtGreen;
            rgbtBlue = (rgbtBlue > 255) ? 255 : rgbtBlue;
            
            //! Clamp sepia values to 0
            rgbtRed = (rgbtRed < 0) ? 0 : rgbtRed;
            rgbtGreen = (rgbtGreen < 0) ? 0 : rgbtGreen;
            rgbtBlue = (rgbtBlue < 0) ? 0 : rgbtBlue;

            // Assign sepia values to current pixel's color values
            image[h][w].rgbtRed = rgbtRed;
            image[h][w].rgbtGreen = rgbtGreen;
            image[h][w].rgbtBlue = rgbtBlue;
        }
    }

    return;
}

//* Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Get middle length of width
    int middle = width / 2;

    // For each row, for each column (only up to middle)
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < middle; w++)
        {
            // Buffer for storing left pixel's values
            RGBTRIPLE buffer = image[h][w];

            // Assign right pixel's values to left pixel
            image[h][w] = image[h][width - w - 1];

            // Assign buffer to right pixel
            image[h][width - w - 1] = buffer;
        }
    }

    return;
}

// Integral Image Structure
typedef struct 
{
    int rgbtRed;
    int rgbtGreen;
    int rgbtBlue;
} RGBINT;

//* Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // TODO
    // Initialize 2d array for integral image
    RGBINT II[height][width];

    // For each column, for each row
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //* Compute the integral image array
            // Initialize integral image array
            II[h][w].rgbtRed = image[h][w].rgbtRed;
            II[h][w].rgbtGreen = image[h][w].rgbtGreen;
            II[h][w].rgbtBlue = image[h][w].rgbtBlue;

            // Add the image value from the pixel above
            if (h > 0)
            {
                II[h][w].rgbtRed += II[h - 1][w].rgbtRed;
                II[h][w].rgbtGreen += II[h - 1][w].rgbtGreen;
                II[h][w].rgbtBlue += II[h - 1][w].rgbtBlue;
            }

            // Add the image value from the pixel to the left
            if (w > 0)
            {
                II[h][w].rgbtRed += II[h][w - 1].rgbtRed;
                II[h][w].rgbtGreen += II[h][w - 1].rgbtGreen;
                II[h][w].rgbtBlue += II[h][w - 1].rgbtBlue;
            }

            // Subtract the image value from pixel above and left
            /*  The pixel from above and left is subtracted for it
                was added twice from the two if statements.
            */
            if (h > 0 && w > 0)    
            {
                II[h][w].rgbtRed -= II[h - 1][w - 1].rgbtRed;
                II[h][w].rgbtGreen -= II[h - 1][w - 1].rgbtGreen;
                II[h][w].rgbtBlue -= II[h - 1][w - 1].rgbtBlue;
            }
        }
    }

    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //! Variables for clamping out of bound elements later
            /* h_top variable will be used for accessing top elements */
            int h_top = h - 1;
            
            /* h_bot variable will be used for accessing bottom elements */
            int h_bot = h + 1;

            /* w_left variable will be used for accessing left elements */
            int w_left = w - 1;

            /* w_right variable will be used for accessing right elements */
            int w_right = w + 1;

            //! Clamp variables from accessing past the bound
            if (h_top < 0)
            {
                h_top = 0;
            }
            if (h_bot >= height)
            {
                h_bot = height - 1;
            }
            if (w_left < 0)
            {
                w_left = 0;
            }
            if (w_right >= width)
            {
                w_right = width - 1;
            }
            
            // Variables of the four corners of the 3x3 kernel
            //! Check cases are for preventing in accessing out of bound elements
            RGBINT bot_right = II[h_bot][w_right];
            
            RGBINT bot_left = (w_left > 0) ? 
                II[h_bot][w_left - 1] : (RGBINT) {0, 0, 0};

            RGBINT top_right = (h_top > 0) ? 
                II[h_top - 1][w_right] : (RGBINT) {0, 0, 0};

            RGBINT top_left = (h_top > 0 && w_left > 0) ? 
                II[h_top - 1][w_left - 1] : (RGBINT) {0, 0, 0};


            // Formula to calculate the sum of a 3x3 kernel using integral image
            /*  sum = II[bot][right] + II[top][left] - II[top][right] - II[bot][left] 

                NOTE: II[top][left] is added because the subtraction of
                II[top][right] and II[bot][left] will subtract the
                integral image value of II[top][left] twice. By adding
                II[top][left] again will return the unwanted lost value.
            */

            // Compute the sum of 3x3 kernel
            RGBINT sum;
            sum.rgbtRed = bot_right.rgbtRed + top_left.rgbtRed -
                top_right.rgbtRed - bot_left.rgbtRed;

            sum.rgbtGreen = bot_right.rgbtGreen + top_left.rgbtGreen -
                top_right.rgbtGreen - bot_left.rgbtGreen;

            sum.rgbtBlue = bot_right.rgbtBlue + top_left.rgbtBlue -
                top_right.rgbtBlue - bot_left.rgbtBlue;

            // Compute the number of valid pixels within kernel
            /*  (h_bot - h_top + 1) gets the range of pixels between top and bottom
                (w_right - w_left + 1) gets the range of pixels between left and right
            */
            int valid_pixels = (h_bot - h_top + 1) * (w_right - w_left + 1);

            // Compute the average of each pixel
            RGBINT average;
            average.rgbtRed = (int) roundf((float) sum.rgbtRed / valid_pixels);
            average.rgbtGreen = (int) roundf((float) sum.rgbtGreen / valid_pixels);
            average.rgbtBlue = (int) roundf((float) sum.rgbtBlue / valid_pixels);

            //! Clamp new average values to 255
            average.rgbtRed = (average.rgbtRed > 255) ? 255 : average.rgbtRed;
            average.rgbtGreen = (average.rgbtGreen > 255) ? 255 : average.rgbtGreen;
            average.rgbtBlue = (average.rgbtBlue > 255) ? 255 : average.rgbtBlue;

            //! Clamp new average values to 0
            average.rgbtRed = (average.rgbtRed < 0) ? 0 : average.rgbtRed;
            average.rgbtGreen = (average.rgbtGreen < 0) ? 0 : average.rgbtGreen;
            average.rgbtBlue = (average.rgbtBlue < 0) ? 0 : average.rgbtBlue;

            // Assign new values to current pixel's values
            image[h][w].rgbtRed = average.rgbtRed;
            image[h][w].rgbtGreen = average.rgbtGreen;
            image[h][w].rgbtBlue = average.rgbtBlue;
        }
    }

    return;
}
