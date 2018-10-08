#include "stdafx.h"

#include "Game.h"
#include "Variables.h"

#include <vector>
#include <time.h>
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

int Game::loop()
{
	//Current sdl event
	SDL_Event event;

	/*------------------------
	Main game loop
	------------------------*/
	while (isRunning)
	{
		//Calculate deltaTime
		lastTime = tickTime;
		tickTime = SDL_GetTicks();
		deltaTime = (tickTime - lastTime);

		//Check for SDL events
		if (SDL_PollEvent(&event))
		{
			//Events found
			switch (event.type)
			{
				//Window closed
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:

				//Check individual keys by code (can be moved out into main switch statement if fewer keys need to be checked.)
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE: // Escape key
						isRunning = false;
						break;

					case SDLK_UP: // Arrow key up
						position.y += 0.05f;
						modelMatrix = glm::translate(position);
						break;

					case SDLK_DOWN: // Arrow key down
						position.y -= 0.05f;
						modelMatrix = glm::translate(position);
						break;

					case SDLK_RIGHT: // Arrow key right
						position.x += 0.05f;
						modelMatrix = glm::translate(position);
						break;

					case SDLK_LEFT: // Arrow key left
						position.x -= 0.05f;
						modelMatrix = glm::translate(position);
						break;

					case SDLK_q: // Rotate left
						modelMatrix = glm::rotate(modelMatrix, glm::radians(10), glm::vec3(0.0f, 0.0f, 10.0f));
						break;
					case SDLK_e: // Rotate right
						break;
				}
				break;
			}

			if (event.type == SDL_MOUSEWHEEL)
			{
				if (event.wheel.y > 0) // Scroll up
				{
					// Scale up the triangle
					modelMatrix = glm::scale(modelMatrix, glm::vec3(1.05f, 1.05f, 1.05f));
				}

				if (event.wheel.y < 0) // Scroll down
				{
					// Scale down the triangle
					modelMatrix = glm::scale(modelMatrix, glm::vec3(0.95f, 0.95f, 0.95f));
				}
			}
		}

		Game::render();
	}

	Game::clean();
	return 0;
}

int Game::initialiseSDL()
{
	// initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success \n";

		// Create a window
		mainWindow = SDL_CreateWindow(
			"SDL Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			variables::SCREEN_WIDTH,
			variables::SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
			);

		// if window succesful..
		if (mainWindow != 0) {
			std::cout << "Window creation success \n";

		}
		else {
			std::cout << "window failed \n";
			return false;
		}

	}
	else {
		std::cout << "SDL fail \n";
		return false;
	}

	isRunning = true;
	std::cout << "SDL init success \n";

	return 0;
}

int Game::initialiseGLEW()
{
	// Initialising GLEW
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation Failed", (char*)glewGetErrorString(error), NULL);
	}

	return 0;
}

bool Game::SetOpenGLAttributes()
{
	// Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Set our OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	return true;
}

int Game::initialise()
{
	//Initalise random seed
	std::srand(time(NULL));


	//Initalise the SDL components
	if (initialiseSDL() < 0)
	{
		std::cout << "SDL initalisation failed." << std::endl;
		return 1;
	}

	Game::SetOpenGLAttributes();

	// Initialise GLEW
	gl_Context = SDL_GL_CreateContext(mainWindow);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateContext Failed", SDL_GetError(), NULL);
		return 1;
	}
	Game::initialiseGLEW();
	return 0;
}

int Game::getVertex()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return 0;
}

int Game::getShaders()
{
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("vertex.glsl", "fragment.glsl");

	// Setting matrices to default
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	scaling = glm::vec3(1.0f, 1.0f, 1.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//translationMatrix = glm::translate(position);
	//scaleMatrix = glm::scale(scaling);
	//rotationMatrix = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * (rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * (rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	//modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	// Set Matrix Location
	modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");


	return 0;
}

void Game::render()
{
	// Update Game and Draw with OpenGL
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,			// attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,			// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalized?
		0,			// stride
		(void*)0	// array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 trangle
	glDisableVertexAttribArray(0);

	SDL_GL_SwapWindow(mainWindow);
}

void Game::clean()
{
	// Cleanup
	std::cout << "Cleaning SDL \n";
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	//Delete Context
	SDL_GL_DeleteContext(gl_Context);
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}
