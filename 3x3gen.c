#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    char *outfile = argv[1];

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (!outptr) {
        fprintf(stderr, "Could not create %s: %m.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf = {
        .bfType = 0x4d42,
        .bfOffBits = 54,
    };

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi = {
        .biSize = 40,
        .biBitCount = 24,
        .biCompression = 0,
        .biWidth = 3,
        .biHeight = 3,
    };

    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // first row: (0, 10, 25), (0, 10, 30), (40, 60, 80)
    // second row: (20, 30, 90), (30, 40, 100), (80, 70, 90)
    // third row: (20, 20, 40), (30, 10, 30), (50, 40, 10)
    uint8_t src[3][3][3] = {
        { //   b,  g,  r
            {  0, 10, 25 },
            {  0, 10, 30 },
            { 40, 60, 80 },
        },
        {
            {  20, 30, 90 },
            {  30, 40, 100 },
            {  80, 70, 90 },
        },
        {
            {  20, 20, 40 },
            {  30, 10, 30 },
            {  50, 40, 10 },
        },
    };

    RGBTRIPLE image[3][3];
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            image[x][y].rgbtBlue = src[x][y][0];
            image[x][y].rgbtGreen = src[x][y][1];
            image[x][y].rgbtRed = src[x][y][2];
        }
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Close outfile
    fclose(outptr);

    return 0;
}
