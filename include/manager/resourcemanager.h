/**
 * @file resourcemanager.h
 * @brief 资源管理器，统一加载并缓存图片、字体、音乐与音效
 */
#pragma once

#include "mysdl/wrapper.h"
#include <unordered_map>
#include <string_view>

/**
 * @brief 资源管理器，以字符串路径为键缓存各类资源
 */
class ResourceManager {
private:
    std::unordered_map<std::string_view, MySDL::UniqueTexture> m_imageMap; ///< 图片缓存
    std::unordered_map<std::string_view, MySDL::UniqueFont> m_fontMap;     ///< 字体缓存
    std::unordered_map<std::string_view, MySDL::UniqueMusic> m_musicMap;   ///< 音乐缓存
    std::unordered_map<std::string_view, MySDL::UniqueChunk> m_chunkMap;   ///< 音效缓存

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager& manager) = delete;
    ResourceManager& operator=(const ResourceManager& manager) = delete;
    ResourceManager(ResourceManager&& manager) = delete;
    ResourceManager& operator=(ResourceManager&& manager) = delete;

    /**
     * @brief 加载全部配置的资源
     * @param renderer 渲染器
     * @return 全部加载成功返回 true
     */
    bool LoadResource(SDL_Renderer* renderer);

    /**
     * @brief 获取图片纹理
     * @param path 图片资源路径
     * @return 对应纹理，不存在时返回空指针
     */
    SDL_Texture* GetImage(std::string_view path) const;
    /**
     * @brief 获取字体
     * @param path 字体资源路径
     * @return 对应字体，不存在时返回空指针
     */
    TTF_Font* GetFont(std::string_view path) const;
    /**
     * @brief 获取音乐
     * @param path 音乐资源路径
     * @return 对应音乐，不存在时返回空指针
     */
    Mix_Music* GetMusic(std::string_view path) const;
    /**
     * @brief 获取音效
     * @param path 音效资源路径
     * @return 对应音效，不存在时返回空指针
     */
    Mix_Chunk* GetChunk(std::string_view path) const;

private:
    /**
     * @brief 加载单张图片
     * @param renderer 渲染器
     * @param path 图片资源路径
     * @return 加载成功返回 true
     */
    bool LoadImage(SDL_Renderer* renderer, std::string_view path);
    /**
     * @brief 加载单个字体
     * @param path 字体资源路径
     * @param size 字体大小
     * @return 加载成功返回 true
     */
    bool LoadFont(std::string_view path, int size);
    /**
     * @brief 加载单个音乐
     * @param path 音乐资源路径
     * @return 加载成功返回 true
     */
    bool LoadMusic(std::string_view path);
    /**
     * @brief 加载单个音效
     * @param path 音效资源路径
     * @return 加载成功返回 true
     */
    bool LoadChunk(std::string_view path);
};