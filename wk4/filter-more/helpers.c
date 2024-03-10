#include "helpers.h"
#include <math.h>
#include <stdio.h>

typedef struct
{
    RGBTRIPLE topleft;
    RGBTRIPLE top;
    RGBTRIPLE topright;
    RGBTRIPLE left;
    RGBTRIPLE right;
    RGBTRIPLE bottomleft;
    RGBTRIPLE bottom;
    RGBTRIPLE bottomright;
} NEIGHBOURS;

void add_rgb_values(WORD *red, WORD *green, WORD *blue, int height, int width, RGBTRIPLE image[height][width], int row,
                    int col);
RGBTRIPLE calculate_sopel(NEIGHBOURS neighbouring);

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

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            WORD red = image[i][j].rgbtRed, green = image[i][j].rgbtGreen, blue = image[i][j].rgbtBlue;
            if (i == height - 1)
            {
                // if we are bottom row, far col, add just cols left and up
                if (j == width - 1)
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    divisor = 4;
                }
                // if we are bottom row, first col, add just cols right and up
                else if (j == 0)
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    divisor = 4;
                }
                // if we are bottom row, any other col, add cols left, up, and right
                else
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    divisor = 6;
                }
            }
            else if (i == 0)
            {
                // if we are top row, far col, add just cols left and down
                if (j == width - 1)
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    divisor = 4;
                }
                // if we are top row, first col, add just cols right and down
                else if (j == 0)
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 4;
                }
                // if we are top row, any other col, add cols left, down, and right
                else
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 6;
                }
            }
            else
            {
                // if we are in any of the middle rows
                // if we are far col, add just cols up, left and down
                if (j == width - 1)
                {
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j - 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    divisor = 6;
                }
                else if (j == 0)
                {
                    // if we are first col, add just cols up, right and down
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i - 1, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i, j + 1);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j);
                    add_rgb_values(&red, &green, &blue, height, width, image, i + 1, j + 1);
                    divisor = 6;
                }
                else
                {
                    // if we are anywhere in the middle of the image, add all neighbouring pixels
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

static const RGBTRIPLE BLACK = {0, 0, 0};

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE modified_image[height][width];

    const int one_less_than_height = height - 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            NEIGHBOURS neighbouring = {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK};

            if (i == 0 && j == 0) // top left corner
            {
                neighbouring.right = image[i][j + 1];
                neighbouring.bottom = image[i + 1][j];
                neighbouring.bottomright = image[i + 1][j + 1];
            }
            else if (i == height - 1 && j == 0) // bottom left corner
            {
                neighbouring.right = image[i][j + 1];
                neighbouring.top = image[i - 1][j];
                neighbouring.topright = image[i - 1][j + 1];
            }
            else if (i == 0 && j == width - 1) // top right corner
            {
                neighbouring.left = image[i][j - 1];
                neighbouring.bottom = image[i + 1][j];
                neighbouring.bottomleft = image[i + 1][j - 1];
            }
            else if (i == height - 1 && j == width - 1) // bottom right corner
            {
                neighbouring.left = image[i][j - 1];
                neighbouring.top = image[i - 1][j];
                neighbouring.topleft = image[i - 1][j - 1];
            }
            else if (i == 0)
            {
                neighbouring.left = image[i][j - 1];
                neighbouring.right = image[i][j + 1];
                neighbouring.bottomleft = image[i + 1][j - 1];
                neighbouring.bottom = image[i + 1][j];
                neighbouring.bottomright = image[i + 1][j + 1];
            }
            else if (i == height - 1)
            {
                neighbouring.topleft = image[i - 1][j - 1];
                neighbouring.top = image[i - 1][j];
                neighbouring.topright = image[i - 1][j + 1];
                neighbouring.left = image[i][j - 1];
                neighbouring.right = image[i][j + 1];
            }
            else if (j == 0)
            {
                neighbouring.top = image[i - 1][j];
                neighbouring.topright = image[i - 1][j + 1];
                neighbouring.right = image[i][j + 1];
                neighbouring.bottom = image[i + 1][j];
                neighbouring.bottomright = image[i + 1][j + 1];
            }
            else if (j == width - 1)
            {
                neighbouring.topleft = image[i - 1][j - 1];
                neighbouring.top = image[i - 1][j];
                neighbouring.left = image[i][j - 1];
                neighbouring.bottomleft = image[i + 1][j - 1];
                neighbouring.bottom = image[i + 1][j];
            }
            else
            {
                neighbouring.topleft = image[i - 1][j - 1];
                neighbouring.top = image[i - 1][j];
                neighbouring.topright = image[i - 1][j + 1];
                neighbouring.left = image[i][j - 1];
                neighbouring.right = image[i][j + 1];
                neighbouring.bottomleft = image[i + 1][j - 1];
                neighbouring.bottom = image[i + 1][j];
                neighbouring.bottomright = image[i + 1][j + 1];
            }
            modified_image[i][j] = calculate_sopel(neighbouring);
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

void add_rgb_values(WORD *red, WORD *green, WORD *blue, int height, int width, RGBTRIPLE image[height][width], int row,
                    int col)
{
    *red += image[row][col].rgbtRed;
    *green += image[row][col].rgbtGreen;
    *blue += image[row][col].rgbtBlue;
}

typedef struct
{
    LONG gx;
    LONG gy;
} SOPELS;

RGBTRIPLE calculate_sopel(NEIGHBOURS neighbouring)
{
    RGBTRIPLE newpixel = BLACK;

    SOPELS tmp = {0, 0};
    double interimvalue = 0;

    tmp.gx = -neighbouring.topleft.rgbtRed + neighbouring.topright.rgbtRed;
    tmp.gx += -2 * neighbouring.left.rgbtRed + 2 * neighbouring.right.rgbtRed;
    tmp.gx += -neighbouring.bottomleft.rgbtRed + neighbouring.bottomright.rgbtRed;
    tmp.gy = -neighbouring.topleft.rgbtRed + neighbouring.bottomright.rgbtRed;
    tmp.gy += -2 * neighbouring.top.rgbtRed + 2 * neighbouring.bottom.rgbtRed;
    tmp.gy += -neighbouring.topright.rgbtRed + neighbouring.bottomright.rgbtRed;
    /* newpixel.rgbtRed = round(fmin(sqrt(tmp.gx ^ 2 + tmp.gy ^ 2), 255)); */
    interimvalue = tmp.gx ^ 2;
    interimvalue += tmp.gy ^ 2;
    interimvalue = sqrt(interimvalue);
    interimvalue = fmin(interimvalue, 255);
    newpixel.rgbtRed = round(interimvalue);

    tmp.gx = -neighbouring.topleft.rgbtGreen + neighbouring.topright.rgbtGreen;
    tmp.gx += -2 * neighbouring.left.rgbtGreen + 2 * neighbouring.right.rgbtGreen;
    tmp.gx += -neighbouring.bottomleft.rgbtGreen + neighbouring.bottomright.rgbtGreen;
    tmp.gy = -neighbouring.topleft.rgbtGreen + neighbouring.bottomright.rgbtGreen;
    tmp.gy += -2 * neighbouring.top.rgbtGreen + 2 * neighbouring.bottom.rgbtGreen;
    tmp.gy += -neighbouring.topright.rgbtGreen + neighbouring.bottomright.rgbtGreen;
    /* newpixel.rgbtGreen = round(fmin(sqrt(tmp.gx ^ 2 + tmp.gy ^ 2), 255)); */
    interimvalue = tmp.gx ^ 2;
    interimvalue += tmp.gy ^ 2;
    interimvalue = sqrt(interimvalue);
    interimvalue = fmin(interimvalue, 255);
    newpixel.rgbtGreen = round(interimvalue);

    tmp.gx = -neighbouring.topleft.rgbtBlue + neighbouring.topright.rgbtBlue;
    tmp.gx += -2 * neighbouring.left.rgbtBlue + 2 * neighbouring.right.rgbtBlue;
    tmp.gx += -neighbouring.bottomleft.rgbtBlue + neighbouring.bottomright.rgbtBlue;
    tmp.gy = -neighbouring.topleft.rgbtBlue + neighbouring.bottomright.rgbtBlue;
    tmp.gy += -2 * neighbouring.top.rgbtBlue + 2 * neighbouring.bottom.rgbtBlue;
    tmp.gy += -neighbouring.topright.rgbtBlue + neighbouring.bottomright.rgbtBlue;
    /* newpixel.rgbtBlue = round(fmin(sqrt(tmp.gx ^ 2 + tmp.gy ^ 2), 255)); */
    interimvalue = tmp.gx ^ 2;
    interimvalue += tmp.gy ^ 2;
    interimvalue = sqrt(interimvalue);
    interimvalue = fmin(interimvalue, 255);
    newpixel.rgbtBlue = round(interimvalue);

    return newpixel;
}

/* void test_sopel(void) */
/* { */
/*     NEIGHBOURS neighbouring = {{0, 10, 25},  {0, 10, 30},  {40, 60, 80}, {20, 30, 90}, */
/*                                {80, 70, 90}, {20, 20, 40}, {30, 10, 30}, {50, 40, 10}}; */
/*     RGBTRIPLE test = calculate_sopel(neighbouring); */
/*     printf("RGB is %i, %i, %i\n", test.rgbtRed, test.rgbtGreen, test.rgbtBlue); */
/* } */
