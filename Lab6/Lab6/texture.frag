#version 150

// Texture mapping vertex shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA
in vec3 normalDir;    
in vec4 lightSourceDir;
in vec4 viewingDir;
in mat4 viewingMatrix;
in vec2 finalVertexCoordinates;


// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading and texture mapping computations

//uniform sampler2D texture2;
uniform sampler2D smileySampler;

//uniform vec4 lightSourcePosition;
uniform vec4 lightSourceColor;
uniform vec4 ambientLightColor;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;


// OUTGOING DATA
out vec4 finalFragColor;

void main()
{

	vec4 basicSmileyColor =  texture( smileySampler, finalVertexCoordinates );

    mat4 normalmatrix = transpose(inverse (viewingMatrix));

    vec4 normalToCameraDir = viewingMatrix * vec4(normalDir, 0.0);
    vec4 normalVector = normalize(normalToCameraDir);
	vec4 lightSourceVector = normalize(lightSourceDir-viewingDir);
	vec4 normalizedReflectionVector = normalize (reflect(-lightSourceVector, normalVector));
    vec4 viewingVector = normalize (-viewingDir);

	vec4 tempAmbientParameter  = basicSmileyColor				*
								 ambientLightColor				*
								 ambientReflectionCoefficient;
	
	vec4 tempDiffuseParameter  = basicSmileyColor				*
								 lightSourceColor				*
								 diffuseReflectionCoefficient	*
								 dot(normalVector, lightSourceVector);

	vec4 tempSpecularParameter = basicSmileyColor				*
								 lightSourceColor				*
								 specularReflectionCoefficient	*
		pow(max(0.0, dot(viewingVector,normalizedReflectionVector)),specularExponent);

	finalFragColor = tempAmbientParameter	+
					 tempDiffuseParameter	+
					 tempSpecularParameter;
}
