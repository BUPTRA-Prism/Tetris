#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class SDLInitializer {
private:
    bool m_sdlInitialized;
    bool m_imgInitialized;
    bool m_mixInitialized;
    bool m_openAudio;

public:
    SDLInitializer();
    ~SDLInitializer();
    bool isSuccess() const;
};


struct WindowDeleter {
    void operator()(SDL_Window* window) const;
};
struct RendererDeleter {
    void operator()(SDL_Renderer* renderer) const;
};
struct TextureDeleter {
    void operator()(SDL_Texture* texture) const;
};
struct SurfaceDeleter {
    void operator()(SDL_Surface* surface) const;
};
struct MusicDeleter {
    void operator()(Mix_Music* music) const;
};
struct ChunkDeleter {
    void operator()(Mix_Chunk* chunk) const;
};


using UniqueWindow = std::unique_ptr<SDL_Window, WindowDeleter>;
using UniqueRenderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;
using UniqueTexture = std::unique_ptr<SDL_Texture, TextureDeleter>;
using UniqueSurface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;
using UniqueMusic = std::unique_ptr<Mix_Music, MusicDeleter>;
using UniqueChunk = std::unique_ptr<Mix_Chunk, ChunkDeleter>;