#include <stdlib.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    double gx_grid[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    double gy_grid[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    RGBTRIPLE oldimage[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            oldimage[x][y] = image[x][y];
        }
    }
    double gxr = 0;
    double gyr = 0;

    double gxg = 0;
    double gyg = 0;

    double gxb = 0;
    double gyb = 0;
    // For every pixel,
    for (int pixel_x = 0; pixel_x < height; pixel_x++)
    {
        for (int pixel_y = 0; pixel_y < width; pixel_y++)
        {
            // apply the Sobel operator to all three colors.
            // Loop through the gx_grid to get our final gx.
            // From -1 to 1 (inclusive), then use addition to find where relatively to the current pixel that pixel is. MAKING SURE NOT TO LOOK AT GARBAGE DATA
            gxr = 0;
            gyr = 0;

            gxg = 0;
            gyg = 0;

            gxb = 0;
            gyb = 0;
            for (int gx_x = -1; gx_x < 2; gx_x++)
            {
                for (int gx_y = -1; gx_y < 2; gx_y++)
                {
                    if (!((pixel_x + gx_x < 0 || pixel_x + gx_x >= width) || (pixel_y + gx_y < 0 || pixel_y + gx_y >= width)))
                    {
                        gxr += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtRed * gx_grid[gx_x + 1][gx_y + 1];
                        gyr += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtRed * gy_grid[gx_x + 1][gx_y + 1];

                        gxg += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtGreen * gx_grid[gx_x + 1][gx_y + 1];
                        gyg += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtGreen * gy_grid[gx_x + 1][gx_y + 1];

                        gxb += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtBlue * gx_grid[gx_x + 1][gx_y + 1];
                        gyb += oldimage[pixel_x + gx_x][pixel_y + gx_y].rgbtBlue * gy_grid[gx_x + 1][gx_y + 1];
                    }
                }
            }
            BYTE redTotal = round(sqrt(gxr * gxr + gyr * gyr));
            image[pixel_x][pixel_y].rgbtRed = redTotal;

            BYTE greenTotal = round(sqrt(gxg * gxg + gyg * gyg));
            image[pixel_x][pixel_y].rgbtGreen = greenTotal;

            BYTE blueTotal = round(sqrt(gxb * gxb + gyb * gyb));
            image[pixel_x][pixel_y].rgbtBlue = blueTotal;
        }
    }
    return;
}
