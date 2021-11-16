#include <algorithm>

#include "SDL2/SDL.h"

#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

//Constructor
Ball::Ball(int wGrid, int hGrid) : _wGrid(wGrid), _hGrid(hGrid), pos({static_cast<int>(wGrid/2), static_cast<int>(hGrid/2)}), _direction(Direction::rightUp) 
{

}

//Check if Ball is still in field
bool Ball::infieldBall() 
{
    if(pos.x >= 0 && pos.x < _wGrid && pos.y >= 0 && pos.y < _hGrid) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//Check if Ball Position matches Paddle Position
bool Ball::paddleCollision(std::vector<std::unique_ptr<Paddle>> &paddles) 
{
    for(auto p = paddles.begin(); p != paddles.end(); ++p) 
    {
        for(auto q = (*p)->queue.begin(); q != (*p)->queue.end(); ++q ) 
        {
            if(q->x == pos.x && (q->y == pos.y || (pos.y < 0 && q->y == 0) || (pos.y >= _hGrid && q->y == _hGrid-1))) 
            {
                return true;
            }
        }
    }
    return false;
}

//Updating the Balls position using its direction as well as paddleCollision() and infieldBall() information.
void Ball::updateBall(std::vector<std::unique_ptr<Paddle>> &paddles) 
{   
    if(_direction == Direction::leftUp) 
    {
        pos.x -= 1;
        pos.y -= 1;

        if(infieldBall()) 
        {
            if(paddleCollision(paddles))
            {
                pos.x += 2;
                _direction = Direction::rightUp;
            }
            if(pos.x == 0) 
            {
                paddles.at(0)->state = Paddle::GameState::lose;
                pos.x = _wGrid/2;
                pos.y = _hGrid/2;
            }
        } 
        else 
        {
            pos.y += 1;
            _direction = Direction::leftDown;
        }
    }
    else if(_direction == Direction::rightDown) 
    {
        pos.x += 1;
        pos.y += 1;

        if(infieldBall()) 
        {
            if(paddleCollision(paddles))
            {
                pos.x -= 2;
                _direction = Direction::leftDown;
            }
            if(pos.x == _wGrid-1) 
            {
                paddles.at(0)->state = Paddle::GameState::lose;
                pos.x = _wGrid/2;
                pos.y = _hGrid/2;
            }
        } 
        else 
        {
            if(paddleCollision(paddles)) {
                pos.x -= 2;
                pos.y -= 2;
                _direction = Direction::leftUp;
            }
            else 
            {
                pos.y -= 2;
                _direction = Direction::rightUp;
            }
        }
    }
    else if(_direction == Direction::rightUp) 
    {
        pos.x += 1;
        pos.y -= 1;

        if(infieldBall()) 
        {
            if(paddleCollision(paddles))
            {
                pos.x -= 2;
                _direction = Direction::leftUp;
            }

            if(pos.x == _wGrid-1) 
            {
                paddles.at(0)->state = Paddle::GameState::lose;
                pos.x = _wGrid/2;
                pos.y = _hGrid/2;
            }
        } 
        else 
        {
            if(paddleCollision(paddles)) 
            {
                pos.x -= 2;
                pos.y += 2;
                _direction = Direction::leftDown;
            }
            else 
            {
                pos.y += 2;
                _direction = Direction::rightDown;
            }
        }
    }

    else 
    {
        pos.x -= 1;
        pos.y += 1;

        if(infieldBall()) 
        {
            if(paddleCollision(paddles))
            {
                pos.x += 2;
                _direction = Direction::rightDown;
            }

            if(pos.x == 0) 
            {
                paddles.at(0)->state = Paddle::GameState::lose;
                pos.x = _wGrid/2;
                pos.y = _hGrid/2;
            }
        } 
        else 
        {
            if(paddleCollision(paddles)) 
            {
                pos.x += 2;
                pos.y -= 2;
                _direction = Direction::rightUp;
            }
            else 
            {
                pos.y -= 2;
                _direction = Direction::leftUp;
            }
        }
    }
}