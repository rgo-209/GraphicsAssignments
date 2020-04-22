#version 150

// Phong fragment shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading computations
uniform vec4 ambientMaterialColor;
uniform vec4 diffuseMaterialColor;
uniform vec4 specularMaterialColor;
uniform vec4 ambientLightColor;
uniform vec4 lightSourceColor;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;
vec4 ambientReflectionParameter, diffuseReflectionParameter, specularReflectionParameter;

uniform vec3 lightSourceVector;
uniform vec3 normalVector;
uniform vec3 viewingDirVector;

vec3 lightSourceDir;
vec3 normalDir;
vec3 viewingDir;

// OUTGOING DATA
out vec4 finalColor;

void main()
{
    vec4 ambientReflectionParameter;
	vec4 diffuseReflectionParameter;
	vec4 specularReflectionParameter;

	vec3 finalNormalizedReflection;
	lightSourceDir = normalize(lightSourceVector - viewingDirVector);
	normalDir = normalize(normalVector);
	viewingDir = normalize(viewingDirVector);
	finalNormalizedReflection = normalize(reflect(lightSourceDir, normalDir));

	ambientReflectionParameter  = ambientLightColor				* 
								  ambientMaterialColor			*
								  ambientReflectionCoefficient;

	diffuseReflectionParameter  = diffuseMaterialColor			*
								  lightSourceColor				*
								  diffuseReflectionCoefficient  *
								  dot(normalize(lightSourceVector - viewingDirVector),normalDir);
	
	specularReflectionParameter = specularMaterialColor			* 
								  lightSourceColor				*
								  specularReflectionCoefficient *
								  pow(clamp(dot(finalNormalizedReflection,viewingDir), 0, 1), specularExponent);
	
   	finalColor = ambientReflectionParameter + 
				 diffuseReflectionParameter +
				 specularReflectionParameter;

}
