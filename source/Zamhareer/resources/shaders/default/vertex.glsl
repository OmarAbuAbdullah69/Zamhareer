#version 150 core
 
in vec4 iPos;
in vec3 iNorm;
in vec2 iUV;

void main()
{
    gl_Position = iPos;
}
