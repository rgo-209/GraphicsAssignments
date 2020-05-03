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
uniform sampler2D frownySampler;

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
	// Getting smiley texture
	vec4 smileyFaceColor	= texture2D(smileySampler, finalVertexCoordinates);
	
	// Getting frowny texture
	vec4 frownyFaceColor 	= texture2D(frownySampler, finalVertexCoordinates);

    vec4 normalToCameraDir = viewingMatrix * vec4(normalDir, 0.0);
    
	// N
	vec4 normalVector = normalize(normalToCameraDir);
	// L
	vec4 lightSourceVector = normalize(lightSourceDir-viewingDir);
	// R
	vec4 normalizedReflectionVector = normalize (reflect(-lightSourceVector, normalVector));
    // V
	vec4 viewingVector = normalize (-viewingDir);


	//Ambient Reflection = Material Color(later) * ambient Light Color * ambient Reflection Coefficient
	vec4 tempAmbientParameter  = ambientLightColor				*
								 ambientReflectionCoefficient;
	
	//Diffuse Reflection  = Material Color(later)			* light Source Color * 
	//						diffuse Reflection Coefficient	* (N.L)
	vec4 tempDiffuseParameter  = lightSourceColor				*
								 diffuseReflectionCoefficient	*
								 dot(normalVector, lightSourceVector);

	//vec4 tempSpecularParameter = Material Color(later)			* light Source Color			*
	//							   specularReflectionCoefficient	* max(0.0, V.R)^specularExponent;
	vec4 tempSpecularParameter = lightSourceColor				*
								 specularReflectionCoefficient	*
		pow(max(0.0, dot(viewingVector,normalizedReflectionVector)),specularExponent);

	if(gl_FrontFacing){
		// For front side show smiley
		tempAmbientParameter	= tempAmbientParameter	* smileyFaceColor;
		tempDiffuseParameter	= tempDiffuseParameter	* smileyFaceColor;
		tempSpecularParameter	= tempSpecularParameter * smileyFaceColor;
	}
	else{
		// For back side show forwny
		tempAmbientParameter	= tempAmbientParameter	* frownyFaceColor;
		tempDiffuseParameter	= tempDiffuseParameter	* frownyFaceColor;
		tempSpecularParameter	= tempSpecularParameter * frownyFaceColor;
	}

	// Final color = ambient color + diffuse color + specular color
	finalFragColor = tempAmbientParameter	+
					 tempDiffuseParameter	+
					 tempSpecularParameter;
}
