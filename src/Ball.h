#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "SDL2/SDL.h"

#include "Paddle.h"

class Ball 
{
    public:
        enum class Direction 
        { 
            rightDown, 
            rightUp, 
            leftUp, 
            leftDown
        };

        Ball(int wGrid, int hGrid);

        void updateBall(std::vector<std::unique_ptr<Paddle>> &paddle);
        void resetBall();
        
		SDL_Point pos;
        int speed{1};

    private: 
        bool paddleCollision(std::vector<std::unique_ptr<Paddle>> &paddles);
        bool infieldBall();

        Direction _direction; 
        
        int _wGrid;
  		int _hGrid;	
};