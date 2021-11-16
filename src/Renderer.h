#pragma once

#include <vector>
#include <memory>

#include "SDL2/SDL.h"

#include "Paddle.h"
#include "Ball.h"

class Renderer 
{
 public:
  Renderer(const std::size_t wScreen, const std::size_t hScreen, const std::size_t wGrid, const std::size_t hGrid);
  ~Renderer();

  // Function to render both of the boards as well as the ball
  void Render(std::vector<std::unique_ptr<Paddle>> &paddles, Ball const ball);

 private:
  SDL_Window* _sdlWindow;
  SDL_Renderer* _sdlRenderer;

  const std::size_t _screenWidth;
  const std::size_t _screenHeight;
  const std::size_t _gridWidth;
  const std::size_t _gridHeight;
};

