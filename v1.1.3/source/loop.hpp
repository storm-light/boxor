#ifndef _LOOP_HPP_
#define _LOOP_HPP_

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"
#include "globalvar.hpp"
#include "player.hpp"
#include "world.hpp"

class P1;
class P2;
class World;

class Loop {
	
  private:
	
	Player * p1, * p2;
	World * world;
	
  public:

	Loop();
	~Loop();

	void handleEvents();
    void update();
    void render();
	void reset();  // when a player gets knocked out
	
};
	
#endif
