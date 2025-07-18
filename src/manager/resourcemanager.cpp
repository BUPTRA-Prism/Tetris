#include "conf/resourceconf.h"
#include "manager/resourcemanager.h"
#include <SDL_Image.h>
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadResource(SDL_Renderer* renderer) {
    std::vector<std::string> imagePaths{
        COYRIGHT_ICON_IMAGE_PATH, 
        COUNT_FRAME_IMAGE_PATH, 
        GAME_FRAME_IMAGE_PATH, 
        HEIGHT_FRAME_IMAGE_PATH, 
        LEVEL_FRAME_IMAGE_PATH, 
        MENU_FRAME_IMAGE_PATH, 
        OPTION_ICON_IMAGE_PATH, 
        RESULT_FRAME_IMAGE_PATH, 
        TITLE_FRAME_IMAGE_PATH, 
        TYPE_FRAME_IMAGE_PATH
    };
    std::vector<std::string> fontPaths{
        DIGIT_FONT_PATH, 
        LETTER_FONT_PATH, 
        PUNCTUATION_FONT_PATH
    };
    std::vector<std::string> musicPaths{
        BGM1_MUSIC_PATH,
        BGM2_MUSIC_PATH,
        BGM3_MUSIC_PATH,
        COUNT_MUSIC_PATH,
        LOSE_MUSIC_PATH,
        TITLE_MUSIC_PATH,
        WIN_MUSIC_PATH
    };
    std::vector<std::string> chunkPaths{
        DROP_CHUNK_PATH,
        ERASE_FOUR_CHUNK_PATH,
        ERASE_CHUNK_PATH,
        LEVEL_CHUNK_PATH,
        MOVE_CHUNK_PATH,
        OPTION_CHUNK_PATH,
        ROTATE_CHUNK_PATH,
        SCENE_CHUNK_PATH
    };

    for (auto& path: imagePaths) {
        if (!loadImage(renderer, path)) {
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

void ResourceManager::destroyResource() {
    m_imageMap.clear();
    m_musicMap.clear();
    m_chunkMap.clear();
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

SDL_Texture* ResourceManager::getImage(const std::string& path) {
    if (m_imageMap.count(path) == 0) {
        return nullptr;
    }
    return m_imageMap.at(path).get();
}

SDL_Texture* ResourceManager::getFont(const std::string& path) {
    if (m_fontMap.count(path) == 0) {
        return nullptr;
    }
    return m_fontMap.at(path).get();
}

Mix_Music* ResourceManager::getMusic(const std::string& path) {
    if (m_musicMap.count(path) == 0) {
        return nullptr;
    }
    return m_musicMap.at(path).get();
}

Mix_Chunk* ResourceManager::getChunk(const std::string& path) {
    if (m_chunkMap.count(path) == 0) {
        return nullptr;
    }
    return m_chunkMap.at(path).get();
}