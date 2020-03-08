#include "p2.hpp"

P2::P2() {
	
	// // need to create a b2body here
	// b2BodyDef bd;
	// b2FixtureDef fd;
	// b2PolygonShape psh;
	// fd.shape = &psh;
	// fd.density = 1;
	
	// bd.type = b2_dynamicBody;
	// bd.position.Set(0, 0);
	// body = world->CreateBody(&bd);
	
	// length = 1;
	// psh.SetAsBox(length/2, length/2);
	// fd.shape = &psh;
	// body->CreateFixture(&fd);
	
	// keyW = 0;
	// keyA = 0;
	// keyS = 0;
	// keyD = 0;

	// forceMag = 20;

	// // testing rendering on angles:
	// // body->ApplyAngularImpulse(4, true);
}

P2::P2(World * worldRef) {	// does this allow P2's body to be created?
	// passing in a reference to the world object in loop.cpp
	
	// need to create a b2body here
	b2BodyDef bd;
	b2FixtureDef fd;
	b2PolygonShape psh;
	fd.shape = &psh;
	fd.density = 1;
	
	bd.type = b2_dynamicBody;
	bd.position.Set(10, 0);
	bd.angle = 90 * DEGTORAD;
	// body = worldRef->CreateBody(&bd);
	body = worldRef->CreateBody(&bd);
	
	length = 1;
	psh.SetAsBox(length/2, length/2);
	fd.shape = &psh;
	fd.density = 1;	 // weight of main body 
	body->CreateFixture(&fd);
	
	// create fist1 and fist2 here
	// other features of bodyDef and fixtureDef are already initialized above
	bd.position.Set(-1 * length, 0);
	fist1 = worldRef->CreateBody(&bd);
	psh.SetAsBox(length/4, length/4);
	fd.density = 0.5;  // weight of fist
	fist1->CreateFixture(&fd);
	
	bd.position.Set(1 * length, 0);
	fist2 = worldRef->CreateBody(&bd);
	psh.SetAsBox(length/4, length/4);
	fd.density = 0.5;  // weight of fist
	fist2->CreateFixture(&fd);

	
	keyDot = 0;
	keyComma = 0;
	
	forceMag = 15;
	torqueMag = 15;
	
	frictionMag = 9;
	
	accTime = 25;
	
	impulseMag = 3.5;
}

void P2::handleEvents() {
	// make sure this logic works out by puttting P2->handleEvents() in Loop
	if (event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
            case SDLK_PERIOD:
				keyDot = 1;
                break;
            case SDLK_COMMA:
				keyComma = 1;
                break;
		}
	}
	
	if (event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
		{
            case SDLK_PERIOD:
				keyDot = 0;
                break;
            case SDLK_COMMA:
				keyComma = 0;
                break;
		}
	}
}

void P2::update() {

	if (keyDot)
	{
		impulse = b2Vec2(-1*impulseMag * sin(fist1->GetAngle()), impulseMag * cos(fist1->GetAngle()));  
		fist1->ApplyLinearImpulse(impulse, fist1->GetWorldCenter(), true);
		keyDot = 0;
	}
	
	if (keyComma)
	{
		impulse = b2Vec2(-1*impulseMag * sin(fist2->GetAngle()), impulseMag * cos(fist2->GetAngle()));  
		fist2->ApplyLinearImpulse(impulse, fist2->GetWorldCenter(), true);
		keyComma = 0;
	}

	if (abs(body->GetWorldCenter().x) >= 15 || abs(body->GetWorldCenter().y) >= 15)
	{
		requestExit = 1;
	}
}

void P2::render() {
	// pos is the actual position in space of the player, make sure to flip and adjust accordingly when rendering to match SDL's coordinate system
	// render centerpoint first, then render whole box
	SDL_SetRenderDrawColor(rend, 255,255,255,255);
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + body->GetPosition().x * alpha, WINDOW_HEIGHT/2 - body->GetPosition().y * alpha);  // center point?
	// // top left (we're assuming angle == 0)
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + body->GetPosition().x * alpha - length / 2 * alpha, WINDOW_HEIGHT/2 - body->GetPosition().y * alpha - length / 2 * alpha); 
	// // top right
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + body->GetPosition().x * alpha + length / 2 * alpha, WINDOW_HEIGHT/2 - body->GetPosition().y * alpha - length / 2 * alpha);
	// // bottom left
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + body->GetPosition().x * alpha - length / 2 * alpha, WINDOW_HEIGHT/2 - body->GetPosition().y * alpha + length / 2 * alpha); 
	// // top right
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + body->GetPosition().x * alpha + length / 2 * alpha, WINDOW_HEIGHT/2 - body->GetPosition().y * alpha + length / 2 * alpha); 
	/***
		RENDERING OF MAIN BODY
	***/
	
	diag = length * sqrt(2) / 2;  
	// std::cout << "DIAG: " << diag << std::endl;
	// rendering four corners
	angleR = body->GetAngle() + 135 * DEGTORAD;  // for front left corner
	FL = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FL.x, FL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (body->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (body->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = body->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (body->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (body->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = body->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (body->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (body->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = body->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (body->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (body->GetPosition().y + diag * sin(angleR)) * alpha); 
	// rendering four sides
	SDL_RenderDrawLine(rend, FR.x, FR.y, FL.x, FL.y);
	SDL_RenderDrawLine(rend, FR.x, FR.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, BL.x, BL.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, FL.x, FL.y, BL.x, BL.y);
	
	/***
		RENDERING OF FISTS
	***/
	/* fist1 */
	diag = length / 2 * sqrt(2) / 2;  
	
	// rendering four corners
	angleR = fist1->GetAngle() + 135 * DEGTORAD;  // for front left corner
	FL = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FL.x, FL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist1->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist1->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist1->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist1->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist1->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist1->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist1->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist1->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist1->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist1->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist1->GetPosition().y + diag * sin(angleR)) * alpha); 
	// rendering four sides
	SDL_RenderDrawLine(rend, FR.x, FR.y, FL.x, FL.y);
	SDL_RenderDrawLine(rend, FR.x, FR.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, BL.x, BL.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, FL.x, FL.y, BL.x, BL.y);
	
	/* fist2 */
	diag = length / 2 * sqrt(2) / 2;  
	
	// rendering four corners
	angleR = fist2->GetAngle() + 135 * DEGTORAD;  // for front left corner
	FL = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FL.x, FL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist2->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist2->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist2->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist2->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist2->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist2->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist2->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist2->GetPosition().y + diag * sin(angleR)) * alpha); 
	angleR = fist2->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	// SDL_RenderDrawPoint(rend, WINDOW_WIDTH/2 + (fist2->GetPosition().x + diag * cos(angleR)) * alpha, WINDOW_HEIGHT/2 - (fist2->GetPosition().y + diag * sin(angleR)) * alpha); 
	// rendering four sides
	SDL_RenderDrawLine(rend, FR.x, FR.y, FL.x, FL.y);
	SDL_RenderDrawLine(rend, FR.x, FR.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, BL.x, BL.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, FL.x, FL.y, BL.x, BL.y);

	
	
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
}

b2Body * P2::GetBody()
{
	return body;
}

b2Body * P2::GetFist1() {
	return fist1;
}

b2Body * P2::GetFist2()
{
	return fist2;
}
