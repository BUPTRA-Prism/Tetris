/**
 * @file wrapper.cpp
 * @brief SDL 初始化器与各类型删除器的实现
 */
#include "mysdl/wrapper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

/**
 * @brief 依次初始化 SDL、SDL_image、SDL_ttf、SDL_mixer 与音频设备
 */
MySDL::Initializer::Initializer() 
    : m_sdlInit(false)
    , m_imgInit(false)
    , m_ttfInit(false)
    , m_mixInit(false)
    , m_openAudio(false) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    m_sdlInit = true;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Image Init Error: " << IMG_GetError() << std::endl;
        return;
    }
    m_imgInit = true;

    if (TTF_Init() != 0) {
        std::cerr << "TTF Init Error: " << TTF_GetError() << std::endl;
        return;
    }
    m_ttfInit = true;

    if (!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG)) {
        std::cerr << "Mix Init Error: " << Mix_GetError() << std::endl;
        return;
    }
    m_mixInit = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix OpenAudio Error: " << Mix_GetError() << std::endl;
        return;
    }
    m_openAudio = true;
}

/**
 * @brief 按初始化逆序释放各子系统
 */
MySDL::Initializer::~Initializer() {
    if (m_openAudio) {
        Mix_CloseAudio();
    }

    if (m_mixInit) {
        Mix_Quit();
    }

    if (m_ttfInit) {
        TTF_Quit();
    }

    if (m_imgInit) {
        IMG_Quit();
    }

    if (m_sdlInit) {
        SDL_Quit();
    }
}

/**
 * @brief 判断全部子系统是否初始化成功
 * @return 全部成功返回 true
 */
bool MySDL::Initializer::IsValid() const noexcept { 
    return m_sdlInit && m_imgInit && m_ttfInit && m_mixInit && m_openAudio; 
}

/** @brief 释放 SDL_Window */
void MySDL::WindowDeleter::operator()(SDL_Window* window) const noexcept {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

/** @brief 释放 SDL_Renderer */
void MySDL::RendererDeleter::operator()(SDL_Renderer* renderer) const noexcept {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
}

/** @brief 释放 SDL_Surface */
void MySDL::SurfaceDeleter::operator()(SDL_Surface* surface) const noexcept {
    if (surface) {
        SDL_FreeSurface(surface);
    }
}

/** @brief 释放 SDL_Texture */
void MySDL::TextureDeleter::operator()(SDL_Texture* texture) const noexcept {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

/** @brief 释放 TTF_Font */
void MySDL::FontDeleter::operator()(TTF_Font* font) const noexcept {
    if (font) {
        TTF_CloseFont(font);
    }
}

/** @brief 释放 Mix_Music */
void MySDL::MusicDeleter::operator()(Mix_Music* music) const noexcept {
    if (music) {
        Mix_FreeMusic(music);
    }
}

/** @brief 释放 Mix_Chunk */
void MySDL::ChunkDeleter::operator()(Mix_Chunk* chunk) const noexcept {
    if (chunk) {
        Mix_FreeChunk(chunk);
    }
}