//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Rahul Golhar
//

#include <list>
#include <algorithm>
#include <iostream>

#include "Rasterizer.h"
#include "Canvas.h"

using namespace std;

///
// Simple class that performs rasterization algorithms
///

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls to the
// setPixel() function.
//
// @param n - number of vertices
// @param x - array of x coordinates
// @param y - array of y coordinates
///
void Rasterizer::drawPolygon(int n, const int x[], const int y[] )
{
    int i, j, edgeTable[900], activeEdgeTable[900];
    
    //Initialize both tables
    initializeTables(edgeTable, activeEdgeTable);
 
    //For both tables with coordinates of vertices
    formTables(n, x, y, edgeTable, activeEdgeTable);
 
    //Draw polygon using both tables
    drawFigure(edgeTable, activeEdgeTable);

}

void Rasterizer::initializeTables( int *edgeTable, int *activeEdgeTable){
    /**
      Initialize the edge table and active edge table
      
      @param  edgeTable          The edge table to be initialized
      @param  activeEdgeTable    The active edge table to be initialized
    */
    for(int i = 0; i < 900; i++){
        edgeTable[i] = 900;
        activeEdgeTable[i] = 0;
    }
}

void Rasterizer::formTables( int n, const int x[], const int y[], int *edgeTable, int *activeEdgeTable){
    /**
      Form the edge table and active edge table from the vertices
      
      @param  x[]                The array of x value of all vertices
      @param  y[]                The array of y value of all vertices
      @param  activeEdgeTable    The active edge table to be formed
      @param  edgeTable          The edge table to be formed
      @param  activeEdgeTable    The active edge table to be formed
    */
    for(int i = 1; i < n; i++){
        fillTable(x[i-1], y[i-1], x[i], y[i], edgeTable, activeEdgeTable);
    }
    fillTable(x[0], y[0], x[n-1], y[n-1], edgeTable, activeEdgeTable);
    
}

void Rasterizer::fillTable(float x1, float y1, float x2, float y2, int *edgeTable, int *activeEdgeTable){
    /**
      Form the edge table and active edge table entry for the value of vertex passed
      
      @param  x1                x value of first vertex
      @param  y1                y value of first vertex
      @param  x2                x value of second vertex
      @param  y2                y value of second vertex
      @param  edgeTable         The edge table to be formed
      @param  activeEdgeTable   The active edge table to be formed
    */
    float xTemp, yTemp, x, slopeInverse;
    // Swap vertices according to y value
	if (y1 > y2){
        xTemp = x1;
        x1 = x2;
        x2 = xTemp;
        yTemp = y1;
        y1 = y2;
        y2 = yTemp;
    }
	// if slop=0
    if(y1 == y2){
        slopeInverse = x2 - x1;
    }
    else{
		// regular slope inverse
        slopeInverse = float((x2 - x1)/(y2 - y1));
    } 
    x = x1;
	// Add entries to both tables
    for(int i = y1; i <= y2; i ++){
       if(x < edgeTable[i]){
           edgeTable[i] = (int)x;
       }
       if(x > activeEdgeTable[i]){
           activeEdgeTable[i] = (int)x;
       }
       x += slopeInverse;
     }
}

void Rasterizer::drawFigure( int *edgeTable, int *activeEdgeTable){
    /**
      Draw the polygon using the edge table and active edge table value
      
      @param  edgeTable         The edge table of the polygon to be formed
      @param  activeEdgeTable   The active edge table of the polygon to be formed
    */
  	for ( int i = 1; i < 900; i++){
      if(edgeTable[i] <= activeEdgeTable[i]){
          for( int j = edgeTable[i]; j <= activeEdgeTable[i]; j ++){
              C.setPixel(j, i);
          } 
      }
    }
}