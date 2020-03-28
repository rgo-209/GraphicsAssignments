//
//  clipper.h
//
//  Created by Warren R. Carithers on 02/27/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Rahul Golhar
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "Vertex.h"

///
// Simple module that performs clipping
///

class Clipper {

public:

    ///
    // Constructor
    ///
    Clipper();

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
    //
    bool inside(Vertex v, Vertex v1, Vertex v2, int side);
    
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
    int sutherlandHodgmanAlgo(int in, const Vertex* inVertices, Vertex* outVertices, Vertex v1, Vertex v2, int side);
    
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
    int clipPolygon(int in, const Vertex inV[], Vertex outV[],
        Vertex ll, Vertex ur);

};

#endif