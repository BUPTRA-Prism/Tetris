#include "util/sdlresource.h"
#include <iostream>

SDLInitializer::SDLInitializer()
    : m_sdlInitialized(false)
    , m_imgInitialized(false)
    , m_mixInitialized(false)
    , m_openAudio(false) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    m_sdlInitialized = true;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << '\n';
        return;
    }
    m_imgInitialized = true;

    if (!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG)) {
        std::cerr << "Mix_Init failed: " << Mix_GetError() << '\n';
        return;
    }
    m_mixInitialized = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << "\n";
        return;
    }
    m_openAudio = true;
}

SDLInitializer::~SDLInitializer() {
    if (m_openAudio) {
        Mix_CloseAudio();
    }
    if (m_mixInitialized) {
        Mix_Quit();
    }
    if (m_imgInitialized) {
        IMG_Quit();
    }
    if (m_sdlInitialized) {
        SDL_Quit();
    }
}

bool SDLInitializer::isSuccess() const {
    return m_sdlInitialized && m_imgInitialized && m_mixInitialized && m_openAudio; 
}


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