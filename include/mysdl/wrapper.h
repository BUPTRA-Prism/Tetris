/**
 * @file wrapper.h
 * @brief SDL 资源的 RAII 封装，提供初始化器与各 SDL 类型的智能指针删除器
 */
#pragma once

#include <memory>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct TTF_Font;
struct Mix_Music;
struct Mix_Chunk;

namespace MySDL {
    /**
     * @brief SDL 初始化器，负责各子系统的初始化与逆序销毁
     */
    class Initializer {
    private:
        bool m_sdlInit;
        bool m_imgInit;
        bool m_ttfInit;
        bool m_mixInit;
        bool m_openAudio;

    public:
        /** @brief 依次初始化 SDL、SDL_image、SDL_ttf、SDL_mixer 与音频设备 */
        Initializer();
        /** @brief 按初始化逆序释放各子系统 */
        ~Initializer();
        Initializer(const Initializer&) = delete;
        Initializer& operator=(const Initializer&) = delete;
        Initializer(Initializer&&) = delete;
        Initializer& operator=(Initializer&&) = delete;

        /**
         * @brief 判断全部子系统是否初始化成功
         * @return 全部成功返回 true
         */
        bool IsValid() const noexcept;
    };

    /** @brief SDL_Window 释放器 */
    struct WindowDeleter {
        void operator()(SDL_Window* window) const noexcept;
    };

    /** @brief SDL_Renderer 释放器 */
    struct RendererDeleter {
        void operator()(SDL_Renderer* renderer) const noexcept;
    };

    /** @brief SDL_Surface 释放器 */
    struct SurfaceDeleter {
        void operator()(SDL_Surface* surface) const noexcept;
    };

    /** @brief SDL_Texture 释放器 */
    struct TextureDeleter {
        void operator()(SDL_Texture* texture) const noexcept;
    };

    /** @brief TTF_Font 释放器 */
    struct FontDeleter {
        void operator()(TTF_Font* font) const noexcept;
    };

    /** @brief Mix_Music 释放器 */
    struct MusicDeleter {
        void operator()(Mix_Music* music) const noexcept;
    };

    /** @brief Mix_Chunk 释放器 */
    struct ChunkDeleter {
        void operator()(Mix_Chunk* chunk) const noexcept;
    };

    /** @brief SDL_Window 独占指针 */
    using UniqueWindow = std::unique_ptr<SDL_Window, WindowDeleter>;
    /** @brief SDL_Renderer 独占指针 */
    using UniqueRenderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;
    /** @brief SDL_Surface 独占指针 */
    using UniqueSurface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;
    /** @brief SDL_Texture 独占指针 */
    using UniqueTexture = std::unique_ptr<SDL_Texture, TextureDeleter>;
    /** @brief TTF_Font 独占指针 */
    using UniqueFont = std::unique_ptr<TTF_Font, FontDeleter>;
    /** @brief Mix_Music 独占指针 */
    using UniqueMusic = std::unique_ptr<Mix_Music, MusicDeleter>;
    /** @brief Mix_Chunk 独占指针 */
    using UniqueChunk = std::unique_ptr<Mix_Chunk, ChunkDeleter>;
}