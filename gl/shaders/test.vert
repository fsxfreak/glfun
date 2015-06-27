#version 330 core

layout (location = 0) in vec3 _position;
layout (location = 1) in vec3 _color;

out vec3 vertexColor;

void main()
{
	vertexColor = _color;
	gl_Position = vec4(_position, 1.0);
}