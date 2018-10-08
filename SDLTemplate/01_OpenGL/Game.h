#pragma once

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <glm\glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"

class Game
{
public:
	Game();
	~Game();

	int loop();
	void render();
	void clean();
	int initialiseSDL();
	int initialiseGLEW();
	bool SetOpenGLAttributes();
	int initialise();
	int getVertex();
	int getShaders();

private:
	SDL_Window* mainWindow = nullptr;
	SDL_GLContext gl_Context;
	GLuint VertexArrayID;
	GLuint vertexbuffer;
	GLuint programID;
	GLuint modelMatrixLocation;
	glm::vec3 position;
	glm::mat4 modelMatrix;

	//Initialise times
	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;

	bool isRunning = false;
};

