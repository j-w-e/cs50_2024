#include "helpers.h"
#include <math.h>

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

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            modified_image[i][j] = image[i][width - j -1];
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = modified_image[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE modified_image[height][width];

    int upper_row = 0, lower_row = 0, left_col = 0, right_col = 0;

    // FIXME this is too dark. I probably need to calculate as a WORD, then convert to a BYTE
    for (int i = 0; i < height; i++)
    {
        if (i == 0)
        {
            upper_row = -1;
            lower_row = 1;
        }
        else if (i == height - 1)
        {
            upper_row = height - 2;
            lower_row = -1;
        }
        else
        {
            upper_row = i - 1;
            lower_row = i + 1;
        }

        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                left_col = -1;
                right_col = 1;
            }
            else if (j == height - 1)
            {
                left_col = height - 2;
                right_col = -1;
            }
            else
            {
                left_col = j - 1;
                right_col = j + 1;
            }


            modified_image[i][j].rgbtRed = image[i][j].rgbtRed;
            modified_image[i][j].rgbtGreen = image[i][j].rgbtGreen;
            modified_image[i][j].rgbtBlue = image[i][j].rgbtBlue;
            if (upper_row != -1) {
                if (left_col != -1) {
                    modified_image[i][j].rgbtRed += image[upper_row][left_col].rgbtRed;
                    modified_image[i][j].rgbtGreen += image[upper_row][left_col].rgbtGreen;
                    modified_image[i][j].rgbtBlue += image[upper_row][left_col].rgbtBlue;
                }
                if (right_col != -1) {
                    modified_image[i][j].rgbtRed += image[upper_row][right_col].rgbtRed;
                    modified_image[i][j].rgbtGreen += image[upper_row][right_col].rgbtGreen;
                    modified_image[i][j].rgbtBlue += image[upper_row][right_col].rgbtBlue;
                }
                modified_image[i][j].rgbtRed += image[upper_row][j].rgbtRed;
                modified_image[i][j].rgbtGreen += image[upper_row][j].rgbtGreen;
                modified_image[i][j].rgbtBlue += image[upper_row][j].rgbtBlue;
            }

            if (lower_row != -1) {
                if (left_col != -1) {
                    modified_image[i][j].rgbtRed += image[lower_row][left_col].rgbtRed;
                    modified_image[i][j].rgbtGreen += image[lower_row][left_col].rgbtGreen;
                    modified_image[i][j].rgbtBlue += image[lower_row][left_col].rgbtBlue;
                }
                if (right_col != -1) {
                    modified_image[i][j].rgbtRed += image[lower_row][right_col].rgbtRed;
                    modified_image[i][j].rgbtGreen += image[lower_row][right_col].rgbtGreen;
                    modified_image[i][j].rgbtBlue += image[lower_row][right_col].rgbtBlue;
                }
                modified_image[i][j].rgbtRed += image[lower_row][j].rgbtRed;
                modified_image[i][j].rgbtGreen += image[lower_row][j].rgbtGreen;
                modified_image[i][j].rgbtBlue += image[lower_row][j].rgbtBlue;
            }
            if(left_col != -1){
                modified_image[i][j].rgbtRed += image[i][left_col].rgbtRed;
                modified_image[i][j].rgbtGreen += image[i][left_col].rgbtGreen;
                modified_image[i][j].rgbtBlue += image[i][left_col].rgbtBlue;
            }
            if(right_col != -1){
                modified_image[i][j].rgbtRed += image[i][right_col].rgbtRed;
                modified_image[i][j].rgbtGreen += image[i][right_col].rgbtGreen;
                modified_image[i][j].rgbtBlue += image[i][right_col].rgbtBlue;
            }

            float divisor = 0;
            if (right_col == -1 || left_col == -1) {
                if (upper_row == -1 || lower_row == -1){
                    divisor = 4;
                } else {
                    divisor = 6;
                }
            } else if (upper_row == -1 || lower_row == -1) {
                divisor = 6;
            } else
                divisor = 9;
            modified_image[i][j].rgbtRed = round(modified_image[i][j].rgbtRed / divisor);
            modified_image[i][j].rgbtGreen = round(modified_image[i][j].rgbtGreen / divisor);
            modified_image[i][j].rgbtBlue = round(modified_image[i][j].rgbtBlue / divisor);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = modified_image[i][j];
        }
    }

    return;
}
