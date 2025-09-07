#pragma once

#include "util/sdlresource.h"
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief 资源管理器类，用于保存和访问图像、字体、音乐、音效资源
 *
 * 使用单例模式，保证全局唯一实例
 */
class ResourceManager {
private:
    std::unordered_map<std::string, UniqueTexture> m_imageMap;  // 图像资源映射表
    std::unordered_map<std::string, UniqueTexture> m_fontMap;   // 字体资源映射表
    std::unordered_map<std::string, UniqueMusic> m_musicMap;    // 音乐资源映射表
    std::unordered_map<std::string, UniqueChunk> m_chunkMap;    // 音效资源映射表

public:
    /**
     * @brief 获取资源管理器单例
     * @return ResourceManager& 全局唯一实例
     */
    static ResourceManager& getInstance();

    // 禁用拷贝与移动
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    /**
     * @brief 加载所有资源（图像、字体、音乐、音效）
     * @param renderer SDL 渲染器，用于加载图像/字体
     * @return bool 所有资源加载成功返回 true ，否则返回 false
     */
    bool loadResource(SDL_Renderer* renderer);
    /**
     * @brief 销毁所有资源
     */
    void destroyResource();

    /**
     * @brief 获取图像资源
     * @param path 图像文件名
     * @return SDL_Texture* 对应图像纹理，如果未加载返回 nullptr
     */
    SDL_Texture* getImage(const std::string& path);
    /**
     * @brief 获取字体资源
     * @param path 字体文件名
     * @return SDL_Texture* 对应字体纹理，如果未加载返回 nullptr
     */
    SDL_Texture* getFont(const std::string& path);
    /**
     * @brief 获取音乐资源
     * @param path 音乐文件名
     * @return Mix_Music* 对应音乐，如果未加载返回 nullptr
     */
    Mix_Music* getMusic(const std::string& path);
    /**
     * @brief 获取音效资源
     * @param path 音效文件名
     * @return Mix_Chunk* 对应音效，如果未加载返回 nullptr
     */
    Mix_Chunk* getChunk(const std::string& path);

private:
    ResourceManager() = default;    // 私有构造函数
    ~ResourceManager() = default;   // 私有析构函数

    /**
     * @brief 加载单个图像资源
     * @param renderer SDL 渲染器
     * @param path 图像文件名
     * @return bool 加载成功返回 true ，否则返回 false
     */
    bool loadImage(SDL_Renderer* renderer, const std::string& path);
    /**
     * @brief 加载单个字体资源
     * @param renderer SDL 渲染器
     * @param path 字体文件名
     * @return bool 加载成功返回 true ，否则返回 false
     */
    bool loadFont(SDL_Renderer* renderer, const std::string& path);
    /**
     * @brief 加载单个音乐资源
     * @param path 音乐文件名
     * @return bool 加载成功返回 true ，否则返回 false
     */
    bool loadMusic(const std::string& path);
    /**
     * @brief 加载单个音效资源
     * @param path 音效文件名
     * @return bool 加载成功返回 true ，否则返回 false
     */
    bool loadChunk(const std::string& path);
};