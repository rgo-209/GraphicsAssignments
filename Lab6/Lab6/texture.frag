#version 150

// Texture mapping vertex shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA
in vec2 finalVertexCoordinates;
uniform sampler2D texture1;
uniform sampler2D texture2;

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading and texture mapping computations
uniform vec4 lightSourcePositionFace;
uniform vec4 lightSourceColorFace;
uniform vec4 ambientLightColorFace;

//uniform vec4 ambientMaterialColor;
//uniform vec4 diffuseMaterialColor;
//uniform vec4 specularMaterialColor;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;


in vec3 lightSourceDir;
in vec3 normalDir;
in vec3 viewingDir;

// OUTGOING DATA

out vec4 finalColor;

// Variables for the smiley and the frowny face
vec4 ambientReflectionParameter;
vec4 diffuseReflectionParameter;
vec4 specularReflectionParameter;

vec3 normalVector;
vec3 lightSourceVector;
vec3 viewingVector;
vec3 finalNormalizedReflection;

vec4 smileyFace;
vec4 frownyFace;


void main()
{
    smileyFace		= texture2D(texture1, finalVertexCoordinates);
	frownyFace 		= texture2D(texture2, finalVertexCoordinates);

	normalVector		= normalize(normalDir);
	lightSourceVector   = normalize(lightSourceDir - normalDir);
	viewingVector       = normalize(viewingDir);
	finalNormalizedReflection = normalize(reflect(lightSourceVector, normalVector));

	vec4 tempAmbientParameter  = ambientLightColorFace			*
								 ambientReflectionCoefficient;
	
	vec4 tempDiffuseParameter  = lightSourceColorFace			*
								 diffuseReflectionCoefficient	*
								 dot(normalVector, lightSourceVector);

	vec4 tempSpecularParameter = specularReflectionCoefficient	*
								 lightSourceColorFace			*
								 pow(max(0.0, dot(viewingVector,finalNormalizedReflection))
								 ,specularExponent);
	if(gl_FrontFacing)
	{
		// Showing smiley face for front side
		ambientReflectionParameter  = tempAmbientParameter	*	smileyFace;
		diffuseReflectionParameter  = smileyFace			*	tempDiffuseParameter; 
		specularReflectionParameter = smileyFace			*	tempSpecularParameter;      
	}
	else
	{		
		// Showing frowny face for the back side
		ambientReflectionParameter  = tempAmbientParameter	*	frownyFace;
		diffuseReflectionParameter  = frownyFace			*	tempDiffuseParameter;
		specularReflectionParameter = frownyFace			*	tempSpecularParameter;	
	}
	//Setting the final color
	finalColor = ambientReflectionParameter  + diffuseReflectionParameter + specularReflectionParameter;
}
