#version 330 core

out vec4 color;

in vec4 vertexColourOut;

void main()
{
	color = vertexColourOut;
}