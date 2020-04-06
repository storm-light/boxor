#ifndef _GLOBALVAR_HPP_
#define _GLOBALVAR_HPP_

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "functions.hpp"

extern SDL_Window * win;
extern SDL_Renderer * rend;
extern SDL_Event event;
extern bool requestExit;

// extern b2World * world;
extern int alpha;  // scale from box2d units to SDL pixels

#endif
