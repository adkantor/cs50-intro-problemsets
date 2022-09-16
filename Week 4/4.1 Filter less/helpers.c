#include <math.h>

#include "helpers.h"

BYTE get_RGB_average(BYTE r, BYTE g, BYTE b);
RGBTRIPLE get_RGB_sepia(RGBTRIPLE pixelCurrent);
void copy_image(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width]);
RGBTRIPLE get_box_blur(int n, RGBTRIPLE box[n]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate individual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate average of RGB
            BYTE new_col = get_RGB_average(image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            // apply new color to pixel
            image[i][j].rgbtRed = new_col;
            image[i][j].rgbtGreen = new_col;
            image[i][j].rgbtBlue = new_col;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate individual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate sepia RGB
            RGBTRIPLE pixel_current = image[i][j];
            RGBTRIPLE pixel_new = get_RGB_sepia(pixel_current);

            // change pixel to new
            image[i][j] = pixel_new;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate rows
    for (int i = 0; i < height; i++)
    {
        // iterate pixels from left to right
        for (int j = 0; j < width; j++)
        {
            // get position of the mirrored pixel
            int k = width - 1 - j;
            if (j < k)
            {
                // swap pixels j and k
                RGBTRIPLE pixel_left = image[i][j];
                RGBTRIPLE pixel_right = image[i][k];
                image[i][j] = pixel_right;
                image[i][k] = pixel_left;
            }
            else
            {
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image
    RGBTRIPLE img_copy[height][width];
    copy_image(height, width, image, img_copy);

    // iterate individual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get box
            int box_height = (i == 0 || i == height - 1) ? 2 : 3;
            int box_width = (j == 0 || j == width - 1) ? 2 : 3;
            RGBTRIPLE box[box_height * box_width]; // flattened
            int box_ndx = 0;
            for (int img_r = i - 1; img_r <= i + 1; img_r++)
            {
                if (img_r >= 0 && img_r <= height - 1)
                {
                    for (int img_c = j - 1; img_c <= j + 1; img_c++)
                    {
                        if (img_c >= 0 && img_c <= width - 1)
                        {
                            box[box_ndx] = img_copy[img_r][img_c];
                            box_ndx++;
                        }
                    }
                }
            }

            // calculate pixel color
            RGBTRIPLE pixel_new = get_box_blur(box_height * box_width, box);

            // change pixel to new
            image[i][j] = pixel_new;
        }
    }

    return;
}

// Calculates average of R, G, B channel intensities.
// @param r     red channel intensity (0-255)
// @param g     green channel intensity (0-255)
// @param b     blue channel intensity (0-255)
// @return      average intensity (0-255)
BYTE get_RGB_average(BYTE r, BYTE g, BYTE b)
{
    double temp = ((double) r + (double) g + (double) b) / 3;
    return round(temp);
}

/**
 * sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
 * sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
 * sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
**/
RGBTRIPLE get_RGB_sepia(RGBTRIPLE pixelCurrent)
{
    BYTE originalRed = pixelCurrent.rgbtRed;
    BYTE originalGreen = pixelCurrent.rgbtGreen;
    BYTE originalBlue = pixelCurrent.rgbtBlue;
    // calculate raw values
    double sepiaRedDbl = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
    double sepiaGreenDbl = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
    double sepiaBlueDbl = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
    // round and ensure intensity is between 0-255
    BYTE sepiaRed = round(fmin(sepiaRedDbl, 255));
    BYTE sepiaGreen = round(fmin(sepiaGreenDbl, 255));
    BYTE sepiaBlue = round(fmin(sepiaBlueDbl, 255));

    RGBTRIPLE temp;
    temp.rgbtRed = sepiaRed;
    temp.rgbtGreen = sepiaGreen;
    temp.rgbtBlue = sepiaBlue;

    return temp;
}

// Copies an image represented by a 2D array
// @param height    height of array
// @param width     width of array
// @param original  original array to be copied
// @param copy      result array (copy of original)
void copy_image(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = original[i][j];
        }
    }
    return;
}

// Calculates color of blurred pixel.
// @param n         array length (4 or 6 or 9)
// @param box       flattened array of box
// @return          RGB color of blurred pixel, i.e. average of box values
RGBTRIPLE get_box_blur(int n, RGBTRIPLE box[n])
{
    int sumRed = 0;
    int sumGreen = 0;
    int sumBlue = 0;
    for (int i = 0; i < n; i++)
    {
        sumRed += box[i].rgbtRed;
        sumGreen += box[i].rgbtGreen;
        sumBlue += box[i].rgbtBlue;
    }

    RGBTRIPLE temp;
    temp.rgbtRed = round((double) sumRed / n);
    temp.rgbtGreen = round((double) sumGreen / n);
    temp.rgbtBlue = round((double) sumBlue / n);

    return temp;
}