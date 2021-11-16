#include "Renderer.h"
#include <iostream>
#include <string>
#include <memory>

//Copied and adapted from: https://github.com/udacity/CppND-Capstone-Snake-Game  

Renderer::Renderer(const std::size_t wScreen, const std::size_t hScreen, const std::size_t wGrid, const std::size_t hGrid)
		: _screenWidth(wScreen), _screenHeight(hScreen), _gridWidth(wGrid), _gridHeight(hGrid) 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}

	_sdlWindow = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED, _screenWidth,
									_screenHeight, SDL_WINDOW_SHOWN);

	if (nullptr == _sdlWindow) {
		std::cerr << "Window could not be created.\n";
		std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
	}

	// Create renderer
	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if (nullptr == _sdlRenderer) {
		std::cerr << "Renderer could not be created.\n";
		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
	}
}

Renderer::~Renderer() {
    SDL_DestroyWindow(_sdlWindow);
    SDL_Quit();
}

void Renderer::Render(std::vector<std::unique_ptr<Paddle>> &paddles, Ball const ball) {
    SDL_Rect block;
    block.w = _screenWidth / _gridWidth;
    block.h = _screenHeight / _gridHeight;

    SDL_SetRenderDrawColor(_sdlRenderer, 35, 24, 30, 204);
    SDL_RenderClear(_sdlRenderer);

    SDL_SetRenderDrawColor(_sdlRenderer, 221, 247, 18, 255);
    block.x = ball.pos.x * block.w;
    block.y = ball.pos.y * block.h;
    SDL_RenderFillRect(_sdlRenderer, &block);

    SDL_SetRenderDrawColor(_sdlRenderer, 208, 51, 12, 255);
    for (SDL_Point const &point : paddles.front()->queue) 
    {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(_sdlRenderer, &block);
    }

    SDL_SetRenderDrawColor(_sdlRenderer, 208, 51, 12, 255);
    for (SDL_Point const &point : paddles.back()->queue) 
    {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(_sdlRenderer, &block);
    }

    SDL_RenderPresent(_sdlRenderer);
}