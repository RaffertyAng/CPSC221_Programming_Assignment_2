/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"
#include <cmath>
QuarterColorPicker::QuarterColorPicker(PNG& inputimg, unsigned char b_amount)
{
    // Complete your implementation below
	referenceimg = inputimg;
    brightamount = b_amount;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 * 
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 * 
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    // scale the reference image dimensions

    int scaled_width = referenceimg.width() / 2;
    int scaled_height = referenceimg.height() / 2;

    // finds the coordinates of the pixel in the tiled reference image
    int quarter_img_X_coord = p.x % scaled_width;
    int quarter_img_Y_coord = p.y % scaled_height;

    int full_img_x_coord = quarter_img_X_coord * 2;
    int full_img_y_coord = quarter_img_Y_coord * 2;
    
    int r = 0, g = 0, b = 0, a = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            r += referenceimg.getPixel(full_img_x_coord + i, full_img_y_coord + j)->r;
            g += referenceimg.getPixel(full_img_x_coord + i, full_img_y_coord + j)->g;
            b += referenceimg.getPixel(full_img_x_coord + i, full_img_y_coord + j)->b;
            a += referenceimg.getPixel(full_img_x_coord + i, full_img_y_coord + j)->a;
        }
    }
    r /= 4;
    g /= 4;
    b /= 4;
    a /= 4;

    // find colour based on the bilinear interpolation
    // formula using the 4 pixels
    r = min(255, r + brightamount);
    g = min(255, g + brightamount);
    b = min(255, b + brightamount);

    return RGBAPixel(r, g, b, a);
}

/**
 * Add your private QuarterColorPicker function implementations below
 */
