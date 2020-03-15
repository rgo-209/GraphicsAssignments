//
//  Rasterizer.cpp
//
//  Created by Warren R. Carithers on 01/28/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Rahul Golhar
//

#include <cmath>
#include <iostream>
#include "Rasterizer.h"

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
// @param C the Canvas to be used
///

Rasterizer::Rasterizer(int n, Canvas& canvas) : n_scanlines(n), C(canvas)
{
}


///
// Draw my initials
//
// Draw my own initials using calls to drawLine(), in the same
// manner that makeLines() in the driver program draws 'CG'.
///

void Rasterizer::myInitials(void) {

    // ######## Use light blue (0.678,0.847,0.902) for initials ######## 

    C.setColor(0.678, 0.847, 0.902);

    // ######## The letter 'R' in light blue ########

    drawLine(60, 60, 60, 280);
    drawLine(60, 280, 200, 280);

    drawLine(200, 280, 200, 180);
    drawLine(200, 180, 120, 180);

    drawLine(100, 60, 100, 160);
    drawLine(100, 60, 60, 60);
    drawLine(100, 160, 180, 60);

    drawLine(200, 80, 180, 60);
    drawLine(120, 180, 200, 80);

    drawLine(100, 200, 100, 240);
    drawLine(100, 200, 160, 200);
    drawLine(100, 240, 160, 240);
    drawLine(160, 200, 160, 240);

    // ######## The letter 'G' in light blue ########

    drawLine(360, 60, 360, 280);
    drawLine(360, 280, 500, 280);

    drawLine(500, 280, 500, 240);
    drawLine(500, 240, 400, 240);

    drawLine(400, 100, 400, 240);

    drawLine(400, 100, 460, 100);
    drawLine(460, 100, 460, 150);

    drawLine(440, 150, 460, 150);
    drawLine(440, 150, 440, 190);

    drawLine(500, 190, 440, 190);

    drawLine(500, 190, 500, 60);
    drawLine(360, 60, 500, 60);
}

///
// Draw a line from (x0,y0) to (x1, y1)
//
// Implementation should be using the Midpoint Line Algorithm.
//
// You are to add the implementation here using only calls to the
// setPixel() method of the Canvas.
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
///
void Rasterizer::drawLine(int x0, int y0, int x1, int y1)
{
    int temp = 0;
    // If the points are not in order swap the values
    if (x1 < x0) {
        temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
        std::cout << "Swapped points" << std::endl;
    }
    std::cout << "Starting to plot: " << "(" << x0 << "," << y0 << ")" << "->" << "(" << x1 << "," << y1 << ")" << std::endl;

    int incE, incNE, incN, incS, incSE, x, y, d;
    int dy = abs(y1 - y0);
    int dx = abs(x1 - x0);
    float slope = (float)(y1 - y0) / (x1 - x0);

    // for large positive slope(>1)
    if (slope > 1.0) {
        std::cout << "Slope > 1" << std::endl;
        incN = 2 * dx;
        incNE = 2 * (dx - dy);
        d = incN - dy; /*2*dx–dy*/
        for (x = x0, y = y0; y <= y1; ++y)
        {
            C.setPixel(x, y);
            if (d <= 0) {
                /*choose N*/
                d += incN;
            }
            else {
                /*choose NE, increment x */
                ++x;
                d += incNE;
            }
        }
        std::cout << "Plotted: " << "(" << x0 << "," << y0 << ")" << "->" << "(" << x1 << "," << y1 << ")" << std::endl;
    }
    // for slope between 0 and 1
    else if ((slope <= 1.0) && (slope >= 0.0))
    {
        std::cout << "0 < Slope < 1" << std::endl;
        incE = 2 * dy;
        incNE = 2 * (dy - dx);
        d = incE - dx; /*2*dy–dx*/
        for (x = x0, y = y0; x <= x1; ++x)
        {
            C.setPixel(x, y);
            if (d <= 0) {
                /*choose E*/
                d += incE;
            }
            else {
                /*choose NE, increment y */
                ++y;
                d += incNE;
            }
        }
        std::cout << "Plotted: " << "(" << x0 << "," << y0 << ")" << "->" << "(" << x1 << "," << y1 << ")" << std::endl;
    }
    // for slope between 0 and -1
    else if ((slope >= -1.0) && (slope < 0.0))
    {
        std::cout << "0 > Slope > -1" << std::endl;
        incSE = 2 * dy;
        incS = 2 * (dy - dx);
        d = incSE - dx;/*2*dy–dx*/
        for (x = x0, y = y0; x <= x1; ++x)
        {
            C.setPixel(x, y);
            if (d <= 0) {
                /*choose SE*/
                d += incSE;
            }
            else {
                /*choose S, decrement y */
                --y;
                d += incS;
            }
        }
        std::cout << "Plotted: " << "(" << x0 << "," << y0 << ")" << "->" << "(" << x1 << "," << y1 << ")" << std::endl;
    }

    // for large negative slope (< -1)
    else if (slope < -1.0) {
        std::cout << "Slope < -1" << std::endl;
        incS = 2 * dx;
        incSE = 2 * (dx - dy);
        d = incS - dy; /*2*dx–dy*/
        for (x = x0, y = y0; y >= y1; --y)
        {
            C.setPixel(x, y);
            if (d <= 0) {
                /*choose S*/
                d += incS;
            }
            else {
                /*choose SE, decrement x */
                ++x;
                d += incSE;
            }
        }
        std::cout << "Plotted: " << "(" << x0 << "," << y0 << ")" << "->" << "(" << x1 << "," << y1 << ")" << std::endl;
    }
}