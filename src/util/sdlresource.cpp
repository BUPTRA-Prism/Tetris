#include "util/sdlresource.h"

void WindowDeleter::operator()(SDL_Window* window) const {
    if (window) {
        SDL_DestroyWindow(window);
    }
}