//
//  Clipper.cpp
//
//  Created by Warren R. Carithers on 01/15/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Rahul Golhar
//

#include "Vertex.h"
#include "Clipper.h"
#include <iostream>
#include <float.h>

///
// Simple module that performs clipping
///

///
// Constructor
///
Clipper::Clipper() {
}

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
bool Clipper:: inside(Vertex v, Vertex v1, Vertex v2, int side)
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
int Clipper:: sutherlandHodgmanAlgo(int in, const Vertex *inVertices, Vertex *outVertices, Vertex v1, Vertex v2, int side)
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

int Clipper::clipPolygon(int in, const Vertex inV[], Vertex outV[],Vertex ll, Vertex ur)
{
    Vertex outV_left[50];
    Vertex outV_right[50];
    Vertex outV_bottom[50];
    Vertex outV_top[50];
    Vertex *inVertices = new Vertex[50];

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