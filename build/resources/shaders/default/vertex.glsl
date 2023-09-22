#version 150 core
 
in vec4 iPos;
in vec3 iNorm;
in vec2 iUV;

uniform vec2 ViewportSize;

out vec3 vNorm;
out vec2 Reslotion;
out vec2 coord;

void main()
{
	
	vec4 Pos = iPos;
	//fixing the strexh
	// vec2 ratio= ViewportSize/max(ViewportSize.x, ViewportSize.y);
	// Pos.x *= ratio.y;
	// Pos.y *= ratio.x;
	
	gl_Position = Pos;

	vNorm = iNorm;
	Reslotion = ViewportSize;
	coord = iUV;
}
