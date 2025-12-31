#pragma once

#include "util/sdlresource.h"
#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager {
private:
    std::unordered_map<std::string, UniqueTexture> m_imageMap;  // 图像资源映射表
    std::unordered_map<std::string, UniqueTexture> m_fontMap;   // 字体资源映射表
    std::unordered_map<std::string, UniqueMusic> m_musicMap;    // 音乐资源映射表
    std::unordered_map<std::string, UniqueChunk> m_chunkMap;    // 音效资源映射表

public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    bool loadResource(SDL_Renderer* renderer);

    SDL_Texture* getImage(const std::string& path) const;
    SDL_Texture* getFont(const std::string& path) const;
    Mix_Music* getMusic(const std::string& path) const;
    Mix_Chunk* getChunk(const std::string& path) const;

private:
    bool loadImage(SDL_Renderer* renderer, const std::string& path);
    bool loadFont(SDL_Renderer* renderer, const std::string& path);
    bool loadMusic(const std::string& path);
    bool loadChunk(const std::string& path);
};