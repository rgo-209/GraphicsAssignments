    //
//  Lighting
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Rahul Golhar
//
//  Simple class for setting up Phong illumination/shading.
//
//  This code can be compiled as either C or C++.
//

#include "Lighting.h"

// Add any global definitions and/or variables you need here.

///
// This function sets up the lighting, material, and shading parameters
// for the Phong shader.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpPhong( GLuint program )
{
	/*
	Material properties of the teapot :

		Ambient material color = (0.5, 0.1, 0.9, 1.0)
		Diffuse material color = (0.89, 0.0, 0.0, 1.0)
		Specular material color = (1.0, 1.0, 1.0, 1.0)
	*/
	glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"), 0.5f, 0.1f, 0.9f, 1.0f);

	glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"), 0.89f, 0.0f, 0.0f, 1.0f);

	glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 1.0, 1.0, 1.0, 1.0);

	/*
	Reflective characteristics of the teapot and the quad :

		Ambient reflection coefficient(ka) = 0.5
		Diffuse reflection coefficient(kd) = 0.7
		Specular reflection coefficient(ks) = 1.0
		Specular exponent = 10.0
	*/
	glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"), 0.5);

	glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"), 0.7);

	glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), 1.0);

	glUniform1f(glGetUniformLocation(program, "specularExponent"), 10.0);

	/*
	Properties of the light source :

		Position = (0.0, 5.0, 2.0, 1.0)
		Color = (1.0, 1.0, 0.0, 1.0)
	*/
	glUniform4f(glGetUniformLocation(program, "lightSourcePosition"), 0.0, 5.0, 2.0, 1.0);
	glUniform4f(glGetUniformLocation(program, "lightSourceColor"), 1.0, 1.0, 0.0, 1.0);

	/*
	Ambient light in the scene :

		Color = (0.5, 0.5, 0.5, 1.0)
	*/
	glUniform4f(glGetUniformLocation(program, "ambientLightColor"), 0.5, 0.5, 0.5, 1.0);

}
