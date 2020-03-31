//
//  Shapes
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  This code can be compiled as either C or C++.
//

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"
#include <iostream>


const float unit = 0.5;
const float neg_unit = -0.5;

///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions )
{
    if( subdivisions < 1 )
        subdivisions = 1;

    // Defining all required points here
    Vertex v_a, v_b;
    Vertex v_ax_ay_p;
    Vertex v_ax_ay_n;
    Vertex v_bx_by_p;
    Vertex v_bx_by_n;
    Vertex v_ax_by_p;
    Vertex v_ax_by_n;
    Vertex v_bx_ay_p;
    Vertex v_bx_ay_n;
    Vertex v_n_ax_by;
    Vertex v_p_ax_by;
    Vertex v_n_bx_ay;
    Vertex v_p_bx_ay;
    Vertex v_n_bx_by;
    Vertex v_p_bx_by;
    Vertex v_n_ax_ay;
    Vertex v_p_ax_ay;
    Vertex v_ax_n_by;
    Vertex v_ax_p_by;
    Vertex v_bx_n_ay;
    Vertex v_bx_p_ay;
    Vertex v_ax_n_ay;
    Vertex v_ax_p_ay;
    Vertex v_bx_n_by;
    Vertex v_bx_p_by;

    for (int x = 1; x <= subdivisions; x++)
    {
        // Compute points on the face
        v_a.x = ( (x - 1) * (1.0 / subdivisions) - unit);
        v_b.x = (    x    * (1.0 / subdivisions) - unit);

        for (int y = 1; y <= subdivisions; y++)
        {

            // Compute points on the face
            v_a.y = (  (y - 1) * (1.0 / subdivisions) - unit);
            v_b.y = (     y    * (1.0 / subdivisions) - unit);

            // Compute the required points for the face

            v_ax_ay_p.x = v_a.x;
            v_ax_ay_p.y = v_a.y;
            v_ax_ay_p.z = unit;

            v_ax_ay_n.x = v_a.x;
            v_ax_ay_n.y = v_a.y;
            v_ax_ay_n.z = neg_unit;

            v_bx_by_p.x = v_b.x;
            v_bx_by_p.y = v_b.y;
            v_bx_by_p.z = unit;

            v_bx_by_n.x = v_b.x;
            v_bx_by_n.y = v_b.y;
            v_bx_by_n.z = neg_unit;

            v_ax_by_p.x = v_a.x;
            v_ax_by_p.y = v_b.y;
            v_ax_by_p.z = unit;

            v_ax_by_n.x = v_a.x;
            v_ax_by_n.y = v_b.y;
            v_ax_by_n.z = neg_unit;

            v_bx_ay_p.x = v_b.x;
            v_bx_ay_p.y = v_a.y;
            v_bx_ay_p.z = unit;

            v_bx_ay_n.x = v_b.x;
            v_bx_ay_n.y = v_a.y;
            v_bx_ay_n.z = neg_unit;

            v_n_ax_by.x = neg_unit;
            v_n_ax_by.y = v_a.x;
            v_n_ax_by.z = v_b.y;
            v_n_bx_ay.x = neg_unit;
            v_n_bx_ay.y = v_b.x;
            v_n_bx_ay.z = v_a.y;

            v_n_ax_ay.x = neg_unit;
            v_n_ax_ay.y = v_a.x;
            v_n_ax_ay.z = v_a.y;
 
            v_n_bx_by.x = neg_unit;
            v_n_bx_by.y = v_b.x;
            v_n_bx_by.z = v_b.y;


            v_p_bx_ay.x = unit;
            v_p_bx_ay.y = v_b.x;
            v_p_bx_ay.z = v_a.y;

            v_p_ax_by.x = unit;
            v_p_ax_by.y = v_a.x;
            v_p_ax_by.z = v_b.y;
            v_p_ax_ay.x = unit;
            v_p_ax_ay.y = v_a.x;
            v_p_ax_ay.z = v_a.y;

            v_p_bx_by.x = unit;
            v_p_bx_by.y = v_b.x;
            v_p_bx_by.z = v_b.y;

            v_ax_n_by.x = v_a.x;
            v_ax_n_by.y = neg_unit;
            v_ax_n_by.z = v_b.y;

            v_bx_n_ay.x = v_b.x;
            v_bx_n_ay.y = neg_unit;
            v_bx_n_ay.z = v_a.y;

            v_ax_n_ay.x = v_a.x;
            v_ax_n_ay.y = neg_unit;
            v_ax_n_ay.z = v_a.y;

            v_bx_n_by.x = v_b.x;
            v_bx_n_by.y = neg_unit;
            v_bx_n_by.z = v_b.y;

            v_ax_p_by.x = v_a.x;
            v_ax_p_by.y = unit;
            v_ax_p_by.z = v_b.y;

            v_bx_p_ay.x = v_b.x;
            v_bx_p_ay.y = unit;
            v_bx_p_ay.z = v_a.y;

            v_ax_p_ay.x = v_a.x;
            v_ax_p_ay.y = unit;
            v_ax_p_ay.z = v_a.y;

            v_bx_p_by.x = v_b.x;
            v_bx_p_by.y = unit;
            v_bx_p_by.z = v_b.y;

            
            // Face Front
            C.addTriangle(v_ax_ay_p, v_bx_ay_p, v_ax_by_p);
            C.addTriangle(v_ax_by_p, v_bx_ay_p, v_bx_by_p);
            
            // Face Back
            C.addTriangle(v_bx_ay_n, v_ax_ay_n, v_ax_by_n);
            C.addTriangle(v_bx_ay_n, v_ax_ay_n, v_ax_by_n);

            // Face Left
            C.addTriangle(v_n_ax_by, v_n_bx_ay, v_n_ax_ay);
            C.addTriangle(v_n_ax_by, v_n_bx_by, v_n_bx_by); 

            // Face Right
            C.addTriangle(v_p_bx_ay, v_p_ax_by, v_p_ax_ay);
            C.addTriangle(v_p_bx_ay, v_p_bx_by, v_p_ax_by);

            // Face Bottom
            C.addTriangle(v_bx_n_ay, v_ax_n_by, v_ax_n_ay);
            C.addTriangle(v_bx_n_ay, v_bx_n_by, v_ax_n_by);

            // Face Top
            C.addTriangle(v_ax_p_by, v_bx_p_ay, v_ax_p_ay);
            C.addTriangle(v_bx_p_by, v_bx_p_ay, v_ax_p_by);     
        }
    }

}


///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE
    Vertex v_a;
    Vertex v_b;

    Vertex v_0_n_0;
    Vertex v_0_p_0;

    Vertex v_ax_n_az;
    Vertex v_ax_p_az;

    Vertex v_bx_n_bz;
    Vertex v_bx_p_bz;

    Vertex v_ax_by_az;
    Vertex v_ax_ay_az;
    Vertex v_bx_by_bz;
    Vertex v_bx_ay_bz;

    for (int x = 1; x <= radialDivisions; x++)
    {
        // Compute the points for calculating
        // the points on the base
        v_a.x = float(radius * cos(2 * (x - 1) * 3.14 / radialDivisions));
        v_b.x = float(radius * cos(2 * (  x  ) * 3.14 / radialDivisions));

        v_a.z = float(radius * sin(2 * (x - 1) * 3.14 / radialDivisions));
        v_b.z = float(radius * sin(2 * (  x  ) * 3.14 / radialDivisions));

        v_0_n_0.x = 0;
        v_0_n_0.y = neg_unit;
        v_0_n_0.z = 0;

        v_0_p_0.x = 0;
        v_0_p_0.y = unit;
        v_0_p_0.z = 0;

        v_ax_n_az.x = v_a.x;
        v_ax_n_az.y = neg_unit;
        v_ax_n_az.z = v_a.z;

        v_ax_p_az.x = v_a.x;
        v_ax_p_az.y = unit;
        v_ax_p_az.z = v_a.z;

        v_bx_n_bz.x = v_b.x;
        v_bx_n_bz.y = neg_unit;
        v_bx_n_bz.z = v_b.z;

        v_bx_p_bz.x = v_b.x;
        v_bx_p_bz.y = unit;
        v_bx_p_bz.z = v_b.z;


        // Base of cylinder
        C.addTriangle(v_0_n_0, v_ax_n_az, v_bx_n_bz);

        // Top of cylinder
        C.addTriangle(v_bx_p_bz , v_ax_p_az ,  v_0_p_0 );

        
        for (int y = 1; y <= heightDivisions; y++)
        {
            // Compute the points for calculating 
            // the points on the curve
            v_a.y = float((y - 1) / heightDivisions - 0.5);
            v_b.y = float(   y    / heightDivisions - 0.5);
            
            // Compute the points for calculating
            // the points on the curved surface
            v_ax_by_az.x = v_a.x;
            v_ax_by_az.y = v_b.y;
            v_ax_by_az.z = v_a.z;

            v_bx_ay_bz.x = v_b.x;
            v_bx_ay_bz.y = v_a.y;
            v_bx_ay_bz.z = v_b.z;

            v_ax_ay_az.x = v_a.x;
            v_ax_ay_az.y = v_a.y;
            v_ax_ay_az.z = v_a.z;

            v_bx_by_bz.x = v_b.x;
            v_bx_by_bz.y = v_b.y;
            v_bx_by_bz.z = v_b.z;

            // For tessalation of right side
            // it's partially visible
            C.addTriangle(v_ax_by_az, v_bx_by_bz, v_ax_ay_az);
            // For tessalation of left side
            // it's almost completely visible
            C.addTriangle(v_bx_by_bz, v_bx_ay_bz, v_ax_ay_az);

        }
    }
}


///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    Vertex v_a;
    Vertex v_b;

    Vertex v_ax_p_az;
    Vertex v_ax_n_az;

    Vertex v_bx_p_bz;
    Vertex v_bx_n_bz;

    Vertex v_a_diff;
    Vertex v_b_diff;

    Vertex v_bx_ay_bz;
    v_bx_ay_bz.x = 0;
    v_bx_ay_bz.y = 0;
    v_bx_ay_bz.z = 0;
    
    Vertex v_ax_ay_az;

    Vertex v_0_n_0;
    v_0_n_0.x = 0;
    v_0_n_0.y = neg_unit;
    v_0_n_0.z = 0;

    Vertex v_0_p_0;
    v_0_p_0.x = 0;
    v_0_p_0.y = unit;
    v_0_p_0.z = 0;


    for (int x = 1; x <= radialDivisions; x++)
    {
        v_a.x = float(radius * cos(2 * (x - 1) * 3.14 / radialDivisions));
        v_a.z = float(radius * sin(2 * (x - 1) * 3.14 / radialDivisions)); 
        
        v_b.x = float(radius * cos(2 * (  x  ) * 3.14 / radialDivisions));
        v_b.z = float(radius * sin(2 * (  x  ) * 3.14 / radialDivisions));


        v_ax_p_az.x = v_a.x;
        v_ax_p_az.y = unit;
        v_ax_p_az.z = v_a.z;

        v_ax_n_az.x = v_a.x;
        v_ax_n_az.y = neg_unit;
        v_ax_n_az.z = v_a.z;

        v_bx_p_bz.x = v_b.x;
        v_bx_p_bz.y = unit;
        v_bx_p_bz.z = v_b.z;

        v_bx_n_bz.x = v_b.x;
        v_bx_n_bz.y = neg_unit;
        v_bx_n_bz.z = v_b.z;

        C.addTriangle(v_ax_n_az, v_bx_n_bz, v_0_n_0);

        v_a.y = neg_unit;
        v_b.y = neg_unit;
        
        for (int y = 1; y <= heightDivisions - 1; y++)
        {
            v_ax_ay_az = v_a;
         
            v_a_diff.x = v_a.x - (v_a.x / heightDivisions);
            v_a_diff.y = v_a.y + (1 / (float)heightDivisions);
            v_a_diff.z = v_a.z - (v_a.z / heightDivisions);

            v_b_diff.x = v_b.x - (v_b.x / heightDivisions);
            v_b_diff.y = v_a.y + (1 / (float)heightDivisions);
            v_b_diff.z = v_b.z - (v_b.z / heightDivisions);

            v_bx_ay_bz.x = v_b.x;
            v_bx_ay_bz.y = v_a.y;
            v_bx_ay_bz.z = v_b.z;

            v_ax_ay_az.x = v_a.x;
            v_ax_ay_az.y = v_a.y;
            v_ax_ay_az.z = v_a.z;

            C.addTriangle(v_ax_ay_az, v_a_diff, v_bx_ay_bz);

            C.addTriangle(v_a_diff, v_b_diff, v_bx_ay_bz);

            v_a.x = v_a.x - (v_a.x / heightDivisions);
            v_b.x = v_b.x - (v_b.x / heightDivisions);

            v_a.y = v_a.y + (1 / (float)heightDivisions);

            v_a.z = v_a.z - (v_a.z / heightDivisions);
            v_b.z = v_b.z - (v_b.z / heightDivisions);
        }

        v_bx_ay_bz.x = v_b.x;
        v_bx_ay_bz.y = v_a.y;
        v_bx_ay_bz.z = v_b.z;
        C.addTriangle(v_a, v_0_p_0, v_bx_ay_bz);
    }
}


///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;
    
    // YOUR IMPLEMENTATION HERE
}
