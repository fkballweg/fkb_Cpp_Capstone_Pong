#include <iostream>

#include "SDL2/SDL.h"

#include "Controller.h"
#include "Paddle.h"

//Copied and adapted from https://github.com/udacity/CppND-Capstone-Snake-Game

//UserInput for Paddles
void Controller::HandleInput(bool &isRunning, std::vector<std::unique_ptr<Paddle>> &paddles) const 
{  
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
    {
		if (event.type == SDL_QUIT) 
        {
			isRunning = false;
		} 
	}

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    
    if (keystate[SDL_SCANCODE_W])
    {
        paddles.front()->direction = Paddle::Direction::Up;
    }

    if (keystate[SDL_SCANCODE_S])
    { 
        paddles.front()->direction = Paddle::Direction::Down;
    }

    if (keystate[SDL_SCANCODE_UP])
    { 
        paddles.back()->direction = Paddle::Direction::Up;
    }

    if (keystate[SDL_SCANCODE_DOWN])
    { 
        paddles.back()->direction = Paddle::Direction::Down;
    }
}
