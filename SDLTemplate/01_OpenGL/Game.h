#pragma once

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
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

private:
	SDL_Window* mainWindow = nullptr;
	SDL_GLContext gl_Context;
	GLuint VertexArrayID;
	GLuint vertexbuffer;

	//Initialise times
	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;

	bool isRunning = false;
};

