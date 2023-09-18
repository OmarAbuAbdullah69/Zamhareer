#version 150 core

in vec3 vnorm;

void main()
{
	gl_FragColor = vec4(vnorm, 1.0);
	// gl_FragColor = vec4(0.431, 0.282, 0.89, 1.0);
}
