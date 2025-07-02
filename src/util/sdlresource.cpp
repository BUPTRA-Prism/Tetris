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

void TextureDeleter::operator()(SDL_Texture* texture) const {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SurfaceDeleter::operator()(SDL_Surface* surface) const {
    if (surface) {
        SDL_FreeSurface(surface);
    }
}

void MusicDeleter::operator()(Mix_Music* music) const {
    if (music) {
        Mix_FreeMusic(music);
    }
}

void ChunkDeleter::operator()(Mix_Chunk* chunk) const {
    if (chunk) {
        Mix_FreeChunk(chunk);
    }
}