#include <iostream>
#include <future>
#include <memory>
#include <thread>

#include "SDL2/SDL.h"

#include "Ball.h"
#include "Game.h"
#include "Paddle.h"

// Copied and adapted from https://github.com/udacity/CppND-Capstone-Snake-Game

Game::Game(std::size_t wGrid, std::size_t hGrid) : _ball(wGrid, hGrid) 
{
	for(int i = 0; i < 2; i++) 
	{
		std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(wGrid, hGrid, 5, i);
		paddles.emplace_back(std::move(paddle));
	}
}

void Game::run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) 
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) 
	{
		frame_start = SDL_GetTicks();

		controller.HandleInput(running, paddles);
		update();
		renderer.Render(paddles, _ball);

		frame_end = SDL_GetTicks();

		frame_count++;
		frame_duration = frame_end - frame_start;

		if (frame_end - title_timestamp >= 15000) {
			_ball.speed -= 1;
			title_timestamp = frame_end;
		}

		if (frame_duration < target_frame_duration) {
			SDL_Delay(target_frame_duration - frame_duration);
		}
    }
}

void Game::update() 
{
	for(auto p = paddles.begin(); p != paddles.end(); ++p) 
	{
		if((*p)->state == Paddle::GameState::lose) 
		{
			return;
		}
	}
	
	std::future<void> ftr = std::async(std::launch::async, [this]() 
	{
			for(auto p = paddles.begin(); p != paddles.end(); ++p) 
			{
				(*p)->update();
				(*p)->direction = Paddle::Direction::None;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	);

	ftr.get();

	_ball.updateBall(paddles);
}