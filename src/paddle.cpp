#include <cmath>
#include <iostream>

#include "Paddle.h"


Paddle::Paddle(int wGrid, int hGrid, int lPaddle, bool player) : _wGrid(wGrid), _hGrid(hGrid) 
{
	SDL_Point ptPaddle;

	for (int i = 0; i < lPaddle; i++) 
	{
		if(player != true) 
		{
			ptPaddle.x = static_cast<int>(1);
		}
		else 
		{
			ptPaddle.x = static_cast<int>(_wGrid-2);
		}

		ptPaddle.y = static_cast<int>(_hGrid/2 - lPaddle/2 + i);
		queue.push_front(ptPaddle);
	}
};

Paddle::Paddle(const Paddle &other) 
{
	queue = other.queue;
	_wGrid = other._wGrid;
	_hGrid = other._hGrid;
}

Paddle &Paddle::operator=(const Paddle &other) 
{	
	if (this == &other)
	{
		return *this;
	}

	queue = other.queue;
	_wGrid = other._wGrid;
	_hGrid = other._hGrid;
	
	return *this;
}

Paddle::Paddle(Paddle &&other) : queue(std::move(other.queue)) 
{	
	_wGrid = other._wGrid;
	_hGrid = other._hGrid;
	
	other._wGrid = 0;
	other._hGrid = 0;
}

Paddle &Paddle::operator=(Paddle &&other) 
{
	queue = std::move(other.queue);
	
	_wGrid = other._wGrid;
	_hGrid = other._hGrid;
	
	other._wGrid = 0;
	other._hGrid = 0;
	
	return *this;
}

void Paddle::update() 
{
	if(direction == Direction::Down) 
	{
		SDL_Point origin = queue.front();

		if(origin.y < _hGrid-1) 
		{
			SDL_Point newOrigin = origin;
			newOrigin.y += 1;

			queue.push_front(newOrigin);
			queue.pop_back();
		} 
	}
	else if (direction == Direction::Up) 
	{		
		SDL_Point origin = queue.back();

		if(origin.y > 0) 
		{
			SDL_Point newOrigin = origin;
			newOrigin.y -= 1;

			queue.push_back(newOrigin);
			queue.pop_front();
		}
	}
}