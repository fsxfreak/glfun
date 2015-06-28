#version 330 core

layout (location = 0) in vec3 _position;
layout (location = 1) in vec3 _color;

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertexColor = _color;
	gl_Position = projection * view * model * vec4(_position, 1.0);
}