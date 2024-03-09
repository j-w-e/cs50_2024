#include "helpers.h"
#include <math.h>

void add_rgb_values(WORD *red, WORD *green, WORD *blue, int height, int width, RGBTRIPLE image[height][width], int row, int col);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE mean = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
            image[i][j].rgbtBlue = mean;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE modified_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            modified_image[i][j] = image[i][width - j - 1];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = modified_image[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE modified_image[height][width];

    float divisor = 0;

    // FIXME this is too dark. I probably need to calculate as a WORD, then convert to a BYTE
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            WORD red = image[i][j].rgbtRed, green = image[i][j].rgbtGreen, blue = image[i][j].rgbtBlue;
            if (i == height - 1) {
                // if we are bottom row, far col, add just cols left and up
                if (j == width - 1) {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    divisor = 4;
                }
                // if we are bottom row, first col, add just cols right and up
                else if (j == 0) {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    divisor = 4;
                }
                // if we are bottom row, any other col, add cols left, up, and right
                else {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    divisor = 6;
                }
            }
             else if (i == 0) {
                // if we are top row, far col, add just cols left and down
                if (j == width - 1) {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    divisor = 4;
                }
                // if we are top row, first col, add just cols right and down
                else if (j == 0) {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 4;
                }
                // if we are top row, any other col, add cols left, down, and right
                else {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 6;
                }
            } else {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 9;
            }
            modified_image[i][j].rgbtRed = red / divisor > 255 ? 255 : round(red / divisor);
            modified_image[i][j].rgbtGreen = green / divisor > 255 ? 255 : round(green / divisor);
            modified_image[i][j].rgbtBlue = blue / divisor > 255 ? 255 : round(blue / divisor);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = modified_image[i][j];
        }
    }

    return;
}

void add_rgb_values(WORD *red, WORD *green, WORD *blue, int height, int width, RGBTRIPLE image[height][width], int row, int col) {
    *red += image[row][col].rgbtRed;
    *green += image[row][col].rgbtGreen;
    *blue += image[row][col].rgbtBlue;
}
