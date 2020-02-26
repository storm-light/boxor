#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <Box2D/Box2D.h>

class Player {	// interface for two p1 and p2

  public:
	
	b2Body * body, * fist1, * fist2;
	// does there need to be a constructor?
	// Player();
	
	virtual void handleEvents() = 0;  // pure virtual, base class doesn't implement but derived classes must
	virtual void update() = 0;
	virtual void render() = 0;
	
	virtual b2Body * GetBody() = 0;
	virtual b2Body * GetFist1() = 0;
	virtual b2Body * GetFist2() = 0;
};

#endif
