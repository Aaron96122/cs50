#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Here we write a funtion to get the right values of sepia
int get_value(float n)
{

    int value = round(n);
    if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float value;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            value =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                       .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                         .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                        .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = get_value(sepiaRed);
            image[i][j].rgbtGreen = get_value(sepiaGreen);
            image[i][j].rgbtBlue = get_value(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int upp_left, upp_right, low_left, low_right;
    int whole_red, whole_green, whole_blue;
    float count;
    for (int i = 0; i < height; i++)
    {
        if (i - 1 <= 0)
        {
            upp_left = 0;
        }
        else
        {
            upp_left = i - 1;
        }
        if (i + 1 >= height)
        {
            low_left = height - 1;
        }
        else
        {
            low_left = i + 1;
        }
        for (int j = 0; j < width; j++)
        {
            if (j - 1 <= 0)
            {
                upp_right = 0;
            }
            else
            {
                upp_right = j - 1;
            }
            if (j + 1 >= width)
            {
                low_right = width - 1;
            }
            else
            {
                low_right = j + 1;
            }

            count = 0.0;
            whole_red = 0;
            whole_blue = 0;
            whole_green = 0;
            for (int m = upp_left; m <= low_left; m++)
            {
                for (int n = upp_right; n <= low_right; n++)
                {
                    whole_red += image[m][n].rgbtRed;
                    whole_green += image[m][n].rgbtGreen;
                    whole_blue += image[m][n].rgbtBlue;
                    count++;
                }
            }
            copy[i][j].rgbtRed = round(whole_red / count);
            copy[i][j].rgbtGreen = round(whole_green / count);
            copy[i][j].rgbtBlue = round(whole_blue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
