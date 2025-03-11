#include "helpers.h"
#include <math.h>

//* Structure of RGBINT containing rgbtRed, Green, Blue int values
typedef struct
{
    int rgbtRed;
    int rgbtGreen;
    int rgbtBlue;
} RGBINT;

//* Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //* Compute average of all color values
            /*  NOTE: To get average, first get the sum of
                all values, then divide it to the number of
                values. Lastly, round off to nearest int.
            */
            int average = (int) roundf(
                (image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);

            //! Clamp average value withing 0 to 255
            average = (average < 0) ? 0 : (average > 255) ? 255 : average;

            // Assign new average value to current pixel
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }

    return;
}

//* Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Get middle of width
    int middle = width / 2;

    //* Swap pixels' opposite positions
    // For each row, for each column up to middle
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < middle; w++)
        {
            // Buffer for temporarily storing left pixel
            RGBTRIPLE left_pixel = image[h][w];

            // Place right pixel on left pixel's position
            image[h][w] = image[h][width - w - 1];

            // Place left pixel from buffer on right pixel's position
            image[h][width - w - 1] = left_pixel;
        }
    }

    return;
}

//* Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // TODO
    // Initialize an integral image 2d array 
    RGBINT II[height][width];

    //* Fill in with values the integral image
    /*  INTEGRAL IMAGE FORMULA:

        II(h, w) = image(h, w)      # The original pixel value
                 + II(h - 1, w)     # The integral image value from above
                 + II(h, w - 1)     # The integral image value from left
                 - II(h - 1, w - 1) # The integral image value from top left
    */

    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // First operation
            /* Add the original pixel value */
            II[h][w].rgbtRed = image[h][w].rgbtRed;
            II[h][w].rgbtGreen = image[h][w].rgbtGreen;
            II[h][w].rgbtBlue = image[h][w].rgbtBlue;

            // Second operation
            /* Add the integral image value from above */
            if (h > 0)
            {
                II[h][w].rgbtRed += II[h - 1][w].rgbtRed;
                II[h][w].rgbtGreen += II[h - 1][w].rgbtGreen;
                II[h][w].rgbtBlue += II[h - 1][w].rgbtBlue;
            }

            // Third operation
            /* Add the integral image value from left */
            if (w > 0)
            {
                II[h][w].rgbtRed += II[h][w - 1].rgbtRed;
                II[h][w].rgbtGreen += II[h][w - 1].rgbtGreen;
                II[h][w].rgbtBlue += II[h][w - 1].rgbtBlue;
            }

            // Last operation
            /* Subtract the integral image value from top left
                
                Why? : It is because the top and left were added,
                meaning the top left value was added twice.
                Subtracting the top left value once will make it
                once.
            */
            if (h > 0 && w > 0)
            {
                II[h][w].rgbtRed -= II[h - 1][w - 1].rgbtRed;
                II[h][w].rgbtGreen -= II[h - 1][w - 1].rgbtGreen;
                II[h][w].rgbtBlue -= II[h - 1][w - 1].rgbtBlue;
            }
        }
    }

    //* Calculate sum of pixels within 3x3 kernel
    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //! Variables (coordinates) to help prevent accessing out-of-bound elements later
            int top = h - 1;   /* For accessing top pixel */ 
            int bot = h + 1;   /* For accessing bottom pixel */
            int left = w - 1;  /* For accessing left pixel */
            int right = w + 1; /* For accessing right pixel */
            
            //! Clamp coordinates in case position is out of bounds
            if (top < 0)
            {
                top = 0;
            }
            if (bot >= height)
            {
                bot = height - 1;
            }
            if (left < 0)
            {
                left = 0;
            }
            if (right >= width)
            {
                right = width - 1;
            }

            //! Clamp corner pixels in case it tries to access out-of-bound elements
            // Value of bottom right integral image value
            RGBINT bot_right = II[bot][right];

            // Value of bottom left integral image value 
            RGBINT bot_left = (left > 0) ? II[bot][left - 1] : (RGBINT) {0, 0, 0};

            // Value of top right integral image value 
            RGBINT top_right = (top > 0) ? II[top - 1][right] : (RGBINT) {0, 0, 0};

            // Value of top left integral image value 
            RGBINT top_left = (top > 0 && left > 0) ? II[top - 1][left - 1] : (RGBINT) {0, 0, 0};

            // Calculate sum from corner pixels
            RGBINT sum;

            // Sum of red values
            sum.rgbtRed =
                bot_right.rgbtRed + top_left.rgbtRed - bot_left.rgbtRed - top_right.rgbtRed;
            
            // Sum of green values
            sum.rgbtGreen =
                bot_right.rgbtGreen + top_left.rgbtGreen - bot_left.rgbtGreen - top_right.rgbtGreen;

            // Sum of blue values
            sum.rgbtBlue =
                bot_right.rgbtBlue + top_left.rgbtBlue - bot_left.rgbtBlue - top_right.rgbtBlue;
            
            // Compute the number of valid pixels within 3x3 kernel
            float valid_pixels = (bot - top + 1) * (right - left + 1);

            // Calculate the average of each color values
            RGBINT average;
            average.rgbtRed = (int) roundf(sum.rgbtRed / valid_pixels);
            average.rgbtGreen = (int) roundf(sum.rgbtGreen / valid_pixels);
            average.rgbtBlue = (int) roundf(sum.rgbtBlue / valid_pixels);

            //! Clamp values within range of 0 to 255
            average.rgbtRed = (average.rgbtRed < 0)     ? 0
                              : (average.rgbtRed > 255) ? 255
                                                        : average.rgbtRed;
            average.rgbtGreen = (average.rgbtGreen < 0)     ? 0
                                : (average.rgbtGreen > 255) ? 255
                                                            : average.rgbtGreen;
            average.rgbtBlue = (average.rgbtBlue < 0)     ? 0
                               : (average.rgbtBlue > 255) ? 255
                                                          : average.rgbtBlue;

            // Assign average values as new pixel values
            image[h][w].rgbtRed = average.rgbtRed;
            image[h][w].rgbtGreen = average.rgbtGreen;
            image[h][w].rgbtBlue = average.rgbtBlue;
        }
    }

    return;
}

//* Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // TODO
    //* Create a 2nd copy of the image for computing edge detection
    RGBTRIPLE image_copy[height][width];

    // Copy values from image to image_copy
    /*  NOTE: image_copy[][] is for the kernel to iterate over
        and compute the edge detection values. Then, the
        calculated values will change the original values 
        of image[][].

        This is so that the kernel doesn't iterate over
        values that were changed, but rather only the
        original values from image_copy[][].
    */
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image_copy[h][w] = image[h][w];
        }
    }

    //* 2d array of sobel operator values
    // Gx direction
    int gx[3][3] = {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };

    // Gy direction
    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    //* Variables for computing values when sobel operator is applied
    // Variable for storing values of valid pixels
    RGBINT pixel_value;

    // Variable for computing edge detection value
    RGBINT edge_value;

    // Variables for computing Gx and Gy values
    RGBINT gx_value;
    RGBINT gy_value;

    // For each row, for each column
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Reset values to 0
            edge_value = (RGBINT) {0, 0, 0};
            gx_value = (RGBINT) {0, 0, 0};
            gy_value = (RGBINT) {0, 0, 0};

            // For each pixel within 3x3 kernel
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    //! Return 0 as value for out-of-bound positions
                    // Either assign red or 0
                    pixel_value.rgbtRed =
                        (h + y < 0 || w + x < 0 || h + y >= height || w + x >= width) 
                            ? 0 
                            : image_copy[h + y][w + x].rgbtRed;

                    // Either assign green or 0
                    pixel_value.rgbtGreen =
                        (h + y < 0 || w + x < 0 || h + y >= height || w + x >= width) 
                            ? 0 
                            : image_copy[h + y][w + x].rgbtGreen;

                    // Either assign blue or 0
                    pixel_value.rgbtBlue =
                        (h + y < 0 || w + x < 0 || h + y >= height || w + x >= width) 
                            ? 0 
                            : image_copy[h + y][w + x].rgbtBlue;

                    //* Compute for the edge detection values
                    // Multiply original values to Gx values
                    gx_value.rgbtRed += pixel_value.rgbtRed * gx[y + 1][x + 1];
                    gx_value.rgbtGreen += pixel_value.rgbtGreen * gx[y + 1][x + 1];
                    gx_value.rgbtBlue += pixel_value.rgbtBlue * gx[y + 1][x + 1];

                    // Multiply original values to Gy values
                    gy_value.rgbtRed += pixel_value.rgbtRed * gy[y + 1][x + 1];
                    gy_value.rgbtGreen += pixel_value.rgbtGreen * gy[y + 1][x + 1];
                    gy_value.rgbtBlue += pixel_value.rgbtBlue * gy[y + 1][x + 1];
                }
            }

            // Compute the squared values of Gx and Gy directions
            double squared_rgbtRed = sqrt((gx_value.rgbtRed * gx_value.rgbtRed) +
                                          (gy_value.rgbtRed * gy_value.rgbtRed));

            double squared_rgbtGreen = sqrt((gx_value.rgbtGreen * gx_value.rgbtGreen) +
                                            (gy_value.rgbtGreen * gy_value.rgbtGreen));

            double squared_rgbtBlue = sqrt((gx_value.rgbtBlue * gx_value.rgbtBlue) +
                                           (gy_value.rgbtBlue * gy_value.rgbtBlue));
            
            // Round off double values
            edge_value.rgbtRed = (int) round(squared_rgbtRed);
            edge_value.rgbtGreen = (int) round(squared_rgbtGreen);
            edge_value.rgbtBlue = (int) round(squared_rgbtBlue);

            //! Clamp values within range of 0 to 255
            edge_value.rgbtRed = (edge_value.rgbtRed < 0)     ? 0
                                 : (edge_value.rgbtRed > 255) ? 255
                                                              : edge_value.rgbtRed;

            edge_value.rgbtGreen = (edge_value.rgbtGreen < 0)     ? 0
                                   : (edge_value.rgbtGreen > 255) ? 255
                                                                  : edge_value.rgbtGreen;

            edge_value.rgbtBlue = (edge_value.rgbtBlue < 0)     ? 0
                                  : (edge_value.rgbtBlue > 255) ? 255
                                                                : edge_value.rgbtBlue;

            // Assign values to original pixel value
            image[h][w].rgbtRed = edge_value.rgbtRed;
            image[h][w].rgbtGreen = edge_value.rgbtGreen;
            image[h][w].rgbtBlue = edge_value.rgbtBlue;
        }
    }

    return;
}
