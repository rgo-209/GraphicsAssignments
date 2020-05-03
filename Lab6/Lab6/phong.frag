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
	mat4 normalViewingMatrix = transpose(inverse (viewingMatrix));
	vec4 normalToCameraDir =viewingMatrix * vec4(normalDir, 0.0);	
	vec4 normalVector = normalize(normalToCameraDir);
	vec4 lightSourceVector = normalize(lightSourceDir-viewingDir);
	vec4 normalizedReflectionVector = normalize (reflect(-lightSourceVector, normalVector));
    vec4 viewingVector = normalize (-viewingDir);


	vec4 tempAmbientParameter  = ambientMaterialColor			*
								 ambientLightColor				*
								 ambientReflectionCoefficient;
	
	vec4 tempDiffuseParameter  = diffuseMaterialColor			*
								 lightSourceColor				*
								 diffuseReflectionCoefficient	*
								 dot(normalVector, lightSourceVector);

	vec4 tempSpecularParameter = ambientMaterialColor			*
								 lightSourceColor				*
								 specularReflectionCoefficient	*
		pow(max(0.0, dot(viewingVector,normalizedReflectionVector)),specularExponent);

   	finalColor = tempAmbientParameter + 
				 tempDiffuseParameter +
				 tempSpecularParameter;
}
