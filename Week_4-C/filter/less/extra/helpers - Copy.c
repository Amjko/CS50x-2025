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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //* Sliding Window Technique - Modified by Amiko
    /*  As the kernel, a.k.a. sliding window, moves horizontally, leaving
        values will be subtracted, and the entering values will be
        in the sum of values (if there are any entering values).

        The sum will be reset for every kernel movement vertically, and the
        sum will be used to calculate the blurred equivalent value of the
        current pixel index [height][width].
    */

    for (int h = 0; h < height; h++)
    {
        /*  Initialize sum to be an array of 3, each containing RGB values.
            The 3 elements are equivalent to 3 rows per 3x3 kernel.
        */
        RGBTRIPLE sum[3];
        for (int i = 0; i < 3; i++)
        {
            sum[i].rgbtRed = 0;
            sum[i].rgbtGreen = 0;
            sum[i].rgbtBlue = 0;
        }

        for (int w = 0; w < width; w++)
        {
            //* Fill array with the first pixels in kernel
            if (w == 0)
            {
                // Kernel loop for neighboring pixels of current pixel
                for (int h_kernel = -1; h_kernel <= 1; h_kernel++)
                {
                    for (int w_kernel = -1; w_kernel <= 1; w_kernel++)
                    {
                        // Variables for neighboring pixels' coordinates
                        int h_coord = h + h_kernel;
                        int w_coord = w + w_kernel;

                        // If coords are in bounds, add the value to sum
                        bool in_bound = (h_coord >= 0 && h_coord < height && w_coord >= 0 && w_coord < width) ? true : false;

                        // If coords are out of bounds, move to next pixel
                        if (!in_bound)
                        {
                            continue;
                        }

                        // Accumulate sums of each color
                        sum[h_kernel + 1].rgbtRed += image[h_coord][w_coord].rgbtRed;
                        sum[h_kernel + 1].rgbtGreen += image[h_coord][w_coord].rgbtGreen;
                        sum[h_kernel + 1].rgbtBlue += image[h_coord][w_coord].rgbtBlue;
                    }
                }
            }

            //* Subtract the leaving values, and Add the entering values
            else
            {

                // Variables 1 pixel out of to 3x3 kernel in left/right
                int left_x = w - 2;
                int right_x = w + 2;

                // Check if in bounds
                bool left_in_bounds = (left_x >= 0) ? true : false;
                bool right_in_bounds = (right_x < width) ? true : false;

                // For every row in kernel
                for (int h_kernel = -1; h_kernel <= 1; h_kernel++)
                {
                    // Variables for left coords (leaving values from 3x3)
                    int y = h + h_kernel;

                    if (y < 0 || y >= height)
                    {
                        continue;
                    }

                    // Subtract leaving values
                    if (left_in_bounds)
                    {
                        sum[h_kernel + 1].rgbtRed -= image[y][left_x].rgbtRed;
                        sum[h_kernel + 1].rgbtGreen -= image[y][left_x].rgbtGreen;
                        sum[h_kernel + 1].rgbtBlue -= image[y][left_x].rgbtBlue;
                    }

                    // Add entering values
                    if (right_in_bounds)
                    {
                        sum[h_kernel + 1].rgbtRed += image[y][right_x].rgbtRed;
                        sum[h_kernel + 1].rgbtGreen += image[y][right_x].rgbtGreen;
                        sum[h_kernel + 1].rgbtBlue += image[y][right_x].rgbtBlue;
                    }
                }
            }

            //* Calculate blurred value for current pixel
            // Compute amount of valid pixels in kernel
            int h1 = h - 1;
            int h2 = h + 1;
            int w1 = w - 1;
            int w2 = w + 1;

            // "h2 - h1"
            float pixels = (h2 - h1 + 1) * (w2 - w1 + 1);

            // Compute average of each color
            int avg_rgbtRed = (int)roundf((sum[0].rgbtRed + sum[1].rgbtRed + sum[2].rgbtRed) / pixels);
            int avg_rgbtGreen = (int)roundf((sum[0].rgbtGreen + sum[1].rgbtGreen + sum[2].rgbtGreen) / pixels);
            int avg_rgbtBlue = (int)roundf((sum[0].rgbtBlue + sum[1].rgbtBlue + sum[2].rgbtBlue) / pixels);

            // Assign average to current pixel
            image[h][w].rgbtRed = avg_rgbtRed;
            image[h][w].rgbtGreen = avg_rgbtGreen;
            image[h][w].rgbtBlue = avg_rgbtBlue;
        }
    }

    return;
}
