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
	//Initalise random seed
	std::srand(time(NULL));


	//Initialise times
	float lastTime = 0;
	float tickTime = 0;
	float deltaTime = 0;


	//Initalise the SDL components
	if (initialiseSDL() < 0)
	{
		std::cout << "SDL initalisation failed." << std::endl;
		return -1;
	}


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
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
				break;
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
			SDL_WINDOW_SHOWN
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

void Game::render()
{

}

void Game::clean()
{
	std::cout << "Cleaning SDL \n";
	SDL_DestroyWindow(mainWindow);
	IMG_Quit();
	SDL_Quit();
}
