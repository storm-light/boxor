#include "player.hpp"
// might not need anything here since Player class is abstract
// or is it... because p1 and p2 are practically the same, most code shall go here
Player::Player(World * worldRef)  // both players share force mags initially
{
	// need to create a b2body here
	b2BodyDef bd;
	b2FixtureDef fd;
	b2PolygonShape psh;
	fd.shape = &psh;
	fd.density = 1;
	
	bd.type = b2_dynamicBody;
	bd.position.Set(-10, 0);  // change for p2
	bd.angle = -90 * DEGTORAD;
	// body = worldRef->CreateBody(&bd);
	body = worldRef->CreateBody(&bd);
	
	length = 1;
	psh.SetAsBox(length/2, length/2);
	fd.shape = &psh;
	fd.density = 0.1;	 // weight of main body 
	fd.restitution = 0.1;  // makes punches have more an effect, bouncy
	body->CreateFixture(&fd);
	
	// create fist1 and fist2 here
	// other features of bodyDef and fixtureDef are already initialized above
	bd.position.Set(-1 * length, 0);
	fist1 = worldRef->CreateBody(&bd);
	psh.SetAsBox(length/4, length/4);
	fd.density = 1.0;  // weight of fist
	fist1->CreateFixture(&fd);
	
	bd.position.Set(1 * length, 0);
	fist2 = worldRef->CreateBody(&bd);
	psh.SetAsBox(length/4, length/4);
	fd.density = 1.0;  // weight of fist
	fist2->CreateFixture(&fd);
	
	// creation of anchor (invisible body mimicking body)
	bd.type = b2_kinematicBody;
	bd.position.Set(-10, 0);  // change for p2
	bd.angle = -90 * DEGTORAD;
	anchor = worldRef->CreateBody(&bd);
	
	key1 = 0;
	key2 = 0;
	
	forceMag = 15;
	torqueMag = 15;
	
	frictionMag = 9;
	
	impulseMag = 1.5;
	angImpulseMag = 0.5;
}

void Player::handleEvents()
{
	if (playerNumber == 1)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_1:
					key1 = 1;
					break;
				case SDLK_2:
					key2 = 1;
					break;
			}
		}
	
		if (event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_1:
					key1 = 0;
					break;
				case SDLK_2:
					key2 = 0;
					break;
			}
		}
	}
	else
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_COMMA:
					key1 = 1;
					break;
				case SDLK_PERIOD:
					key2 = 1;
					break;
			}
		}
	
		if (event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_COMMA:
					key1 = 0;
					break;
				case SDLK_PERIOD:
					key2 = 0;
					break;
			}
		}
	}
}

void Player::update()
{
	// teleport anchor to body
	anchor->SetTransform(body->GetPosition(), body->GetAngle());
	// instead of teleporting, set velocity and angle?
	anchor->SetLinearVelocity(body->GetLinearVelocity());
	anchor->SetAngularVelocity(body->GetAngularVelocity());
	
	if (key2)
	{
		impulse = b2Vec2(-1*impulseMag * sin(fist1->GetAngle()), impulseMag * cos(fist1->GetAngle()));  
		// to make sure a punch goes full force no matter previous force/velocity, we reset velocity here
		// fist1->SetLinearVelocity(b2Vec2(0,0));
		// fist1->ApplyLinearImpulse(2 * impulse, fist1->GetWorldCenter(), true);
		// // body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true); // need this since fist1 is connected with anchor and does not impact forces on body
		fist1->ApplyForce(100 * impulse, fist1->GetWorldCenter(), true);
		body->ApplyForce(20 * impulse, body->GetWorldCenter(), true); // need this since fist1 is connected with anchor and does not impact forces on body
		// anchor->ApplyLinearImpulse(impulse, anchor->GetWorldCenter(), true);
		
		// rotation impulse
		// body->ApplyAngularImpulse(angImpulseMag, true);
		body->ApplyTorque(37 * angImpulseMag, true);
		fist2->ApplyForceToCenter(-100 * impulse, true);
		// fist2->ApplyLinearImpulse(-1 * impulse, fist2->GetWorldCenter(), true);
		// anchor->ApplyAngularImpulse(angImpulseMag, true);
		// key2 = 0;
	}
	
	if (key1)
	{
		impulse = b2Vec2(-1*impulseMag * sin(fist2->GetAngle()), impulseMag * cos(fist2->GetAngle()));  
		// fist2->SetLinearVelocity(b2Vec2(0,0));
		fist2->ApplyForce(100 * impulse, fist2->GetWorldCenter(), true);
		body->ApplyForce(20 * impulse, body->GetWorldCenter(), true); // need this since fist1 is connected with anchor and does not impact forces on body
		// fist2->ApplyLinearImpulse(2 * impulse, fist2->GetWorldCenter(), true);
		// // body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
		// anchor->ApplyLinearImpulse(impulse, anchor->GetWorldCenter(), true);
		
		// rotation impulse
		// body->ApplyAngularImpulse(-1 * angImpulseMag, true);
		body->ApplyTorque(-37 * angImpulseMag, true);
		fist1->ApplyForceToCenter(-100 * impulse, true);
		// fist1->ApplyLinearImpulse(-1 * impulse, fist1->GetWorldCenter(), true);
		// anchor->ApplyAngularImpulse(angImpulseMag, true);
		// key1 = 0;
	}

	if (abs(body->GetWorldCenter().x) >= 15 || abs(body->GetWorldCenter().y) >= 15)
	{
		requestExit = 1;
	}
	
}

void Player::render()
{
	
	SDL_SetRenderDrawColor(rend, 255,255,255,255);

	diag = length * sqrt(2) / 2;  
	
	/***
		RENDERING OF BODY
	***/
	// rendering four corners
	angleR = body->GetAngle() + 135 * DEGTORAD;  // for front left corner
	FL = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FL.x, FL.y); 
	
	angleR = body->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	
	angleR = body->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	
	angleR = body->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(body->GetPosition().x + diag * cos(angleR), body->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	
	// rendering four sides
	SDL_RenderDrawLine(rend, FR.x, FR.y, FL.x, FL.y);
	SDL_RenderDrawLine(rend, FR.x, FR.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, BL.x, BL.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, FL.x, FL.y, BL.x, BL.y);
	
	
	// test: render impulse vector for fists
	SDL_RenderDrawLine(rend, BoxToSDL(impulse).x, BoxToSDL(impulse).y, BoxToSDL(b2Vec2(0,0)).x, BoxToSDL(b2Vec2(0,0)).y);
	
	/***
		RENDERING OF FISTS
	***/
	/* fist1 */
	diag = length / 2 * sqrt(2) / 2;  
	
	// rendering four corners
	angleR = fist1->GetAngle() + 135 * DEGTORAD;  // for front left corner
	FL = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FL.x, FL.y); 
	
	angleR = fist1->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	
	angleR = fist1->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	
	angleR = fist1->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(fist1->GetPosition().x + diag * cos(angleR), fist1->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	
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
	
	angleR = fist2->GetAngle() + 45 * DEGTORAD;  // for front right corner
	FR = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, FR.x, FR.y); 
	
	angleR = fist2->GetAngle() + 225 * DEGTORAD;  // for back left corner
	BL = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BL.x, BL.y); 
	
	angleR = fist2->GetAngle() + 315 * DEGTORAD;  // for back right corner
	BR = b2Vec2(BoxToSDL(b2Vec2(fist2->GetPosition().x + diag * cos(angleR), fist2->GetPosition().y + diag * sin(angleR))));
	SDL_RenderDrawPoint(rend, BR.x, BR.y); 
	
	// rendering four sides
	SDL_RenderDrawLine(rend, FR.x, FR.y, FL.x, FL.y);
	SDL_RenderDrawLine(rend, FR.x, FR.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, BL.x, BL.y, BR.x, BR.y);
	SDL_RenderDrawLine(rend, FL.x, FL.y, BL.x, BL.y);
	
	SDL_SetRenderDrawColor(rend, 0,0,0,255);
}
	
void Player::P1_Init()
{
	playerNumber = 1;
}

void Player::P2_Init()
{
	playerNumber = 2;

	body->SetTransform(b2Vec2(10,0), 90 * DEGTORAD);
	anchor->SetTransform(b2Vec2(10,0), 90 * DEGTORAD);
}

b2Body * Player::GetBody()
{
	return body;
}

b2Body * Player::GetAnchor()
{
	return anchor;
}

b2Body * Player::GetFist1()
{
	return fist1;
}

b2Body * Player::GetFist2()
{
	return fist2;
}
