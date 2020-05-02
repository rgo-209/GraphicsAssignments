#version 150

// Phong fragment shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading computations
uniform vec4 lightSourcePosition;
uniform vec4 lightSourceColor;
uniform vec4 ambientLightColor;

uniform vec4 ambientMaterialColor;
uniform vec4 diffuseMaterialColor;
uniform vec4 specularMaterialColor;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;


in vec3 lightSourceDir;
in vec3 normalDir;
in vec3 viewingDir;

// OUTGOING DATA
out vec4 finalFragmentColor;

void main()
{
	vec3 normalVector = normalize(normalDir);
	vec3 lightSourceVector = normalize(lightSourceDir - normalDir);
	vec3 finalNormalizedReflection = normalize(reflect(lightSourceVector, normalVector));

	vec4 ambientReflectionParameter, diffuseReflectionParameter, specularReflectionParameter;

	ambientReflectionParameter  = ambientMaterialColor			*
								  ambientReflectionCoefficient	*
								  ambientLightColor				;

	diffuseReflectionParameter  = diffuseMaterialColor			*
								  diffuseReflectionCoefficient  *
								  dot(normalVector, lightSourceVector);


	specularReflectionParameter = specularMaterialColor			* 
								  specularReflectionCoefficient *
								  pow(max(0.0, dot(normalize (viewingDir),finalNormalizedReflection)),specularExponent);

   	finalFragmentColor = ambientReflectionParameter + 
						 diffuseReflectionParameter * lightSourceColor +
						 specularReflectionParameter;
}
