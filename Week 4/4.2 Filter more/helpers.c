#include <math.h>

#include "helpers.h"

BYTE get_RGB_average(BYTE r, BYTE g, BYTE b);
void copy_image(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width]);
RGBTRIPLE get_box_blur(int n, RGBTRIPLE box[n]);
RGBTRIPLE black_pixel(void);
RGBTRIPLE edgeSobel(int n, RGBTRIPLE box[n]);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image
    RGBTRIPLE img_copy[height][width];
    copy_image(height, width, image, img_copy);

    // iterate individual pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get Box
            int box_height = 3;
            int box_width = 3;
            RGBTRIPLE box[box_height * box_width]; // flattened
            int box_ndx = 0;
            for (int img_r = i - 1; img_r <= i + 1; img_r++)
            {
                // if (img_r >= 0 && img_r <= height - 1)
                {
                    for (int img_c = j - 1; img_c <= j + 1; img_c++)
                    {
                        if (img_r >= 0 && img_r <= height - 1 && img_c >= 0 && img_c <= width - 1)
                        {
                            box[box_ndx] = img_copy[img_r][img_c];
                        }
                        else
                        {
                            // black pixel
                            box[box_ndx] = black_pixel();
                        }
                        box_ndx++;
                    }
                }
            }

            // calculate pixel color
            RGBTRIPLE pixel_new = edgeSobel(box_height * box_width, box);

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

// Returns a black pixel (RGB=0)
RGBTRIPLE black_pixel(void)
{
    RGBTRIPLE temp;
    temp.rgbtRed = 0;
    temp.rgbtGreen = 0;
    temp.rgbtBlue = 0;

    return temp;
}

// Returns the final RGB color of a pixel after applying edge filter, using Sobel algorithm.
// @param n         array length (must be 9)
// @param box       flattened array of box
// Return           RGB color of pixel after applying edge filter
RGBTRIPLE edgeSobel(int n, RGBTRIPLE box[n])
{
    int Gx_Red = 0, Gx_Green = 0, Gx_Blue = 0;
    int Gy_Red = 0, Gy_Green = 0, Gy_Blue = 0;
    int Gx_mask[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy_mask[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < n; i++)
    {
        // Gx channels
        Gx_Red += box[i].rgbtRed * Gx_mask[i];
        Gx_Green += box[i].rgbtGreen * Gx_mask[i];
        Gx_Blue += box[i].rgbtBlue * Gx_mask[i];
        // Gy channels
        Gy_Red += box[i].rgbtRed * Gy_mask[i];
        Gy_Green += box[i].rgbtGreen * Gy_mask[i];
        Gy_Blue += box[i].rgbtBlue * Gy_mask[i];
    }

    // final colors
    BYTE final_Red = round(fmin(sqrt(pow((double)Gx_Red, 2) + pow((double)Gy_Red, 2)), 255.));
    BYTE final_Green = round(fmin(sqrt(pow((double)Gx_Green, 2) + pow((double)Gy_Green, 2)), 255.));
    BYTE final_Blue = round(fmin(sqrt(pow((double)Gx_Blue, 2) + pow((double)Gy_Blue, 2)), 255.));


    RGBTRIPLE temp;
    temp.rgbtRed = final_Red;
    temp.rgbtGreen = final_Green;
    temp.rgbtBlue = final_Blue;

    return temp;
}