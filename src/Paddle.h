#pragma once

#include <deque>
#include <iostream>

#include "SDL2/SDL.h"

class Paddle 
{
	public:
		enum class Direction 
        { 
            Up, 
            Down, 
            None 
        };

		enum class GameState 
        { 
            win, 
            lose, 
            inGame 
        };

		Paddle(int wGrid, int hGrid, int wPaddle, bool player);
		~Paddle() = default;

		Paddle(const Paddle &other);
		Paddle &operator=(const Paddle &other);

		Paddle(Paddle &&other);
		Paddle &operator=(Paddle &&other);
			
		void update();

		GameState state = GameState::inGame;
		Direction direction = Direction::None;

		float speed{0.1f};

		std::deque<SDL_Point> queue;

	private:
		int _wGrid;
  		int _hGrid;
};