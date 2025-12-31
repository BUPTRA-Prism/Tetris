#include "conf/resourceconf.h"
#include "framework/resourcemanager.h"
#include <iostream>

bool ResourceManager::loadResource(SDL_Renderer* renderer) {
    std::vector<std::string> imagePaths{
        TITLE_FRAME_PATH,
        TITLE_IMAGE_PATH,
        INNER_FIREWORK_1_PATH,
        INNER_FIREWORK_2_PATH,
        INNER_FIREWORK_3_PATH,
        INNER_FIREWORK_4_PATH,
        INNER_FIREWORK_5_PATH,
        OUTER_FIREWORK_1_PATH,
        OUTER_FIREWORK_2_PATH,
        OUTER_FIREWORK_3_PATH,
        OUTER_FIREWORK_4_PATH,
        OUTER_FIREWORK_5_PATH,
        ARROW_PATH,
        LOGO_PATH,
        SETTING_FRAME_PATH,
        VERSUS_GAME_FRAME_PATH,
        COOP_GAME_FRAME_PATH,
        SINGLE_BOARD_PATH,
        VERSUS_BOARD_PATH,
        COOP_BOARD_PATH,
        BLOCK_PATH
    };
    std::vector<std::string> fontPaths{
        DIGIT_FONT_PATH,
        LETTER_FONT_PATH
    };
    std::vector<std::string> musicPaths{
        TITLE_MUSIC_PATH,
        KOROBEINIKI_MUSIC_PATH,
        KARINKA_MUSIC_PATH,
        TROIKA_MUSIC_PATH
    };
    std::vector<std::string> chunkPaths{
        NEXT_SCENE_CHUNK_PATH,
        SELECT_CHUNK_PATH
    };

    for (auto& path: imagePaths) {
        if (!loadImage(renderer, path)) {
            std::cerr << "Failed to load image '" << path << "': " << IMG_GetError() << '\n';
            return false; 
        }
    }
    for (auto& path: fontPaths) {
        if (!loadFont(renderer, path)) {
            return false; 
        }
    }
    for (auto& path: musicPaths) {
        if (!loadMusic(path)) {
            return false; 
        }
    }
    for (auto& path: chunkPaths) {
        if (!loadChunk(path)) {
            return false;
        }
    }

    return true;
}

bool ResourceManager::loadImage(SDL_Renderer* renderer, const std::string& path) {
    if (m_imageMap.count(path) != 0) {
        std::cerr << "Duplicate texture \"" << path << '\n';
        return false;
    }
    SDL_Texture* texture = IMG_LoadTexture(renderer, (IMAGE_DIR + path).c_str());
    if (!texture) {
        std::cerr << "Failed to load texture \"" << path << "\": " << IMG_GetError() << '\n';
        return false;
    }
    m_imageMap.emplace(path, UniqueTexture(texture));
    return true;
}

bool ResourceManager::loadFont(SDL_Renderer* renderer, const std::string& path) {
    if (m_fontMap.count(path) != 0) {
        std::cerr << "Duplicate texture \"" << path << '\n';
        return false;
    }
    SDL_Texture* texture = IMG_LoadTexture(renderer, (FONT_DIR + path).c_str());
    if (!texture) {
        std::cerr << "Failed to load texture \"" << path << "\": " << IMG_GetError() << '\n';
        return false;
    }
    m_fontMap.emplace(path, UniqueTexture(texture));
    return true;
}

bool ResourceManager::loadMusic(const std::string& path) {
    if (m_musicMap.count(path) != 0) {
        std::cerr << "Duplicate music \"" << path << '\n';
        return false;
    }
    Mix_Music* music = Mix_LoadMUS((MUSIC_DIR + path).c_str());
    if (!music) {
        std::cerr << "Failed to load music '" << path << "': " << Mix_GetError() << '\n';
        return false;
    }
    m_musicMap.emplace(path, UniqueMusic(music));
    return true;
}

bool ResourceManager::loadChunk(const std::string& path) {
    if (m_chunkMap.count(path) != 0) {
        std::cerr << "Duplicate chunk \"" << path << '\n';
        return false;
    }
    Mix_Chunk* chunk = Mix_LoadWAV(((CHUNK_DIR + path)).c_str());
    if (!chunk) {
        std::cerr << "Failed to load chunk '" << path << "': " << Mix_GetError() << '\n';
        return false;
    }
    m_chunkMap.emplace(path, UniqueChunk(chunk));
    return true;
}

SDL_Texture* ResourceManager::getImage(const std::string& path) const {
    auto it = m_imageMap.find(path);
    return it != m_imageMap.end() ? it->second.get() : nullptr;
}

SDL_Texture* ResourceManager::getFont(const std::string& path) const {
    auto it = m_fontMap.find(path);
    return it != m_fontMap.end() ? it->second.get() : nullptr;
}

Mix_Music* ResourceManager::getMusic(const std::string& path) const {
    auto it = m_musicMap.find(path);
    return it != m_musicMap.end() ? it->second.get() : nullptr;
}

Mix_Chunk* ResourceManager::getChunk(const std::string& path) const {
    auto it = m_chunkMap.find(path);
    return it != m_chunkMap.end() ? it->second.get() : nullptr;
}