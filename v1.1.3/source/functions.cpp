#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "globalvar.hpp"
#include <iostream>
#include <string>

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Init error: " << SDL_GetError() << std::endl;
		return false;
	}
	
    if (TTF_Init() != 0)
    {
        std::cout << "TTF Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
	
	// creating window 
	win = SDL_CreateWindow("BOXOR",
						   SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED,
						   WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    // fullscreen!
    // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
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

int BoxToSDL(float in)
{
	return alpha * in;
}

void titlescreen()
{

    int quit = 0;
    int alpha = 0;
    int increasing = 1;
    // unsigned int lastTime, currentTime;
    while (1)
    {
        SDL_SetRenderDrawColor(rend, 0,0,0,255);
        SDL_RenderClear(rend);
        SDL_SetRenderDrawColor(rend, 255,255,255,255);
        renderText("B0X0R", "UbuntuMono.ttf", 100, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 70);
        alphaText("Press Any Key", "UbuntuMono.ttf", 30, WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 50, alpha);

        // alpha mod of "press any key" texture
        if (increasing)
            alpha += 4;
        else
            alpha -= 4;

        if (0 > alpha || alpha > 255)
        {
            if (increasing)
            {
                increasing = 0;
                alpha = 255;
            }
            else
            {
                increasing = 1;
                alpha = 0;
            }
        }

        SDL_RenderPresent(rend);
        SDL_Delay(1000/60);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
                quit = 1;
        }

        if (quit)
            break;
    }

}

void alphaText(std::string message, std::string fontFile, int fontSize, int x, int y, int a)
{
    /* opens font */
    TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == 0)
    {
        std::cout << "TTF OPENfont: " << SDL_GetError() << std::endl;
    }

    /* render surface first with TTF_RenderText then create a texture for the surface */
	SDL_Color white; white.r = 255; white.g = 255; white.b = 255; white.a = 255; 
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), white);
    if (surf == 0)
    {
        TTF_CloseFont(font);
        std::cout << "TTF RenderText: " << SDL_GetError() << std::endl;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
	if (texture == NULL){
        std::cout << "Create Texture : " << SDL_GetError() << std::endl;
	}

    SDL_Rect d;
    SDL_QueryTexture(texture, NULL, NULL, &d.w, &d.h);
    if (x == -1)
    {
        d.x = (WINDOW_WIDTH - d.w) / 2;
    }
    else
        d.x = x - d.w / 2;
    d.y = y - d.h / 2;

    SDL_SetTextureAlphaMod(texture, a);
    SDL_RenderCopy(rend, texture, NULL, &d);

    /* frees stuff up */
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture); // fucking TwinkleBear Dev FUCK HIM
	TTF_CloseFont(font);
}

void renderText(std::string message, std::string fontFile, int fontSize, int x, int y)
{
    /* opens font */
    TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == 0)
    {
        std::cout << "TTF OPENfont: " << SDL_GetError() << std::endl;
    }

    /* render surface first with TTF_RenderText then create a texture for the surface */
	SDL_Color white; white.r = 255; white.g = 255; white.b = 255; white.a = 255; 
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), white);
    if (surf == 0)
    {
        TTF_CloseFont(font);
        std::cout << "TTF RenderText: " << SDL_GetError() << std::endl;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
	if (texture == NULL){
        std::cout << "Create Texture : " << SDL_GetError() << std::endl;
	}

    SDL_Rect d;
    SDL_QueryTexture(texture, NULL, NULL, &d.w, &d.h);
    if (x == -1)
    {
        d.x = (WINDOW_WIDTH - d.w) / 2;
    }
    else
        d.x = x - d.w / 2;
    d.y = y - d.h / 2;
    SDL_RenderCopy(rend, texture, NULL, &d);

    /* frees stuff up */
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture); // fucking TwinkleBear Dev FUCK HIM
	TTF_CloseFont(font);
}

void renderScore()
{
	std::string s;
	s.append(std::to_string(p1Score));
	s.append(1, '-');
	s.append(std::to_string(p2Score));
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
	SDL_RenderClear(rend);
	SDL_SetRenderDrawColor(rend, 255,255,255,255);
	renderText(s, "UbuntuMono.ttf", 100, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	SDL_RenderPresent(rend);
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
	SDL_Delay(2000);
}
