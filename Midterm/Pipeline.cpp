//
//  Pipeline.cpp
//
//  Created by Warren R. Carithers on 2016/10/19.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2016 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include <iostream>

#include "Pipeline.h"

///
// Simple wrapper class for midterm assignment
//
// Only methods in the implementation file whose bodies
// contain the comment
//
//    // YOUR IMPLEMENTATION HERE
//
// are to be modified by students.
///

///
// Constructor
//
// @param w width of canvas
// @param h height of canvas
///
Pipeline::Pipeline( int w, int h ) : Canvas(w,h)
    // YOUR IMPLEMENTATION HERE if you need to add initializers
{
    // YOUR IMPLEMENTATION HERE if you need to modify the constructor
}


//************ Defining all required global variables **********
//Initial vertices of polygons
Vertex initPolygons[1000][1000];

//Vertices of polygons after clipping
Vertex clippedPolygons[1000][1000];

//Vertices of polygons after transformation
Vertex transformedPolygons[1000][1000];

//Store number of vertices of initial polygon
int initNoOfVertices[1000];

//Store number of vertices of clipped polygon
int clippedNoOfVertices[1000];

//Unique ID for the polygon
static int currentID = 0;

//Identity matrix
float identityMatrix[3][3];




///
// addPoly - Add a polygon to the canvas.  This method does not draw
//           the polygon, but merely stores it for later drawing.
//           Drawing is initiated by the drawPoly() method.
//
//           Returns a unique integer id for the polygon.
//
// @param p - Array containing the vertices of the polygon to be added.
// @param n - Number of vertices in polygon
//
// @return a unique integer identifier for the polygon
///
int Pipeline::addPoly( const Vertex p[], int n )
{   
    initNoOfVertices[currentID] = n;
    for (int i = 0; i < n; i++) {
        // Add the vertices of the current polygon being added
        initPolygons[currentID][i] = p[i];
    }
    std::cout << "added polygon: " << currentID<<std::endl;
    //Update the id for next polygon
    currentID+=1;

    //return the id of added polygon
    return currentID - 1;
}

///
// drawPoly - Draw the polygon with the given id.  The polygon should
//            be drawn after applying the current transformation to
//            the vertices of the polygon.
//
// @param polyID - the ID of the polygon to be drawn.
///
void Pipeline::drawPoly( int polyID )
{
    // YOUR IMPLEMENTATION HERE
}

///
// clearTransform - Set the current transformation to the identity matrix.
///
void Pipeline::clearTransform( void )
{
    //Identity Matrix = {1 0 0
    //                   0 1 0
    //                   0 0 1}

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(i==j)
                identityMatrix[i][j] = 1;
            else
                identityMatrix[i][j] = 0;
        }
    }
}

///
// translate - Add a translation to the current transformation by
//             premultiplying the appropriate translation matrix to
//             the current transformation matrix.
//
// @param x - Amount of translation in x.
// @param y - Amount of translation in y.
///
void Pipeline::translate( float tx, float ty )
{
    // YOUR IMPLEMENTATION HERE
}

///
// rotate - Add a rotation to the current transformation by premultiplying
//          the appropriate rotation matrix to the current transformation
//          matrix.
//
// @param degrees - Amount of rotation in degrees.
///
void Pipeline::rotate( float degrees )
{
    // YOUR IMPLEMENTATION HERE
}

///
// scale - Add a scale to the current transformation by premultiplying
//         the appropriate scaling matrix to the current transformation
//         matrix.
//
// @param x - Amount of scaling in x.
// @param y - Amount of scaling in y.
///
void Pipeline::scale( float sx, float sy )
{
    // YOUR IMPLEMENTATION HERE
}

///
// setClipWindow - Define the clip window.
//
// @param bottom - y coord of bottom edge of clip window (in world coords)
// @param top - y coord of top edge of clip window (in world coords)
// @param left - x coord of left edge of clip window (in world coords)
// @param right - x coord of right edge of clip window (in world coords)
///
void Pipeline::setClipWindow( float bottom, float top, float left, float right )
{
    // YOUR IMPLEMENTATION HERE
}

///
// setViewport - Define the viewport.
//
// @param xmin - x coord of lower left of view window (in screen coords)
// @param ymin - y coord of lower left of view window (in screen coords)
// @param width - width of view window (in world coords)
// @param height - width of view window (in world coords)
///
void Pipeline::setViewport( int x, int y, int width, int height )
{
    // YOUR IMPLEMENTATION HERE
}
