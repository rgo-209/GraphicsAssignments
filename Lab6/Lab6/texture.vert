#version 150

// Texture mapping vertex shader
//
// Contributor:  Rahul Golhar

// INCOMING DATA
uniform vec4 lightSourcePosition;

// Vertex location (in model space)
in vec4 vPosition;

// Normal vector at vertex (in model space)
in vec3 vNormal;

// Texture coordinate for this vertex
in vec2 vTexCoord;

// Model transformations
uniform vec3 theta;
uniform vec3 trans;
uniform vec3 scale;

// Camera parameters
uniform vec3 cPosition;
uniform vec3 cLookAt;
uniform vec3 cUp;

// View volume boundaries
uniform float left;
uniform float right;
uniform float top;
uniform float bottom;
uniform float near;
uniform float far;


// Here is where you should add the variables you need in order
// order to perform the vertex shader portion of the shading
// and texture mapping computations

// OUTGOING DATA
out vec3 normalDir;    
out vec4 lightSourceDir;
out vec4 viewingDir;
out mat4 viewingMatrix;
out vec2 finalVertexCoordinates;

// add all necessary variables for communicating with
// the fragment shader here

void main()
{
    // Compute the sines and cosines of each rotation about each axis
    vec3 angles = radians( theta );
    vec3 c = cos( angles );
    vec3 s = sin( angles );

    // Create rotation matrices
    mat4 rxMat = mat4( 1.0,  0.0,  0.0,  0.0,
                       0.0,  c.x,  s.x,  0.0,
                       0.0,  -s.x, c.x,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 ryMat = mat4( c.y,  0.0,  -s.y, 0.0,
                       0.0,  1.0,  0.0,  0.0,
                       s.y,  0.0,  c.y,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 rzMat = mat4( c.z,  s.z,  0.0,  0.0,
                       -s.z, c.z,  0.0,  0.0,
                       0.0,  0.0,  1.0,  0.0,
                       0.0,  0.0,  0.0,  1.0 );

    mat4 xlateMat = mat4( 1.0,     0.0,     0.0,     0.0,
                          0.0,     1.0,     0.0,     0.0,
                          0.0,     0.0,     1.0,     0.0,
                          trans.x, trans.y, trans.z, 1.0 );

    mat4 scaleMat = mat4( scale.x,  0.0,     0.0,     0.0,
                          0.0,      scale.y, 0.0,     0.0,
                          0.0,      0.0,     scale.z, 0.0,
                          0.0,      0.0,     0.0,     1.0 );

    // Create view matrix
    vec3 nVec = normalize( cPosition - cLookAt );
    vec3 uVec = normalize( cross (normalize(cUp), nVec) );
    vec3 vVec = normalize( cross (nVec, uVec) );

    mat4 viewMat = mat4( uVec.x, vVec.x, nVec.x, 0.0,
                         uVec.y, vVec.y, nVec.y, 0.0,
                         uVec.z, vVec.z, nVec.z, 0.0,
                         -1.0*(dot(uVec, cPosition)),
                         -1.0*(dot(vVec, cPosition)),
                         -1.0*(dot(nVec, cPosition)), 1.0 );

    // Create projection matrix
    mat4 projMat = mat4( (2.0*near)/(right-left), 0.0, 0.0, 0.0,
                         0.0, ((2.0*near)/(top-bottom)), 0.0, 0.0,
                         ((right+left)/(right-left)),
                         ((top+bottom)/(top-bottom)),
                         ((-1.0*(far+near)) / (far-near)), -1.0,
                         0.0, 0.0, ((-2.0*far*near)/(far-near)), 0.0 );

    // Transformation order:
    //    scale, rotate Z, rotate Y, rotate X, translate
    mat4 modelMat = xlateMat * rxMat * ryMat * rzMat * scaleMat;
    mat4 modelViewMat = viewMat * modelMat;

    // Here is where you should all all your code to perform the
    // vertex shader portion of your lighting and shading work
    //
    // remember that transformation of the surface normal should not
    // include translations; see
    // http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
    // for a discussion.  normal transformation should be done using the
    // inverse transpose of the upper-left 3x3 submatrix of the modelView
    // matrix.
    
    //Add the vertex coordinates
    finalVertexCoordinates = vTexCoord;
    
    // Get viewing direction vector
    viewingDir = modelViewMat * vPosition;
    // Get light source direction vector
	lightSourceDir = viewMat * lightSourcePosition;
    // Get normal direction vector
	normalDir = vNormal;
    // Get viewing transform matrix
	viewingMatrix = modelViewMat;

    // Transform the vertex location into clip space
    gl_Position =  projMat * viewMat  * modelMat * vPosition;
}