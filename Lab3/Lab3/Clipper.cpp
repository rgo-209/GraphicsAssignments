//
//  Clipper.cpp
//
//  Created by Warren R. Carithers on 01/15/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  YOUR_NAME_HERE
//

#include "Vertex.h"
#include "Clipper.h"
#include <iostream>

///
// Simple module that performs clipping
///

///
// Constructor
///
Clipper::Clipper() {
}

static int outVertices=0;

///
// intersection_point
//
// Find the intersection point of 2 lines
//
// @param v1    the first vertex
// @param v2    the second vertex
// @param v3    the third vertex
// @param v4    the fourth vertex
//
// @return intersection point of the lines
//
///
Vertex intersection_point(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{

    Vertex intersection;

    int num = (v1.x * v2.y - v1.y * v2.x) * (v3.x - v4.x) -
        (v1.x - v2.x) * (v3.x * v4.y - v3.y * v4.x);
    int den = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
    intersection.x = num / den;

    num = (v1.x * v2.y - v1.y * v2.x) * (v3.y - v4.y) -
        (v1.y - v2.y) * (v3.x * v4.y - v3.y * v4.x);
    den = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
    intersection.y = num / den;

    return intersection;
}



///
// clipVertices
//
// Clip vertices w.r.t. the current edge being selected.
// 
// @param in    the number of vertices
// @param inV   the first vertex
// @param v2    the second vertex
// @param v3    the third vertex
// @param v4    the fourth vertex
//
// @return intersection point of the lines
//
///
void clipVertices(int in, const Vertex *inV, Vertex *outV, Vertex v1, Vertex v2)
{

    for (int i = 0; i < in; i++)
    {
        int j = (i + 1) % 4;

        std::cout << "Clipping line: (" << inV[i].x << "," << inV[i].y << ")" <<
                                 "-> (" << inV[j].x << "," << inV[j].y << ")" << std::endl;

        Vertex intersectionPoint = intersection_point( inV[i], inV[j], v1, v2 );

        int i_position, j_position;

        i_position = (v2.x - v1.x) * (inV[i].y - v1.y) - (v2.y - v1.y) * (inV[i].x - v1.x);

        j_position = (v2.x - v1.x) * (inV[j].y - v1.y) - (v2.y - v1.y) * (inV[j].x - v1.x);
        

        // Case 1 : both points are inside 
        if (i_position < 0 && j_position < 0)
        {
            //Add first point 
            outV[outVertices] = inV[j];
            outVertices++;
        }

        // Case 2: only first point is outside 
        else if (i_position >= 0 && j_position < 0)
        {
            // Add point of intersection with current edge           
            outV[outVertices] = intersection_point(inV[i], inV[j], v1, v2);
            outVertices++;
            // Add second point
            outV[outVertices] = inV[j];
            outVertices++;
        }

        // Case 3: When only second point is outside 
        else if (i_position < 0 && j_position >= 0)
        {
            // Add point of intersection with current edge           
            outV[outVertices] = intersection_point(inV[i], inV[j], v1, v2);
            outVertices++;
        }

        // Case 4: When both points are outside 
        else
        {
            // None of the points are added 
        }
    }
}




///
// sutherlandHodgmanAlgo
//
// Clip windows according to each and every vertex
//

// @param in                    the number of vertices in the polygon to be clipped
// @param inV                   the incoming vertex list
// @param outV                  the outgoing vertex list
// @param clipWindowVertices    the clip window vertices list
//
//
///
void sutherlandHodgmanAlgo(int in, const Vertex *inV, Vertex *outV, Vertex *clipWindowVertices)
{
    int outNum=0;
    for ( int i = 0; i < 4; i++)
    { 
        int j = (i + 1) % 4;

        clipVertices(in, inV, outV, clipWindowVertices[i], clipWindowVertices[j]);

    }
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

int Clipper::clipPolygon( int in, const Vertex inV[], Vertex outV[],
                          Vertex ll, Vertex ur )
{
    // YOUR CODE GOES HERE

    Vertex clipWindowVertices[4];
    clipWindowVertices[0] = ll;

    clipWindowVertices[1].x = ur.x;
    clipWindowVertices[1].y = ll.y;
    
    clipWindowVertices[2] = ur;

    clipWindowVertices[3].x = ll.x;
    clipWindowVertices[3].y = ur.y;

    std::cout << "Clip edge 1: (" << clipWindowVertices[0].x << " , " << clipWindowVertices[0].y << ")" << std::endl;
    std::cout << "Clip edge 2: (" << clipWindowVertices[1].x << " , " << clipWindowVertices[1].y << ")" << std::endl;
    std::cout << "Clip edge 3: (" << clipWindowVertices[2].x << " , " << clipWindowVertices[2].y << ")" << std::endl;
    std::cout << "Clip edge 4: (" << clipWindowVertices[3].x << " , " << clipWindowVertices[3].y << ")" << std::endl;
    

    sutherlandHodgmanAlgo(in, inV, outV, clipWindowVertices);


    return outNum;  // remember to return the outgoing vertex count!

}