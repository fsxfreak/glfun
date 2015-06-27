#version 330 core

in vec3 color;
out vec4 frag_color;

void main()
{
	frag_color = vec4(color.x, color.y, color.z, 1.0f);
}