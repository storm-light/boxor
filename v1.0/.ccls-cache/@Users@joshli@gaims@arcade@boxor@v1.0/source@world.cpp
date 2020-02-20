#include "world.hpp"

World::World() {
	
	b2Vec2 gravity = b2Vec2(0.0f, -0.0f);
	world = new b2World(gravity);
	
	timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
	velocityIterations = 8;   //how strongly to correct velocity
	positionIterations = 3;   //how strongly to correct position
	
	// need to create a b2body for ground
	b2BodyDef bd;
	b2FixtureDef fd;
	b2EdgeShape esh;
	fd.shape = &esh;
	fd.density = 1;
	
	bd.type = b2_staticBody;
	bd.position.Set(0, -5);  // below the origin some distance
	ground = world->CreateBody(&bd);
	
	esh.Set(b2Vec2(-10, 0), b2Vec2(10,0));
	fd.shape = &esh;
	ground->CreateFixture(&fd);
}

World::~World() {
	delete world;
}

void World::Step()
{
	world->Step(timeStep, velocityIterations, positionIterations);	
}

b2Body* World::CreateBody(b2BodyDef * bd)
{
	return world->CreateBody(bd);
}

void World::CreateFrictionJoint(b2Body * A, b2Body * B)
{
	b2FrictionJointDef fjd;
	fjd.maxForce = 9;
	fjd.maxTorque = 3;
	fjd.bodyA = A;
	fjd.bodyB = B;
	fjd.localAnchorA.Set(0.f,0.f); 
	fjd.localAnchorB.Set(0.0f,0.0f); 
	fjd.collideConnected = true;
	fj = (b2FrictionJoint *) world->CreateJoint(&fjd);
}

void World::updateMaxForceAndTorque(float spd, float angSpd)
{
	fj->SetMaxForce(pow(spd, 2) * k);
	fj->SetMaxTorque(pow(angSpd, 2) * k);
}

void World::render()
{
	SDL_SetRenderDrawColor(rend, 255,255,255,255);
	
	SDL_RenderDrawLine(rend, BoxToSDL(ground->GetPosition() - b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y, BoxToSDL(ground->GetPosition() + b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y);
	
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
	
}

b2Body* World::GetGround()
{
	return ground;
}
