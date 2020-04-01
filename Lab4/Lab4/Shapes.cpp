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
void makeCone(Canvas& C, float radius, int radialDivisions, int heightDivisions)
{
    if (radialDivisions < 3)
        radialDivisions = 3;

    if (heightDivisions < 1)
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

        v_b.x = float(radius * cos(2 * (x) * 3.14 / radialDivisions));
        v_b.z = float(radius * sin(2 * (x) * 3.14 / radialDivisions));


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
// drawSlices - Create slice of the given sphere of a given radius,
// centered at the origin, using spherical coordinates with separate
// number of thetha and phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param v_a - vertex of the slice.
// @param v_b - vertex of the slice.
// @param v_c - vertex of the slice.
//
// Can only use calls to C.addTriangle()
///
void drawSlices(Canvas &C , float radius, int slices, Vertex v_a, Vertex v_b, Vertex v_c)
{

    if (slices > 1)
    {
        // Define required vertices
        Vertex v_a_b_2;
        v_a_b_2.x = (v_a.x + v_b.x) / 2;
        v_a_b_2.y = (v_a.y + v_b.y) / 2;
        v_a_b_2.z = (v_a.z + v_b.z) / 2;

        Vertex v_a_c_2;
        v_a_c_2.x = (v_a.x + v_c.x) / 2;
        v_a_c_2.y = (v_a.y + v_c.y) / 2;
        v_a_c_2.z = (v_a.z + v_c.z) / 2;

        Vertex v_b_c_2;
        v_b_c_2.x = (v_c.x + v_b.x) / 2;
        v_b_c_2.y = (v_c.y + v_b.y) / 2;
        v_b_c_2.z = (v_c.z + v_b.z) / 2;

        // Recursively call function to draw slices one by one
        drawSlices(C, radius, (slices - 1),   v_a   , v_a_b_2 , v_a_c_2);
        drawSlices(C, radius, (slices - 1), v_a_b_2 , v_b_c_2 , v_a_c_2);
        drawSlices(C, radius, (slices - 1), v_a_b_2 ,   v_b   , v_b_c_2);
        drawSlices(C, radius, (slices - 1), v_a_c_2 , v_b_c_2 ,   v_c  );
    }
    else
    {
        //Define all required vertices
        float a_div = (float(sqrt(v_a.x * v_a.x + v_a.y * v_a.y + v_a.z * v_a.z)));
        Vertex v_aa_r;
        v_aa_r.x = (v_a.x / a_div) * radius;
        v_aa_r.y = (v_a.y / a_div) * radius;
        v_aa_r.z = (v_a.z / a_div) * radius;

        float b_div = (float(sqrt(v_b.x * v_b.x + v_b.y * v_b.y + v_b.z * v_b.z)));
        Vertex v_bb_r;
        v_bb_r.x = (v_b.x / b_div) * radius;
        v_bb_r.y = (v_b.y / b_div) * radius;
        v_bb_r.z = (v_b.z / b_div) * radius;

        float c_div = (float(sqrt(v_c.x * v_c.x + v_c.y * v_c.y + v_c.z * v_c.z)));
        Vertex v_cc_r;
        v_cc_r.x = (v_c.x / c_div) * radius;
        v_cc_r.y = (v_c.y / c_div) * radius;
        v_cc_r.z = (v_c.z / c_div) * radius;

        //After normalization the triangles are printed on screen. 
        C.addTriangle(v_aa_r, v_bb_r, v_cc_r);
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
void makeSphere( Canvas &C , float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices < 1 )
        slices = 1;
    else if (slices > 5)
        slices = 5;

    if( stacks < 3 )
        stacks = 3;
    
    // Define all required vertices
    Vertex v_r_1_0, v_r_n1_0;
    Vertex v_1_0_r, v_1_0_nr;
    Vertex v_nr_1_0, v_nr_n1_0;
    Vertex v_n1_0_nr, v_n1_0_r;
    Vertex v_0_r_1, v_0_r_n1;
    Vertex v_0_nr_n1, v_0_nr_1;

    v_r_1_0.x = radius;
    v_r_1_0.y = 1;
    v_r_1_0.z = 0;

    v_r_n1_0.x = radius;
    v_r_n1_0.y = -1;
    v_r_n1_0.z = 0;

    v_1_0_r.x = 1;
    v_1_0_r.y = 0;
    v_1_0_r.z = radius;

    v_1_0_nr.x = 1;
    v_1_0_nr.y = 0;
    v_1_0_nr.z = -radius;

    v_nr_1_0.x = -radius;
    v_nr_1_0.y = 1;
    v_nr_1_0.z = 0;

    v_nr_n1_0.x = -radius;
    v_nr_n1_0.y = -1;
    v_nr_n1_0.z = 0;

    v_n1_0_nr.x = -1;
    v_n1_0_nr.y = 0;
    v_n1_0_nr.z = -radius;

    v_n1_0_r.x = -1;
    v_n1_0_r.y = 0;
    v_n1_0_r.z = radius;

    v_0_r_1.x = 0;
    v_0_r_1.y = radius;
    v_0_r_1.z = 1;
    
    v_0_r_n1.x = 0;
    v_0_r_n1.y = radius;
    v_0_r_n1.z = -1;

    v_0_nr_n1.x = 0 ;
    v_0_nr_n1.y = -radius;
    v_0_nr_n1.z = -1;

    v_0_nr_1.x = 0;
    v_0_nr_1.y = -radius;
    v_0_nr_1.z = 1;

    // Call function to draw slices one by one
    drawSlices(C, radius, slices, v_0_r_1, v_1_0_r, v_r_1_0);
    drawSlices(C, radius, slices, v_r_n1_0, v_1_0_nr, v_1_0_r);

    drawSlices(C, radius, slices, v_r_1_0, v_1_0_r, v_1_0_nr);
    drawSlices(C, radius, slices, v_nr_1_0, v_n1_0_nr, v_n1_0_r);
    drawSlices(C, radius, slices, v_nr_n1_0, v_n1_0_r, v_n1_0_nr);

    drawSlices(C, radius, slices, v_0_r_1, v_nr_1_0, v_n1_0_r);
    drawSlices(C, radius, slices, v_0_r_1, v_r_1_0, v_nr_1_0);
    drawSlices(C, radius, slices, v_0_r_1, v_n1_0_r, v_0_nr_1);
    drawSlices(C, radius, slices, v_0_r_1, v_0_nr_1, v_1_0_r);

    drawSlices(C, radius, slices, v_0_r_n1, v_n1_0_nr, v_nr_1_0);
    drawSlices(C, radius, slices, v_0_r_n1, v_r_1_0, v_1_0_nr);

    drawSlices(C, radius, slices, v_0_nr_n1, v_nr_n1_0, v_n1_0_nr);
    drawSlices(C, radius, slices, v_0_nr_n1, v_1_0_nr, v_r_n1_0);
    drawSlices(C, radius, slices, v_0_nr_1, v_n1_0_r, v_nr_n1_0);
    drawSlices(C, radius, slices, v_0_nr_1, v_r_n1_0, v_1_0_r);
    drawSlices(C, radius, slices, v_0_nr_n1, v_r_n1_0, v_nr_n1_0);
    
    drawSlices(C, radius, slices, v_0_r_n1, v_nr_1_0, v_r_1_0);
    drawSlices(C, radius, slices, v_0_r_n1, v_1_0_nr, v_0_nr_n1);
    drawSlices(C, radius, slices, v_0_r_n1, v_0_nr_n1, v_n1_0_nr);
    drawSlices(C, radius, slices, v_0_nr_1, v_nr_n1_0, v_r_n1_0);
}