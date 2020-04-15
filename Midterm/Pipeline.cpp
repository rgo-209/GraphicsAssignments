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

// Store the old clip vertices
float oldBottom, oldTop, oldLeft, oldRight;


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
    std::cout << "Added polygon: " << currentID<<std::endl;
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
    int edgeTable[1000], activeEdgeTable[1000];
    
    int n = clippedNoOfVertices[polyID];
    int x[1000];
    int y[1000];
    
    for (int i = 0; i < n; i++) {
        // view port is the last transform 
        // multiplied by current transform
        Vertex tempVertex = transformedPolygons[polyID][i];
        x[i] = (int)(identityMatrix[0][0] * tempVertex.x + identityMatrix[0][1] * tempVertex.y + identityMatrix[0][2] * 1);
        y[i] = (int)(identityMatrix[1][0] * tempVertex.x + identityMatrix[1][1] * tempVertex.y + identityMatrix[1][2] * 1);
    }
        //Initialize both tables
        initializeTables(edgeTable, activeEdgeTable);

        //For both tables with coordinates of vertices
        formTables(n, x, y, edgeTable, activeEdgeTable);

        //Draw polygon using both tables
        drawFigure(edgeTable, activeEdgeTable);
    
    std::cout << "Drawn polygon: " << polyID << std::endl;
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
    std::cout << "\tCleared Identity Matrix..!!" << std::endl;
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
    //Translate(x, y) = {1 0 tx
    //                   0 1 ty
    //                   0 0  1}
    identityMatrix[0][0] = 1 * identityMatrix[0][0] + 0 * identityMatrix[1][0] + tx * identityMatrix[2][0];
    identityMatrix[0][1] = 1 * identityMatrix[0][1] + 0 * identityMatrix[1][1] + tx * identityMatrix[2][1];
    identityMatrix[0][2] = 1 * identityMatrix[0][2] + 0 * identityMatrix[1][2] + tx * identityMatrix[2][2];

    identityMatrix[1][0] = 0 * identityMatrix[0][0] + 1 * identityMatrix[1][0] + ty * identityMatrix[2][0];
    identityMatrix[1][1] = 0 * identityMatrix[0][1] + 1 * identityMatrix[1][1] + ty * identityMatrix[2][1];
    identityMatrix[1][2] = 0 * identityMatrix[0][2] + 1 * identityMatrix[1][2] + ty * identityMatrix[2][2];

    identityMatrix[2][0] = 0 * identityMatrix[0][0] + 0 * identityMatrix[1][0] + 1 * identityMatrix[2][0];
    identityMatrix[2][1] = 0 * identityMatrix[0][1] + 0 * identityMatrix[1][1] + 1 * identityMatrix[2][1];
    identityMatrix[2][2] = 0 * identityMatrix[0][2] + 0 * identityMatrix[1][2] + 1 * identityMatrix[2][2];

    std::cout << "\t\tTranslating polygon: " << tx << "," << ty << std::endl;
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
    //R(rad) = { cos(rad) -sin(rad)     0
    //           sin(rad)  cos(rad)     0
    //              0          0        1}

    //rad = degress * pi / 180
    float rad = (degrees * 22) / (7*180);
    identityMatrix[0][0] = cos(rad) * identityMatrix[0][0] + (-sin(rad) * identityMatrix[1][0]) + 0 * identityMatrix[2][0];
    identityMatrix[0][1] = cos(rad) * identityMatrix[0][1] + (-sin(rad) * identityMatrix[1][1]) + 0 * identityMatrix[2][1];
    identityMatrix[0][2] = cos(rad) * identityMatrix[0][2] + (-sin(rad) * identityMatrix[1][2]) + 0 * identityMatrix[2][2];

    identityMatrix[1][0] = sin(rad) * identityMatrix[0][0] + cos(rad) * identityMatrix[1][0] + 0 * identityMatrix[2][0];
    identityMatrix[1][1] = sin(rad) * identityMatrix[0][1] + cos(rad) * identityMatrix[1][1] + 0 * identityMatrix[2][1];
    identityMatrix[1][2] = sin(rad) * identityMatrix[0][2] + cos(rad) * identityMatrix[1][2] + 0 * identityMatrix[2][2];

    identityMatrix[2][0] = 0 * identityMatrix[0][0] + 0 * identityMatrix[1][0] + 1 * identityMatrix[2][0];
    identityMatrix[2][1] = 0 * identityMatrix[0][1] + 0 * identityMatrix[1][1] + 1 * identityMatrix[2][1];
    identityMatrix[2][2] = 0 * identityMatrix[0][2] + 0 * identityMatrix[1][2] + 1 * identityMatrix[2][2];

    std::cout << "\t\tRotating polygon: " << degrees << "degrees -> " << rad << std::endl;
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
    //S(x, y) = { sx 0  0
    //            0  sy 0
    //            0  0   1}
    identityMatrix[0][0] = sx * identityMatrix[0][0] + 0 * identityMatrix[1][0] + 0 * identityMatrix[2][0];
    identityMatrix[0][1] = sx * identityMatrix[0][1] + 0 * identityMatrix[1][1] + 0 * identityMatrix[2][1];
    identityMatrix[0][2] = sx * identityMatrix[0][2] + 0 * identityMatrix[1][2] + 0 * identityMatrix[2][2];

    identityMatrix[1][0] = 0 * identityMatrix[0][0] + sy * identityMatrix[1][0] + 0 * identityMatrix[2][0];
    identityMatrix[1][1] = 0 * identityMatrix[0][1] + sy * identityMatrix[1][1] + 0 * identityMatrix[2][1];
    identityMatrix[1][2] = 0 * identityMatrix[0][2] + sy * identityMatrix[1][2] + 0 * identityMatrix[2][2];

    identityMatrix[2][0] = 0 * identityMatrix[0][0] + 0 * identityMatrix[1][0] + 1 * identityMatrix[2][0];
    identityMatrix[2][1] = 0 * identityMatrix[0][1] + 0 * identityMatrix[1][1] + 1 * identityMatrix[2][1];
    identityMatrix[2][2] = 0 * identityMatrix[0][2] + 0 * identityMatrix[1][2] + 1 * identityMatrix[2][2];

    std::cout << "\t\tScaling polygon: " << sx << "," << sy << std::endl;
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
    Vertex ll, ur;
    ll.x = left;
    ll.y = bottom;
 
    ur.x = right;
    ur.y = top;
    
    for (int i = 0; i < currentID; i++) {
        Vertex outV[1000];
        int in = initNoOfVertices[i];
        clippedNoOfVertices[i] = clipPolygon(in, initPolygons[i], outV, ll, ur);
        for (int j = 0; j < clippedNoOfVertices[i]; j++) {
            // store the vertices after clipping
            clippedPolygons[i][j] = outV[j];
        }
        std::cout << "\tClipped Polygon: " << i << std::endl;
    }
    //store the boundaries 
    oldBottom = bottom;
    oldTop = top;
    oldLeft = left;
    oldRight = right;

    std::cout << "\tClip Window set..!!" <<std::endl;
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
    // Here, we considering transforming
    // directly from the clipwindow

    // polygon matrix = {x
    //                   y
    //                   1}

    // Transormation Matrix = {sx  0  tx
    //                          0 sy  ty
    //                          0  0  1}

    
    //set the value of sx = (xmax - xmin) / (right - left)
    float sx = (x + width - x) / (oldRight - oldLeft);
    
    //set the value of sy = (ymax - ymin) / (top - bottom)
    float sy = (y + height - y) / (oldTop - oldBottom);
    
    //set the value of tx = (right * xmin - left * xmax) / (right - left)
    float tx = (oldRight * x - oldLeft * (width + x)) / (oldRight - oldLeft);
    
    //set the value of ty = (top * ymin - bottom * ymax) / (top - bottom)
    float ty = (oldTop * y - oldBottom * (y + height)) / (oldTop - oldBottom);
    
    for (int i = 0; i < currentID; i++) {
        for (int j = 0; j < clippedNoOfVertices[i]; j++) {
            // set new vertices for the clipped polygon
            //x_new = sx * x + 0 * y + tx * 1
            transformedPolygons[i][j].x = sx * clippedPolygons[i][j].x + 0 * clippedPolygons[i][j].y + tx * 1;
            //y_new = 0 * x + sy * y + ty * 1
            transformedPolygons[i][j].y = 0 * clippedPolygons[i][j].x + sy * clippedPolygons[i][j].y + ty * 1;
        }
    }
    std::cout << "\tSetting the viewport done..!!"<< std::endl;
}


//**************************** LAB 2 - Draw Polygon ************************
 /**
      Initialize the edge table and active edge table

      @param  edgeTable          The edge table to be initialized
      @param  activeEdgeTable    The active edge table to be initialized
    */
void Pipeline::initializeTables(int* edgeTable, int* activeEdgeTable) {
   
    for (int i = 0; i < 900; i++) {
        edgeTable[i] = 900;
        activeEdgeTable[i] = 0;
    }
}

/**
      Form the edge table and active edge table from the vertices

      @param  x[]                The array of x value of all vertices
      @param  y[]                The array of y value of all vertices
      @param  activeEdgeTable    The active edge table to be formed
      @param  edgeTable          The edge table to be formed
      @param  activeEdgeTable    The active edge table to be formed
*/
void Pipeline::formTables(int n, const int x[], const int y[], int* edgeTable, int* activeEdgeTable) {
    for (int i = 1; i < n; i++) {
        fillTable(x[i - 1], y[i - 1], x[i], y[i], edgeTable, activeEdgeTable);
    }
    fillTable(x[0], y[0], x[n - 1], y[n - 1], edgeTable, activeEdgeTable);

}

/**
   Form the edge table and active edge table entry for the value of vertex passed

   @param  x1                x value of first vertex
   @param  y1                y value of first vertex
   @param  x2                x value of second vertex
   @param  y2                y value of second vertex
   @param  edgeTable         The edge table to be formed
   @param  activeEdgeTable   The active edge table to be formed
 */
void Pipeline::fillTable(float x1, float y1, float x2, float y2, int* edgeTable, int* activeEdgeTable) {
    float xTemp, yTemp, x, slopeInverse;
    // Swap vertices according to y value
    if (y1 > y2) {
        xTemp = x1;
        x1 = x2;
        x2 = xTemp;
        yTemp = y1;
        y1 = y2;
        y2 = yTemp;
    }
    // if slop=0
    if (y1 == y2) {
        slopeInverse = x2 - x1;
    }
    else {
        // regular slope inverse
        slopeInverse = float((x2 - x1) / (y2 - y1));
    }
    x = x1;
    // Add entries to both tables
    for (int i = y1; i <= y2; i++) {
        if (x < edgeTable[i]) {
            edgeTable[i] = (int)x;
        }
        if (x > activeEdgeTable[i]) {
            activeEdgeTable[i] = (int)x;
        }
        x += slopeInverse;
    }
}

/**
  Draw the polygon using the edge table and active edge table value

  @param  edgeTable         The edge table of the polygon to be formed
  @param  activeEdgeTable   The active edge table of the polygon to be formed
*/
void Pipeline::drawFigure(int* edgeTable, int* activeEdgeTable) {

    for (int i = 1; i < 900; i++) {
        if (edgeTable[i] <= activeEdgeTable[i]) {
            for (int j = edgeTable[i]; j <= activeEdgeTable[i]; j++) {
                setPixel(j, i);
            }
        }
    }
}




//**************************** LAB 3 - Clipping ************************
///
// inside
//
// Checks if the vertex is inside the polygon w.r.t. the endpoints of the current edge used for clipping.
//
// @param v1    the first vertex
// @param v2    the second vertex
// @param v     the vertex to check for
//
// @return true if vertex is inside the polygon
//
///
bool Pipeline::  inside(Vertex v, Vertex v1, Vertex v2, int side)
{
    if (side == 1 && v1.y < v.y)
    {
        // Bottom
        return true;
    }
    else if (side == 2 && v2.x > v.x)
    {
        // Right
        return true;
    }
    else if (side == 3 && v1.y > v.y)
    {
        // Top
        return true;
    }
    else if (side == 4 && v2.x < v.x)
    {
        // Left
        return true;
    }
    else
    {
        return false;
    }
}

///
// sutherlandHodgmanAlgo
//
// Clip vertices using Sutherland Hodgman Algorithm
// w.r.t. the current edge being selected.
// 
// @param in            the number of incoming vertices
// @param inVertices    incoming vertices array
// @param outVertices   outgoing vertices array
// @param v1            the first vertex of edge
// @param v2            the second vertex of edge
// @param side          the side of the edge
//
// @return              number of elements in array of 
//                      vertices clipped w.r.t. current edge
//
///
int Pipeline::  sutherlandHodgmanAlgo(int in, const Vertex* inVertices, Vertex* outVertices, Vertex v1, Vertex v2, int side)
{
    int outGoingCount = 0;

    Vertex second_vertex = inVertices[in - 1];

    // Iterate through all edges
    for (int i = 0; i < in; i++)
    {
        Vertex first_vertex = inVertices[i];

        //If first point is inside
        if (inside(first_vertex, v1, v2, side)) {
            //If second point is inside
            if (inside(second_vertex, v1, v2, side)) {
                outVertices[outGoingCount] = first_vertex;
                outGoingCount++;
            }
            else {

                //If second point is outside
                if (v1.x == v2.x) {
                    outVertices[outGoingCount].x = v1.x;
                    outVertices[outGoingCount].y = first_vertex.y + (v1.x - first_vertex.x) * (second_vertex.y - first_vertex.y) / (second_vertex.x - first_vertex.x);
                }
                else {
                    outVertices[outGoingCount].x = first_vertex.x + (v1.y - first_vertex.y) * (second_vertex.x - first_vertex.x) / (second_vertex.y - first_vertex.y);
                    outVertices[outGoingCount].y = v1.y;
                }
                outGoingCount++;
                outVertices[outGoingCount] = first_vertex;
                outGoingCount++;
            }
        }
        else {
            // If first point is outside, but second is inside
            if (inside(second_vertex, v1, v2, side)) {
                if (v1.x == v2.x) {
                    outVertices[outGoingCount].x = v1.x;
                    outVertices[outGoingCount].y = first_vertex.y + (v1.x - first_vertex.x) * (second_vertex.y - first_vertex.y) / (second_vertex.x - first_vertex.x);
                }
                else {
                    outVertices[outGoingCount].x = first_vertex.x + (v1.y - first_vertex.y) * (second_vertex.x - first_vertex.x) / (second_vertex.y - first_vertex.y);
                    outVertices[outGoingCount].y = v1.y;
                }
                outGoingCount++;
            }
        }
        second_vertex = first_vertex;
    }
    return outGoingCount;
}

///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///

int Pipeline:: clipPolygon(int in, const Vertex inV[], Vertex outV[], Vertex ll, Vertex ur)
{
    Vertex outV_left[50];
    Vertex outV_right[50];
    Vertex outV_bottom[50];
    Vertex outV_top[50];
    Vertex* inVertices = new Vertex[50];

    // Copy initial vertices in array. 
    for (int i = 0; i < in; i++)
    {
        inVertices[i] = inV[i];
    }

    int outVertices = 0;

    // Store the clip window edges
    Vertex clipWindowVertices[4];

    // bottom left
    clipWindowVertices[0] = ll;

    // bottom right 
    clipWindowVertices[1].x = ur.x;
    clipWindowVertices[1].y = ll.y;

    // top right
    clipWindowVertices[2] = ur;

    // top left
    clipWindowVertices[3].x = ll.x;
    clipWindowVertices[3].y = ur.y;

    // Start clipping

    // w.r.t. left side
    outVertices = sutherlandHodgmanAlgo(in, inVertices, outV_left, clipWindowVertices[0], clipWindowVertices[3], 4);

    // w.r.t. right side
    outVertices = sutherlandHodgmanAlgo(outVertices, outV_left, outV_right, clipWindowVertices[1], clipWindowVertices[2], 2);

    // w.r.t. top side
    outVertices = sutherlandHodgmanAlgo(outVertices, outV_right, outV_top, clipWindowVertices[3], clipWindowVertices[2], 3);

    // w.r.t. bottom side
    outVertices = sutherlandHodgmanAlgo(outVertices, outV_top, outV_bottom, clipWindowVertices[0], clipWindowVertices[1], 1);

    // Combining all the vertices to return 
    for (int i = 0; i < outVertices; i++)
    {
        outV[i] = outV_bottom[i];
    }

    // return the outgoing vertex count
    return outVertices;
}