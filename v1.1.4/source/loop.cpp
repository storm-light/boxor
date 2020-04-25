#include "loop.hpp"
#include <iostream>

Loop::Loop() {	// defines world (grav, timesteps), but not player body/fixtures
	
	world = new World();
	p1 = new Player(world);
	p1->P1_Init();
	p2 = new Player(world);
	p2->P2_Init();

	// create friction joints
	world->CreateFrictionJoint(world->GetGround(), p1->GetBody());
	world->CreateFrictionJoint(world->GetGround(), p2->GetBody());
	
	// create prismatic joints here
	world->CreatePrismaticJoints(p1->GetAnchor(), p1->GetFist1(), p1->GetFist2());
	world->CreatePrismaticJoints(p2->GetAnchor(), p2->GetFist1(), p2->GetFist2());

	start = 0;
	o = 1;
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
	
	world->render();
	p1->render();
	p2->render();
	
	if (start < 30)
		start++;
	if (start >= 30 && o)
	{
		o = 0;
		renderInstructions();
	}
	
	SDL_RenderPresent(rend);
	SDL_Delay(1000/60);
	
}

void Loop::reset()
{
	p1->reset();
	p2->reset();
}
