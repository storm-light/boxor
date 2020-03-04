#include <SDL2/SDL.h>
#include "globalvar.hpp"
#include <iostream>

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Init error: " << SDL_GetError() << std::endl;
		return false;
	}
	// creating window 
	win = SDL_CreateWindow("BOXOR",
						   SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED,
						   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    // fullscreen!
    SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if (!win)
	{
		std::cout << "Window init error: " << SDL_GetError() << std::endl;
		return false;
	}
	// creating renderer
	Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
	rend = SDL_CreateRenderer(win, -1, flags);

	if (!rend)
	{
		std::cout << "Renderer init error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
		return false;
	}

    // gets the fullscreen window dimensions
	int winW, winH;
    SDL_GetRendererOutputSize(rend, &winW, &winH); 
	std::cout << "width: " << winW << " and height: " << winH << std::endl;

	
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );	// anti-aliasing?

	return true;
}

b2Vec2 BoxToSDL(b2Vec2 in)
{
	return b2Vec2(WINDOW_WIDTH/2 + alpha * in.x, WINDOW_HEIGHT/2 - alpha * in.y);
}
