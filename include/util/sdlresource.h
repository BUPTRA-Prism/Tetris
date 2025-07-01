#pragma once

#include <memory>
#include <SDL.h>

class SDLInitializer {
public:
    SDLInitializer(Uint32 flags);
    ~SDLInitializer();
    bool isSuccess() const;

private:
    bool m_success;
};

struct WindowDeleter {
    void operator()(SDL_Window* window) const;
};
struct RendererDeleter {
    void operator()(SDL_Renderer* renderer) const;
};

using UniqueWindow = std::unique_ptr<SDL_Window, WindowDeleter>;
using UniqueRenderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;