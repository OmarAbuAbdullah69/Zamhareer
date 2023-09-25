#version 150 core

in vec3 vNorm;
in vec2 Reslotion;
in vec2 vUV;

uniform sampler2D Albedo;

void main()
{
	vec4 color =  texture2D(Albedo, vUV);
	gl_FragColor = color;
}
