//
// Vertex shader for the transformation assignment
//
// Created by Warren R. Carithers 2016/04/22.
//
// Contributor:  Rahul Golhar
//

#version 140

// attribute:  vertex position
in vec4 vPosition;

// add other global shader variables to hold the
// parameters your application code is providing
// add other global shader variables to hold the
// parameters your application code is providing
//Vectors 
uniform vec3 eye, look, upparameter, scale, rotate, translate;
//Variables
uniform float l, r, f, n, t, b, prjTyp;


void main()
{
    // By default, no transformations are performed.
    gl_Position =  vPosition;

    // For storing the projection matrix. 
	mat4 projectionMatrix;

	if(prjTyp ==1.0)
	{
		// Frustum projection
		// | 2*n/r-l,		0,		r+l/r-l,			0	  |
		// |	0,		2*n/t-b,	t+b/t-b,			0	  |
		// |	0,			0,	  -(f+n)/f-n,	(-2*f*n)/f-n  |
		// |	0,			0,		 -1,				0	  |

		projectionMatrix = mat4((2.0*n/(r-l)),			0,            0,              0,
									  0,		(2.0*n/(t-b)),		  0,              0,
								(r+l)/(r-l),	  (t+b)/(t-b),	-(f+n)/(f-n),		 -1,
									  0,				0,     -2.0*f*n/(f-n),		  0);
	}
	else
	{
		// Orthographic projection
		// | 2/(r-l),		0,			0,		-(r+l)/(r-l)  |
		// |	0,		2/(t-b),		0,		-(t+b)/(t-b)  |
		// |	0,			0,		-2/(f-n),	-(f+n)/(f-n)  |
		// |	0,			0,			0,			 1		  |
		projectionMatrix = mat4((2.0/(r-l)),       0,             0,            0,
								0,        (2.0/(t-b)),        0,            0,
								0,             0,        -2.0/(f-n),		   0,
							-(r+l)/(r-l), -(t+b)/(t-b),  -(f+n)/(f-n),	   1);
	}
	
	// Getting u,v and n vector by normalization
	vec3 n = normalize(eye - look);
	vec3 u = normalize(cross(upparameter, n));
	vec3 v = cross(n, u);

	mat4 viewingMatrix ;
	// Camera Transformation
	// |	ux,		uy,		uz,		-1*(u*eyepoint) |	
	// |	vx,		vy,		vz,		-1*(v*eyepoint) |	
	// |	nx,		ny,		nz,		-1*(n*eyepoint) |	
	// |	 0,		0,		 0,			1			|	

	viewingMatrix = mat4(	u.x,				v.x,				n.x,			0.0,
							u.y,				v.y,				n.y,			0.0,
							u.z,				v.z,				n.z,			0.0,
						-1.0 * dot(u, eye), -1.0 * dot(v, eye), -1.0 * dot(n, eye), 1.0);
	
	mat4 translationMatrix;
	// Translation Matrix
	// |	1.0,	0.0,	0.0,	0.0	|	
	// |	0.0,	1.0,	0.0,	0.0	|	
	// |	0.0,	0.0,	1.0,	0.0	|	
	// |	t.x,	t.x,	t.z,	1.0	|
	translationMatrix = mat4(	1.0,			0.0,			0.0,		0.0,
								0.0,			1.0,			0.0,		0.0,
								0.0,			0.0,			1.0,		0.0,
							translate.x,	translate.x,	translate.z,	1.0);

	mat4 scaleMatrix;
	// Scaling Matrix
	// |	s.x,	0.0,	0.0,	0.0	|	
	// |	0.0,	s.y,	0.0,	0.0	|	
	// |	0.0,	0.0,	s.z,	0.0	|	
	// |	0.0,	0.0,	0.0,	1.0	|
	scaleMatrix = mat4(			scale.x,	  0.0,		0.0,		0.0,
								  0.0,		scale.y,	0.0,		0.0,
								  0.0,		  0.0,	   scale.z,		0.0,
								  0.0,		  0.0,		0.0,		1.0);

	mat4 rotationMatrix;

	vec3 angle = radians(rotate), cosV = cos(angle),sinV = sin(angle);

	// X Rotation matrix
	// |	1.0,	0.0,	 0.0,	0.0 |	
	// |	0.0,   cosV.x,	sinV.x,	0.0 |	
	// |	0.0,  -sinV.x,  cosV.x,	0.0 |	
	// |	0.0,	0.0,	 0.0,	1.0 |	
	mat4 xRotationMatrix = mat4(  1.0,		0.0,		 0.0,		0.0,
								  0.0,	   cosV.x,		sinV.x,		0.0,
								  0.0,	  -sinV.x,		cosV.x,		0.0,
								  0.0,		0.0,		 0.0,		1.0);

	// Y Rotation matrix
	// |	cosV.y,	 0.0,   -sinV.y,	0.0 |	
	// |	  0.0,   1.0,		0.0,	0.0 |	
	// |	sinV.y,	 0.0,	 cosV.y,	0.0 |	
	// |	  0.0,	 0.0,		0.0,	1.0 |	
	mat4 yRotationMatrix = mat4( cosV.y,	0.0,		-sinV.y,	0.0,
								  0.0,		1.0,		  0.0,		0.0,
								 sinV.y,	0.0,		cosV.y,		0.0,
								  0.0,		0.0,		  0.0,		1.0);

	// Z Rotation matrix
	// |	cosV.z,		sinV.z,  0.0,	0.0 |	
	// |   -sinV.z,		cosV.z,	 0.0,	0.0 |	
	// |	  0.0,		0.0,	 1.0,	0.0 |	
	// |	  0.0,		0.0,	0.0,	1.0 |	
	mat4 zRotationMatrix = mat4( cosV.z,   sinV.z,		  0.0,		0.0,
								 -sinV.z,  cosV.z,		  0.0,		0.0,
								  0.0,		0.0,		  1.0,		0.0,
								  0.0,		0.0,		  0.0,		1.0);

	// Rotation matrix  = Z Rotation Matrix * Y Rotation Matrix * X Rotation Matrix
	rotationMatrix = zRotationMatrix * yRotationMatrix * xRotationMatrix;

	// final object postion = projection Matrix * viewingMatrix 
	//						* translationMatrix * rotationMatrix * scaleMatrix 
	//						* vPosition;
	
	gl_Position = projectionMatrix * viewingMatrix * 
				translationMatrix * rotationMatrix * scaleMatrix *
				vPosition;
	
}
