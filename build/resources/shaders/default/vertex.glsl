#version 150 core
 
in vec4 iPos;
in vec3 iNorm;
in vec2 iUV;

uniform vec2 ViewportSize;

uniform mat4 Transform;
uniform mat4 ViewProjection;

out vec3 vNorm;
out vec2 Reslotion;
out vec2 vUV;



void main()
{
	
	vec4 Pos = iPos;
	Pos *= Transform * ViewProjection;
	//fixing the strexh
	// vec2 ratio= ViewportSize/max(ViewportSize.x, ViewportSize.y);
	// Pos.x *= ratio.y;
	// Pos.y *= ratio.x;
	
	gl_Position = Pos;

	vNorm = iNorm;
	Reslotion = ViewportSize;
	vUV = iUV;
}
