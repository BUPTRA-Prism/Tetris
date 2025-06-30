#pragma once

#include <memory>
#include <SDL.h>

struct WindowDeleter {
    void operator()(SDL_Window* window) const;
};

using UniqueWindow = std::unique_ptr<SDL_Window, WindowDeleter>;