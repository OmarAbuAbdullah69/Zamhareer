#version 150 core
 
in vec4 iPos;
in vec3 iNorm;
in vec2 iUV;

out vec3 vnorm;

void main()
{
    gl_Position = iPos;
	vnorm = iNorm;
}
