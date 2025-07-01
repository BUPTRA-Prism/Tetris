#include "util/sdlresource.h"
#include <iostream>

SDLInitializer::SDLInitializer(Uint32 flags) {
    if (SDL_Init(flags) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        m_success = false;
    } else {
        m_success = true;
    }
}

SDLInitializer::~SDLInitializer() {
    if (m_success) {
        SDL_Quit();
    } 
}

bool SDLInitializer::isSuccess() const { return m_success; }


void WindowDeleter::operator()(SDL_Window* window) const {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

void RendererDeleter::operator()(SDL_Renderer* renderer) const {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}