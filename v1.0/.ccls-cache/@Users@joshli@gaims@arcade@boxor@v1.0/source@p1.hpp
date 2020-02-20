#ifndef _P1_HPP_
#define _P1_HPP_

#include "globalvar.hpp"
#include "player.hpp"
#include "world.hpp"

class World;

class P1 : public Player {
	
  public:
	
	P1();
	P1(World * worldRef);
	
	void handleEvents();
	void update();
	void render();
	
	b2Body * GetBody();
	
	int keyW;
	int keyA;
	int keyS;
	int keyD;
	int keyQ;
	int keyE;

	int countW;
	int countA;
	int countS;
	int countD;
	int countQ;
	int countE;

	b2Vec2 force;
	float forceMag;
	float torqueMag;
	
	float frictionMag;	// obtained from world object (for now, manually updated)

	int accTime;

	float length;	// side length of box
	float angleR;	// rendering angle (used to render corners of box)
	float diag;		// half of length of box diagonal
	
	b2Vec2 FL;	// front left
	b2Vec2 FR;	// front right
	b2Vec2 BL;	// back left
	b2Vec2 BR;	// back right
};
#endif
