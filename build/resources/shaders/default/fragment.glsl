#version 150 core

in vec3 vNorm;
in vec2 Reslotion;
in vec2 coord;

void main()
{
	gl_FragColor =  vec4(coord, 0.0, 1.0);
}
