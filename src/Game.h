#pragma once

#include <memory>
#include <random>
#include <vector>

#include "SDL2/SDL.h"

#include "Ball.h"
#include "Controller.h"
#include "Paddle.h"
#include "Renderer.h"

class Game {
	public:
		Game(std::size_t wGrid, std::size_t hGrid);
		
        void run(Controller const &controller, Renderer &renderer,
				std::size_t target_frame_duration);

        void update();
		// Via a vector on the stack, store boards on the heap.
		std::vector<std::unique_ptr<Paddle>> paddles;		
		
	private:
		Ball _ball;	
};