//
//  Textures
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Rahul Golhar
//
//  Simple class for setting up texture mapping parameters.
//
//  This code can be compiled as either C or C++.
//

#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

#include "Textures.h"

// this is here in case you are using SOIL;
// if you're not, it can be deleted.
#include <SOIL.h>

#ifdef __cplusplus
using namespace std;
#endif

// Add any global definitions and/or variables you need here.
GLuint smileyID, frownyID;
GLint baseImageLocation, normalMapLocation, shadowMapLocation;

float lightSourcePositionFace[] = { 0.0, 5.0, 2.0, 1.0 };
float lightSourceColorFace[] = { 1.0, 1.0, 0.0, 1.0 };
float ambientLightColorFace[] = { 0.5, 0.5f, 0.5, 1.0 };



///
// This function loads texture data for the GPU.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
///
void loadTexture(void)
{
    //Loading the first texture
    smileyID = SOIL_load_OGL_texture(
        "smiley2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_TEXTURE_REPEATS
    );
    //Loading the second texture	
    frownyID = SOIL_load_OGL_texture(
        "frowny2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
        SOIL_FLAG_TEXTURE_REPEATS
    );
}

///
// This function sets up the parameters for texture use.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpTexture(GLuint program)
{
	/*
	Ambient light in the scene :

		Color = (0.5, 0.5, 0.5, 1.0)
	*/
	glUniform4fv(glGetUniformLocation(program, "ambientLightColorFace"), 1, ambientLightColorFace);

	/*
	Properties of the light source :

		Position = (0.0, 5.0, 2.0, 1.0)
		Color = (1.0, 1.0, 0.0, 1.0)
	*/
	glUniform4fv(glGetUniformLocation(program, "lightSourcePositionFace"), 1, lightSourcePositionFace);
	glUniform4fv(glGetUniformLocation(program, "lightSourceColorFace"), 1, lightSourceColorFace);


	/*
	Reflective characteristics of the teapot and the quad :

		Ambient reflection coefficient(ka) = 0.5
		Diffuse reflection coefficient(kd) = 0.7
		Specular reflection coefficient(ks) = 1.0
		Specular exponent = 10.0
	*/
	float ambientReflectionCoefficient = 0.5f;
	float diffuseReflectionCoefficient = 0.7f;
	float specularReflectionCoefficient = 1.0f;
	float specularExponent = 10.0f;

	glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"),
		ambientReflectionCoefficient);

	glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"),
		diffuseReflectionCoefficient);

	glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"),
		specularReflectionCoefficient);

	glUniform1f(glGetUniformLocation(program, "specularExponent"),
		specularExponent);


	//Start the shader
	glUseProgram(program);
	
	// For Smiley face
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, smileyID);

	// For Frowny face
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, frownyID);
	
	//Get the sampler variables
	baseImageLocation = glGetUniformLocation(program, "texture1");
	normalMapLocation = glGetUniformLocation(program, "texture2");
	
	// Texutre unit 0
	glUniform1i(baseImageLocation, 0);
	
	// Texutre unit 2
	glUniform1i(normalMapLocation, 2);
}