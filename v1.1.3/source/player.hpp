#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <Box2D/Box2D.h>
#include "world.hpp"
#include "globalvar.hpp"

class World;

class Player {	// super class of p1 and p2

  public:
	
	b2Body * body, * anchor, * fist1, * fist2;
	// for handling input
	int key1, key2;
	
	// for updating forces
	b2Vec2 force;
	b2Vec2 impulse;
	float forceMag;
	float torqueMag;
	float impulseMag;  // for punching
	float angImpulseMag;  // rotation of body due to punching
	
	float frictionMag;	// obtained from world object (for now, manually updated)

	int stamina;	// time cap on inputting forces (not as spammable punches)
	
	// for rendering purposes
	float length;	// side length of box
	float angleR;	// rendering angle (used to render corners of box)
	float diag;		// half of length of box diagonal
	
	b2Vec2 FL;	// front left
	b2Vec2 FR;	// front right
	b2Vec2 BL;	// back left
	b2Vec2 BR;	// back right
	
	SDL_Texture * tex;	// plain white texture for body and fists
	SDL_Texture * red;	// to indicate depleted stamina
	SDL_Rect * rect;
	SDL_Point * center;
	SDL_RendererFlip flip;
	
	Player(World * worldRef);
	~Player();
	
	int playerNumber;
	void P1_Init();
	void P2_Init();
	
	void handleEvents();
	void update();
	void render();
	void reset();
	
	b2Body * GetAnchor();
	b2Body * GetBody();
	b2Body * GetFist1();
	b2Body * GetFist2();

};

#endif
