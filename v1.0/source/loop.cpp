#include "loop.hpp"
#include <iostream>

Loop::Loop() {	// defines world (grav, timesteps), but not player body/fixtures
	// // creates new world, sets gravity
	// gravity.Set(0.0f, -9.8f);
	// gravity.Set(0.0f, 0.0f);
	// world = new b2World(gravity);
	// // parameters of Step method of b2World class
	// timeStep = 1/60.0;      //the length of time passed to simulate (seconds)
	// velocityIterations = 8;   //how strongly to correct velocity
	// positionIterations = 3;   //how strongly to correct position
	
	world = new World();
	p1 = new Player(world);
	p1->P1_Init();
	p2 = new Player(world);
	p2->P2_Init();

	// create friction joints
	world->CreateFrictionJoint(world->GetGround(), p1->GetBody());
	world->CreateFrictionJoint(world->GetGround(), p2->GetBody());
	
	// create prismatic joints here
	world->CreatePrismaticJoints(p1->GetBody(), p1->GetFist1(), p1->GetFist2());
	world->CreatePrismaticJoints(p2->GetBody(), p2->GetFist1(), p2->GetFist2());

	// // need to create a b2body for ground
	// b2BodyDef bd;
	// b2FixtureDef fd;
	// b2EdgeShape esh;
	// fd.shape = &esh;
	// fd.density = 1;
	
	// bd.type = b2_staticBody;
	// bd.position.Set(0, -5);  // below the origin some distance
	// ground = world->CreateBody(&bd);
	
	// esh.Set(b2Vec2(-10, 0), b2Vec2(10,0));
	// fd.shape = &esh;
	// ground->CreateFixture(&fd);
}

Loop::~Loop() {
	// delete world;
	world->~World();
}

void Loop::handleEvents() {
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			requestExit = 1;
		
		p1->handleEvents();
		p2->handleEvents();
        if (event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_BACKQUOTE:
				requestExit = 1;
                break;
			}
		}
	}
	
}

void Loop::update() {

	// world->Step(timeStep, velocityIterations, positionIterations);	
	world->Step();
	p1->update();
	p2->update();
	
}

void Loop::render() {

    SDL_RenderClear(rend);
	
	// std::cout << ground->GetPosition().x - 10 << " " << ground->GetPosition().x + 10 << std::endl;
	// std::cout << "ground leve: " << ground->GetPosition().y << std::endl;
	// // rendering of ground (w edge shape fixture)
	// SDL_SetRenderDrawColor(rend, 255,255,255,255);
	// // SDL_RenderDrawLine(rend, (ground->GetPosition().x - 10)*alpha, (ground->GetPosition().y)*alpha, (ground->GetPosition().x + 10)*alpha, (ground->GetPosition().y)*alpha);
	// SDL_RenderDrawLine(rend, BoxToSDL(ground->GetPosition() - b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y, BoxToSDL(ground->GetPosition() + b2Vec2(10, 0)).x, BoxToSDL(ground->GetPosition()).y);
	// SDL_SetRenderDrawColor(rend, 0,0,0,255);
	// rendering of p1
	world->render();
	p1->render();
	p2->render();
	
	SDL_RenderPresent(rend);
	SDL_Delay(1000/60);
	
}
