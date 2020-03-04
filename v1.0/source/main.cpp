#include <SDL2/SDL.h>
#include <iostream>
#include "globalvar.hpp"
#include "loop.hpp"
// #include "functions.hpp"

// global var definition
SDL_Window * win;
SDL_Renderer * rend;
SDL_Event event;
bool requestExit = 0;
// b2World * world;
int alpha = 20;

// function forward declaration
bool init();

int main()
{
	if (!init())
	{
		SDL_Quit();
		return 1;
	}

	Loop * gameLoop = new Loop();
	while (!requestExit) {
		
		gameLoop->handleEvents();
		gameLoop->update();
		gameLoop->render();
		
	}

	SDL_Delay(3000);  // remove this later
	gameLoop->~Loop();

	// clean up
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	
}
