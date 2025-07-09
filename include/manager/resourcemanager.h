#pragma once

#include "util/sdlresource.h"
#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager {
private:
    std::unordered_map<std::string, UniqueTexture> m_imageMap;
    std::unordered_map<std::string, UniqueTexture> m_fontMap;
    std::unordered_map<std::string, UniqueMusic> m_musicMap;
    std::unordered_map<std::string, UniqueChunk> m_chunkMap;

public:
    static ResourceManager& getInstance();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    bool loadResource(SDL_Renderer* renderer);
    void destroyResource();

    SDL_Texture* getImage(const std::string& path);
    SDL_Texture* getFont(const std::string& path);
    Mix_Music* getMusic(const std::string& path);
    Mix_Chunk* getChunk(const std::string& path);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    bool loadImage(SDL_Renderer* renderer, const std::string& path);
    bool loadFont(SDL_Renderer* renderer, const std::string& path);
    bool loadMusic(const std::string& path);
    bool loadChunk(const std::string& path);
};