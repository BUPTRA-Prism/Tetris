#pragma once

#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>

/**
 * @brief SDL 初始化管理类 
*/
class SDLInitializer {
private:
    bool m_sdlInitialized;  // SDL 主库是否初始化成功
    bool m_imgInitialized;  // SDL_image 是否初始化成功
    bool m_mixInitialized;  // SDL_mixer 是否初始化成功
    bool m_openAudio;       // 音频设备是否成功打开

public:
    /**
     * @brief 构造函数，初始化 SDL 主库/ SDL_image / SDL_mixer ，并打开音频设备
    */
    SDLInitializer();
    /**
     * @brief 析构函数，关闭音频设备，并退出 SDL_mixer / SDL_image / SDL 主库
    */
    ~SDLInitializer();
    /**
     * @brief SDL 初始化流程是否成功
     * @return bool 初始化流程成功返回 true ，否则返回 false
    */
    bool isSuccess() const;
};


/* SDL 相关资源删除器，用于智能指针定义 */
// SDL 窗口删除器
struct WindowDeleter {
    void operator()(SDL_Window* window) const;
};
// SDL 渲染器删除器
struct RendererDeleter {
    void operator()(SDL_Renderer* renderer) const;
};
// SDL 纹理删除器
struct TextureDeleter {
    void operator()(SDL_Texture* texture) const;
};
// SDL 表面删除器
struct SurfaceDeleter {
    void operator()(SDL_Surface* surface) const;
};
// SDL 音乐删除器
struct MusicDeleter {
    void operator()(Mix_Music* music) const;
};
// SDL 音效删除器
struct ChunkDeleter {
    void operator()(Mix_Chunk* chunk) const;
};


/* SDL 相关资源智能指针 */
using UniqueWindow = std::unique_ptr<SDL_Window, WindowDeleter>;        // SDL 窗口智能指针
using UniqueRenderer = std::unique_ptr<SDL_Renderer, RendererDeleter>;  // SDL 渲染器智能指针
using UniqueTexture = std::unique_ptr<SDL_Texture, TextureDeleter>;     // SDL 纹理智能指针
using UniqueSurface = std::unique_ptr<SDL_Surface, SurfaceDeleter>;     // SDL 表面智能指针
using UniqueMusic = std::unique_ptr<Mix_Music, MusicDeleter>;           // SDL 音乐智能指针
using UniqueChunk = std::unique_ptr<Mix_Chunk, ChunkDeleter>;           // SDL 音效智能指针