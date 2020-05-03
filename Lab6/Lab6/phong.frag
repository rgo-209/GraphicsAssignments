#version 150

// Phong fragment shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA
in vec4 lightSourceDir;
in vec3 normalDir;
in vec4 viewingDir;
in mat4 viewingMatrix;

// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading computations

uniform vec4 ambientMaterialColor;
uniform vec4 diffuseMaterialColor;
uniform vec4 specularMaterialColor;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;

uniform vec4 colorLightSource;
uniform vec4 ambientLightColor;

uniform vec4 lightSourcePosition;
uniform vec4 lightSourceColor;

// OUTGOING DATA
out vec4 finalColor;

void main()
{
	vec4 normalToCameraDir = viewingMatrix * vec4(normalDir, 0.0);	
	// N
	vec4 normalVector = normalize(normalToCameraDir);
	// L
	vec4 lightSourceVector = normalize(lightSourceDir-viewingDir);
	// R
	vec4 normalizedReflectionVector = normalize (reflect(-lightSourceVector, normalVector));
    // V
	vec4 viewingVector = normalize (-viewingDir);

	//Ambient Reflection = ambient Material Color * ambient Light Color * ambient Reflection Coefficient
	vec4 tempAmbientParameter  = ambientMaterialColor			*
								 ambientLightColor				*
								 ambientReflectionCoefficient;
	
	//Diffuse Reflection  = diffuse Material Color			* light Source Color * 
	//						diffuse Reflection Coefficient	* (N.L)
	vec4 tempDiffuseParameter  = diffuseMaterialColor			*
								 lightSourceColor				*
								 diffuseReflectionCoefficient	*
								 dot(normalVector, lightSourceVector);

	//vec4 tempSpecularParameter = specular Material Color			* light Source Color	*
	//							   specularReflectionCoefficient	* max(0.0, V.R)^specularExponent;
	vec4 tempSpecularParameter = specularMaterialColor			*
								 lightSourceColor				*
								 specularReflectionCoefficient	*
		pow(max(0.0, dot(viewingVector,normalizedReflectionVector)),specularExponent);
	
	// Final color = ambient color + diffuse color + specular color
   	finalColor = tempAmbientParameter + 
				 tempDiffuseParameter +
				 tempSpecularParameter;
}
