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
GLuint smileyID , frownyID;
GLint smileyImageTexture, frownyImageTexture;


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
//	if (smileyID != 0){
//		glActiveTexture(GL_TEXTURE0+0);
//		glBindTexture(GL_TEXTURE_2D, smileyID);
//	}
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
	Properties of the light source :
		Position = (0.0, 5.0, 2.0, 1.0)
		Color = (1.0, 1.0, 0.0, 1.0)
	*/
	float lightSourceColor[] = { 1.0, 1.0, 0.0, 1.0 };
	glUniform4fv(glGetUniformLocation(program, "lightSourceColor"), 1, lightSourceColor);

	float lightSourcePosition[] = { 0.0, 5.0, 2.0, 1.0 };
	glUniform4fv(glGetUniformLocation(program, "lightSourcePosition"), 1, lightSourcePosition);

	/*
	Reflective characteristics of the teapot and the quad :
		Ambient reflection coefficient(ka) = 0.5
		Diffuse reflection coefficient(kd) = 0.7
		Specular reflection coefficient(ks) = 1.0
		Specular exponent = 10.0
	*/
	float ambientReflectionCoefficient = 0.5;
	glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"), ambientReflectionCoefficient);

	float diffuseReflectionCoefficient = 0.7;
	glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"), diffuseReflectionCoefficient);

	float specularReflectionCoefficient = 1.0;
	glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), specularReflectionCoefficient);

	float specularExponent = 10.0;
	glUniform1f(glGetUniformLocation(program, "specularExponent"), specularExponent);

	/*
	Ambient light in the scene :
		Color = (0.5, 0.5, 0.5, 1.0)
	*/
	float ambientLightColor[] = { 0.5, 0.5, 0.5, 1.0 };
	glUniform4fv(glGetUniformLocation(program, "ambientLightColor"), 1, ambientLightColor);

	//Activating the shader program
	glUseProgram(program);
	
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, smileyID);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, frownyID);
	
	//Getting sampler variables location
	smileyImageTexture = glGetUniformLocation(program, "smileySampler");
	frownyImageTexture = glGetUniformLocation(program, "frownySampler");
	
	// smiley Image Texture unit 0
	glUniform1i(smileyImageTexture, 0);

	// frowny Image Texutre unit 2
	glUniform1i(frownyImageTexture, 2);

}