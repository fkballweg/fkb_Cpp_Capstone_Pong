#pragma once

#include <memory>
#include <vector>

#include "Paddle.h"


class Controller {
    public:
        void HandleInput(bool &isRunning,  std::vector<std::unique_ptr<Paddle>> &paddles) const;
};

