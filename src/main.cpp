#include <iostream>
#include "Controller.h"
#include "Game.h"
#include "Renderer.h"
#include <unistd.h>

//Copied and adapted from https://github.com/udacity/CppND-Capstone-Snake-Game 

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{960};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{48};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game pong(kGridWidth, kGridHeight);
  pong.run(controller, renderer, kMsPerFrame);
  return 0;
}