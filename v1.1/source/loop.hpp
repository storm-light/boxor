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
	
	// b2Vec2 gravity;
	
	// float32 timeStep;      //the length of time passed to simulate (seconds)
	// int32 velocityIterations;   //how strongly to correct velocity
	// int32 positionIterations;   //how strongly to correct position
	
	Player * p1, * p2;
	World * world;
	// b2Body * ground;
	
  public:

	Loop();
	~Loop();

	void handleEvents();
    void update();
    void render();
	
};
	
#endif
