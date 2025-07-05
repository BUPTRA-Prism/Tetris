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

public:
    static ResourceManager& getInstance();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    bool loadResource(SDL_Renderer* renderer);
    void destroyResource();

    SDL_Texture* getImage(const std::string& path);
    SDL_Surface* getDigitFont(char digit);
    SDL_Surface* getLetterFont(char letter);
    SDL_Surface* getPunctuationFont(char punctuation);
    Mix_Music* getMusic(const std::string& path);
    Mix_Chunk* getChunk(const std::string& path);

private:
    ResourceManager() = default;
    ~ResourceManager() = default;

    bool loadImage(SDL_Renderer* renderer, const std::string& path);
    bool loadDigitFont();
    bool loadLetterFont();
    bool loadPunctuationFont();
    bool loadMusic(const std::string& path);
    bool loadChunk(const std::string& path);

    bool splitSurfaceGroup(std::vector<UniqueSurface>& surfaceVec, const std::string& path, int rowCnt, int colCnt);
};