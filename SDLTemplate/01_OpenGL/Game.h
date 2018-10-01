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

private:
	SDL_Window* mainWindow = nullptr;
	SDL_GLContext gl_Context = SDL_GL_CreateContext(mainWindow);
	GLuint VertexArrayID;
	GLuint vertexbuffer;

	bool isRunning = true;
};

