/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"
#include <cmath>
#include <vector>
/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG& inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    // Complete your implementation below
	borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
    reColor.resize(img.width());
    for (int i = 0; i < img.width(); i++) {
        reColor[i].resize(img.height());
        for (int j = 0; j < img.height(); j++) {
            PixelPoint t(i, j, *(img.getPixel(i, j)));
            // cout<<(int)t.color.r<<' ';
            reColor[i][j] = PickColor(t);
        }
    }
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    // Replace the line below with your implementation
    return reColor[p.x][p.y];
    // if (reColor[p.x][p.y]) {
    //     return bordercolor;
    // }
    // // cout<<(int)p.color.r<<' ';
    // return p.color;
}

/**
 * Add your private BorderColorPicker function implementations below
 */

RGBAPixel BorderColorPicker::PickColor(PixelPoint p) {
    if (img.getPixel(p.x, p.y)->distanceTo(seedcolor) >= tolerance) {
        return p.color;
    }
    if (p.x + 1 <= borderwidth || p.y + 1 <= borderwidth || p.x + borderwidth >= img.width() || p.y + borderwidth >= img.height()) {
        return bordercolor;
    }
    for (int x = max(0, (int)p.x - (int)borderwidth - 1); x < min((unsigned int)img.width(), p.x + borderwidth + 1); x++) {
        for (int y = max(0, (int)p.y - (int)borderwidth - 1); y < min(img.height(), p.y + borderwidth + 1); y++) {
            int dis = (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
            if ((img.getPixel(x, y)->distanceTo(seedcolor) >= tolerance && dis <= borderwidth * borderwidth)) {
                return bordercolor;
            }
        }
    }
    return p.color;
}