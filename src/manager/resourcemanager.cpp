/**
 * @file resourcemanager.cpp
 * @brief 资源管理器实现
 */
#include "manager/resourcemanager.h"
#include "config/resource.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

/**
 * @brief 加载全部配置的图片、字体、音乐与音效
 * @return 全部加载成功返回 true
 */
bool ResourceManager::LoadResource(SDL_Renderer* renderer) {
    std::vector<std::string_view> imagePaths {
        Resource::Image::TITLE_IMG,
        Resource::Image::COPYRIGHT_IMG,
        Resource::Image::MENU_IMG,
        Resource::Image::MENU_OPTION_ICON_IMG,
        Resource::Image::SETTING_IMG,
        Resource::Image::GAME_TYPE_A_PANEL_IMG,
        Resource::Image::GAME_TYPE_B_PANEL_IMG,
        Resource::Image::LEVEL_A_PANEL_IMG,
        Resource::Image::LEVEL_B_PANEL_IMG,
        Resource::Image::HEIGHT_PANEL_IMG,
        Resource::Image::SETTING_OPTION_ICON_IMG,
        Resource::Image::LEADER_BOARD_PANEL_IMG,
        Resource::Image::GAME_A_IMG,
        Resource::Image::GAME_B_IMG,
        Resource::Image::BLOCK_BASE_IMG,
        Resource::Image::BLOCK_SOLID_PATTERN_IMG,
        Resource::Image::BLOCK_HOLLOW_PATTERN_IMG,
        Resource::Image::BLOCK_ICON_BASE_IMG,
        Resource::Image::BLOCK_ICON_SOLID_PATTERN_IMG,
        Resource::Image::BLOCK_ICON_HOLLOW_PATTERN_IMG,
        Resource::Image::FINISH_OUTER_PANEL_IMG,
        Resource::Image::FINISH_INNER_PANEL_IMG,
        Resource::Image::RANK_OPTION_ICON_IMG
    };

    std::vector<std::pair<std::string_view, int>> fontPaths {
        { Resource::Font::DEFAULT_FONT, Resource::Font::DEFAULT_FONT_SIZE }
    };

    std::vector<std::string_view> musicPaths {
        Resource::Audio::TITLE_MUSIC,
        Resource::Audio::BGM_1,
        Resource::Audio::BGM_2,
        Resource::Audio::BGM_3,
        Resource::Audio::WIN_MUSIC,
        Resource::Audio::LOSE_MUSIC,
        Resource::Audio::RANK_MUSIC
    };

    std::vector<std::string_view> chunkPaths {
        Resource::Audio::LOAD_SCENE_CHUNK,
        Resource::Audio::OPTION_CHUNK,
        Resource::Audio::PAUSE_CHUNK,
        Resource::Audio::MOVE_CHUNK,
        Resource::Audio::ROTATE_CHUNK,
        Resource::Audio::LAND_CHUNK,
        Resource::Audio::ERASE_CHUNK,
        Resource::Audio::ERASE_FOUR_CHUNK,
        Resource::Audio::LEVEL_UP_CHUNK
    };

    if (!renderer) {
        std::cerr << "Renderer is null!" << std::endl;
        return false;
    }
    for (const auto& path: imagePaths) {
        if (!LoadImage(renderer, path)) {
            std::cerr << "Failed to load image \"" << path << "\": " << IMG_GetError() << std::endl;
            return false;
        }
    }

    for (const auto& path: fontPaths) {
        if (!LoadFont(path.first, path.second)) {
            std::cerr << "Failed to load font \"" << path.first << "\": " << TTF_GetError() << std::endl;
            return false;
        }
    }

    for (const auto& path: musicPaths) {
        if (!LoadMusic(path)) {
            std::cerr << "Failed to load music \"" << path << "\": " << Mix_GetError() << std::endl;
            return false;
        }
    }

    for (const auto& path: chunkPaths) {
        if (!LoadChunk(path)) {
            std::cerr << "Failed to load chunk \"" << path << "\": " << Mix_GetError() << std::endl;
            return false;
        }
    }

    return true;
}

/**
 * @brief 获取图片纹理
 * @return 对应纹理，不存在时返回空指针
 */
SDL_Texture* ResourceManager::GetImage(std::string_view path) const {
    auto it = m_imageMap.find(path);
    return it != m_imageMap.end() ? it->second.get() : nullptr;
}

/**
 * @brief 获取字体
 * @return 对应字体，不存在时返回空指针
 */
TTF_Font* ResourceManager::GetFont(std::string_view path) const {
    auto it = m_fontMap.find(path);
    return it != m_fontMap.end() ? it->second.get() : nullptr;
}

/**
 * @brief 获取音乐
 * @return 对应音乐，不存在时返回空指针
 */
Mix_Music* ResourceManager::GetMusic(std::string_view path) const {
    auto it = m_musicMap.find(path);
    return it != m_musicMap.end() ? it->second.get() : nullptr;
}

/**
 * @brief 获取音效
 * @return 对应音效，不存在时返回空指针
 */
Mix_Chunk* ResourceManager::GetChunk(std::string_view path) const {
    auto it = m_chunkMap.find(path);
    return it != m_chunkMap.end() ? it->second.get() : nullptr;
}

/**
 * @brief 加载单张图片
 * @return 加载成功返回 true，重复或失败返回 false
 */
bool ResourceManager::LoadImage(SDL_Renderer* renderer, std::string_view path) {
    if (m_imageMap.count(path) != 0) {
        std::cerr << "Duplicate texture \"" << path << "\"" << std::endl;
        return false;
    }

    std::string fullPath(Resource::Image::FOLDER);
    fullPath.append(path);
    SDL_Texture* texture = IMG_LoadTexture(renderer, fullPath.c_str());
    if (!texture) {
        std::cerr << "Failed to load texture \"" << path << "\": " << IMG_GetError() << std::endl;
        return false;
    }

    m_imageMap.emplace(path, MySDL::UniqueTexture(texture));
    return true;
}

/**
 * @brief 加载单个字体
 * @return 加载成功返回 true，重复或失败返回 false
 */
bool ResourceManager::LoadFont(std::string_view path, int size) {
    if (m_fontMap.count(path) != 0) {
        std::cerr << "Duplicate font \"" << path << "\"" << std::endl;
        return false;
    }

    std::string fullPath(Resource::Font::FOLDER);
    fullPath.append(path);
    TTF_Font* font = TTF_OpenFont(fullPath.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font \"" << path << "\": " << TTF_GetError() << std::endl;
        return false;
    }

    m_fontMap.emplace(path, MySDL::UniqueFont(font));
    return true;
}

/**
 * @brief 加载单个音乐
 * @return 加载成功返回 true，重复或失败返回 false
 */
bool ResourceManager::LoadMusic(std::string_view path) {
    if (m_musicMap.count(path) != 0) {
        std::cerr << "Duplicate music \"" << path << "\"" << std::endl;
        return false;
    }

    std::string fullPath(Resource::Audio::MUSIC_FOLDER);
    fullPath.append(path);
    Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
    if (!music) {
        std::cerr << "Failed to load music \"" << path << "\": " << Mix_GetError() << std::endl;
        return false;
    }

    m_musicMap.emplace(path, MySDL::UniqueMusic(music));
    return true;
}

/**
 * @brief 加载单个音效
 * @return 加载成功返回 true，重复或失败返回 false
 */
bool ResourceManager::LoadChunk(std::string_view path) {
    if (m_chunkMap.count(path) != 0) {
        std::cerr << "Duplicate chunk \"" << path << "\"" << std::endl;
        return false;
    }

    std::string fullPath(Resource::Audio::CHUNK_FOLDER);
    fullPath.append(path);
    Mix_Chunk* chunk = Mix_LoadWAV(fullPath.c_str());
    if (!chunk) {
        std::cerr << "Failed to load chunk \"" << path << "\": " << Mix_GetError() << std::endl;
        return false;
    }

    m_chunkMap.emplace(path, MySDL::UniqueChunk(chunk));
    return true;
}