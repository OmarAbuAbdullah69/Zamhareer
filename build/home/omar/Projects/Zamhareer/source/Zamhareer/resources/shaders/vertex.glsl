#version 150
 
in vec3 iPos;
in vec3 iNorm;
in vec2 iUV;

void main()
{
    gl_Position = vec4(iPos, 1) ;
}
