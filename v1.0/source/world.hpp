#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <SDL2/SDL.h>
#include "Box2D/Box2D.h"
#include "globalvar.hpp"

class World {

  private:

	b2World * world;
	
	float32 timeStep;      //the length of time passed to simulate (seconds)
	int32 velocityIterations;   //how strongly to correct velocity
	int32 positionIterations;   //how strongly to correct position

	b2Body * ground;
	b2FrictionJoint * fj;
	float k;  // friction constant

  public:
	
	World();
	~World();
	void Step();
	b2Body* CreateBody(b2BodyDef * bd);
	void CreateFrictionJoint(b2Body * A, b2Body * B);
	void render();
	b2Body* GetGround();
	void updateMaxForceAndTorque(float spd, float angSpd);	// this might not work since if multiple players, their spd, angSpd differs and there's only 1 world
};

#endif
