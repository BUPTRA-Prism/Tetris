#pragma once

#include "util/sdlresource.h"
#include <string>
#include <unordered_map>
#include <vector>

class ResourceManager {
private:
    std::unordered_map<std::string, UniqueTexture> m_imageMap;
    std::vector<UniqueSurface> m_digitFontVec;
    std::vector<UniqueSurface> m_letterFontVec;
    std::unordered_map<char, UniqueSurface> m_punctuationFontMap;
    std::unordered_map<std::string, UniqueMusic> m_musicMap;
    std::unordered_map<std::string, UniqueChunk> m_chunkMap;

    bool m_loaded = false;

public:
    static ResourceManager& getInstance();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    void loadResource();
    void destroyResource();
    bool isLoaded() const;

private:
    ResourceManager();
    ~ResourceManager() = default;
};