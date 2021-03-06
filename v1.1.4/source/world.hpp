#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "SDL2/SDL.h"
#include "Box2D/Box2D.h"
#include "globalvar.hpp"

class World {

  private:

	b2World * world;
	
	float32 timeStep;      //the length of time passed to simulate (seconds)
	int32 velocityIterations;   //how strongly to correct velocity
	int32 positionIterations;   //how strongly to correct position

	// b2Body * bounds[4];
	b2Body * ground;
	b2FrictionJoint * fj;
	b2PrismaticJoint * pj1, * pj2;
	float k;  // friction constant

  public:
	
	World();
	~World();
	void Step();
	b2Body* CreateBody(b2BodyDef * bd);
	b2FrictionJoint * CreateFrictionJoint(b2Body * A, b2Body * B); // can add more parameters if specificity is needed later on, or can edit individual joint through returned pointer
	std::pair<b2PrismaticJoint *, b2PrismaticJoint *> CreatePrismaticJoints(b2Body * A, b2Body * B1, b2Body * B2);
	void render();
	b2Body* GetGround();
	void updateMaxForceAndTorque(float spd, float angSpd);	// this might not work since if multiple players, their spd, angSpd differs and there's only 1 world
};

#endif
