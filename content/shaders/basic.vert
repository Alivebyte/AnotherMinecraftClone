#version 150 core

in vec3 position;

void main()
{
	glPosition = vec4(position, 1.0);
}