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
	// bd.position.Set(0, -5);  // below the origin some distance
	// ground = world->CreateBody(&bd);
	
	// esh.Set(b2Vec2(-10, 0), b2Vec2(10,0));
	// fd.shape = &esh;
	// ground->CreateFixture(&fd);

	// bounds = new b2Body[4];
	// top
	bd.position.Set(0, 15);
	bounds[0] = world->CreateBody(&bd);
	esh.Set(b2Vec2(-15,0), b2Vec2(15, 0));
	fd.shape = &esh;
	fd.isSensor = true;
	bounds[0]->CreateFixture(&fd);
	// bot
	bd.position.Set(0, -15);
	bounds[1] = world->CreateBody(&bd);
	esh.Set(b2Vec2(-15,0), b2Vec2(15, 0));
	fd.shape = &esh;
	bounds[1]->CreateFixture(&fd);
	// left
	bd.position.Set(-15, 0);
	bounds[2] = world->CreateBody(&bd);
	esh.Set(b2Vec2(0, -15), b2Vec2(0, 15));
	fd.shape = &esh;
	bounds[2]->CreateFixture(&fd);
	// right
	bd.position.Set(15, 0);
	bounds[3] = world->CreateBody(&bd);
	esh.Set(b2Vec2(0, -15), b2Vec2(0, 15));
	fd.shape = &esh;
	bounds[3]->CreateFixture(&fd);
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
	fjd.maxTorque = 9;
	fjd.bodyA = A;
	fjd.bodyB = B;
	fjd.localAnchorA.Set(0.f,0.f); 
	fjd.localAnchorB.Set(0.0f,0.0f); 
	fjd.collideConnected = true;
	fj = (b2FrictionJoint *) world->CreateJoint(&fjd);
}

void World::CreatePrismaticJoints(b2Body * A, b2Body * B1, b2Body * B2)
{
	b2PrismaticJointDef prismaticJointDef1, prismaticJointDef2;
	prismaticJointDef1.bodyA = A; 
	prismaticJointDef1.bodyB = B1; 
	prismaticJointDef1.collideConnected = true; 
	prismaticJointDef1.localAxisA.Set(0, 1); 
	prismaticJointDef1.localAnchorA.Set(0, 0); 
	prismaticJointDef1.localAnchorB.Set(-1, 0); 
	prismaticJointDef1.enableLimit = true; 
	prismaticJointDef1.lowerTranslation = 0; 
	prismaticJointDef1.upperTranslation = 2; 
	prismaticJointDef1.enableMotor = true; 
	prismaticJointDef1.maxMotorForce = 5; 
	prismaticJointDef1.motorSpeed = -5; 
	// set localAnchorA and B later, assume its center of body for now 
	
	prismaticJointDef2.bodyA = A; 
	prismaticJointDef2.bodyB = B2; 
	prismaticJointDef2.collideConnected = true; 
	prismaticJointDef2.localAxisA.Set(0, 1); 
	prismaticJointDef2.localAnchorA.Set(0, 0); 
	prismaticJointDef2.localAnchorB.Set(1, 0); 
	prismaticJointDef2.enableLimit = true; 
	prismaticJointDef2.lowerTranslation = 0; 
	prismaticJointDef2.upperTranslation = 2; 
	prismaticJointDef2.enableMotor = true; 
	prismaticJointDef2.maxMotorForce = 5; 
	prismaticJointDef2.motorSpeed = -5; 
	
	// finish creating prismatic here
	pj1 = (b2PrismaticJoint *) world->CreateJoint(&prismaticJointDef1);
	pj2 = (b2PrismaticJoint *) world->CreateJoint(&prismaticJointDef2);
	// weird error with undeclared identifier
}

void World::updateMaxForceAndTorque(float spd, float angSpd)
{
	fj->SetMaxForce(pow(spd, 2) * k);
	fj->SetMaxTorque(pow(angSpd, 2) * k);
}

void World::render()
{
	SDL_SetRenderDrawColor(rend, 255,255,255,255);
	
	// SDL_RenderDrawLine(rend, BoxToSDL(ground->GetPosition() - b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y, BoxToSDL(ground->GetPosition() + b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y);
	// top
	SDL_RenderDrawLine(rend, BoxToSDL(b2Vec2(-15, 15)).x, BoxToSDL(b2Vec2(-15, 15)).y, BoxToSDL(b2Vec2(15, 15)).x, BoxToSDL(b2Vec2(15, 15)).y);
	// bot
	SDL_RenderDrawLine(rend, BoxToSDL(b2Vec2(15, -15)).x, BoxToSDL(b2Vec2(15, -15)).y, BoxToSDL(b2Vec2(-15, -15)).x, BoxToSDL(b2Vec2(-15, -15)).y);
	// left
	SDL_RenderDrawLine(rend, BoxToSDL(b2Vec2(-15, 15)).x, BoxToSDL(b2Vec2(-15, 15)).y, BoxToSDL(b2Vec2(-15, -15)).x, BoxToSDL(b2Vec2(-15, -15)).y);
	// right
	SDL_RenderDrawLine(rend, BoxToSDL(b2Vec2(15, -15)).x, BoxToSDL(b2Vec2(15, -15)).y, BoxToSDL(b2Vec2(15, 15)).x, BoxToSDL(b2Vec2(15, 15)).y);
	
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
	
}

b2Body* World::GetGround()
{
	return bounds[0];
}
