#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec4 vertexColour;

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix;

out vec4 vertexColourOut;

void main()
{
	vec4 modelVertexPosition = modelMatrix * vec4(vertexPos, 1.0f);

	mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

	vec4 mvpPosition = mvpMatrix * vec4(vertexPos, 1.0f);

	vertexColourOut = vertexColour;
	gl_Position = modelVertexPosition; // later will be mvpPosition
}