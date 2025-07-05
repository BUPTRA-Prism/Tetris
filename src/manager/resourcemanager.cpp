#include "conf/resourceconf.h"
#include "manager/resourcemanager.h"
#include <SDL_Image.h>
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadResource(SDL_Renderer* renderer) {
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << '\n';
        return false;
    }
    if (!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG)) {
        std::cerr << "Mix_Init failed: " << Mix_GetError() << '\n';
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
        return false;
    }

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

    if (!loadDigitFont()) { 
        return false; 
    }
    if (!loadLetterFont()) { 
        return false; 
    }
    if (!loadPunctuationFont()) { 
        return false; 
    }
    for (auto path: imagePaths) {
        if (!loadImage(renderer, path)) {
            return false; 
        }
    }
    for (auto path: musicPaths) {
        if (!loadMusic(path)) {
            return false; 
        }
    }
    for (auto path: chunkPaths) {
        if (!loadChunk(path)) {
            return false;
        }
    }
    return true;
}

void ResourceManager::destroyResource() {
    m_imageMap.clear();
    m_digitFontVec.clear();
    m_letterFontVec.clear();
    m_punctuationFontMap.clear();
    m_musicMap.clear();
    m_chunkMap.clear();

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
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

bool ResourceManager::loadDigitFont() {
    m_digitFontVec.resize(10);
    return splitSurfaceGroup(m_digitFontVec, FONT_DIR + DIGIT_FONT_PATH, 1, 10);
}

bool ResourceManager::loadLetterFont() {
    m_letterFontVec.resize(26);
    return splitSurfaceGroup(m_letterFontVec, FONT_DIR + LETTER_FONT_PATH, 1, 26);
}

bool ResourceManager::loadPunctuationFont() {
    int len = PUNCTUATION_LIST.length();
    std::vector<UniqueSurface> punctuationFontVec;
    punctuationFontVec.resize(len);
    if (!splitSurfaceGroup(punctuationFontVec, FONT_DIR + PUNCTUATION_FONT_PATH, 1, len)) {
        return false;
    }
    for (int idx = 0; idx < len; ++idx) {
        m_punctuationFontMap.emplace(PUNCTUATION_LIST[idx], std::move(punctuationFontVec[idx]));
    }
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

SDL_Surface* ResourceManager::getDigitFont(char digit) {
    if (digit >= '0' && digit <= '9') {
        return m_digitFontVec[digit - '0'].get();
    }
    return nullptr;
}

SDL_Surface* ResourceManager::getLetterFont(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return m_letterFontVec[letter - 'A'].get();
    }
    return nullptr;
}

SDL_Surface* ResourceManager::getPunctuationFont(char punctuation) {
    if (m_punctuationFontMap.count(punctuation) == 0) {
        return nullptr;
    }
    return m_punctuationFontMap.at(punctuation).get();
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

bool ResourceManager::splitSurfaceGroup(std::vector<UniqueSurface>& surfaceVec, const std::string& path, int rowCnt, int colCnt) {
    UniqueSurface surfaceGroup(IMG_Load(path.c_str()));
    if (!surfaceGroup) {
        std::cerr << "Load surface group failed: " << SDL_GetError() << std::endl;
        return false;
    }
    if (surfaceGroup->w % colCnt != 0 || surfaceGroup->h % rowCnt != 0) {
        std::cerr << "Invalid surface group size: (" << surfaceGroup->w << ", " << surfaceGroup->h << ")" << std::endl;
        return false;
    }
    int surfaceWidth = surfaceGroup->w / colCnt;
    int surfaceHeight = surfaceGroup->h / rowCnt;
    for (int y = 0; y < rowCnt; y++) {
        for (int x = 0; x < colCnt; x++) {
            SDL_Rect srcRect = { x * surfaceWidth, y * surfaceHeight, surfaceWidth, surfaceHeight };

            SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
                0, surfaceWidth, surfaceHeight, 
                surfaceGroup->format->BitsPerPixel,
                surfaceGroup->format->format);

            if (!surface) {
                std::cerr << "Create frame surface failed: " << SDL_GetError() << std::endl;
                return false;
            }

            if (SDL_BlitSurface(surfaceGroup.get(), &srcRect, surface, nullptr) != 0) {
                std::cerr << "Blit failed: " << SDL_GetError() << std::endl;
                SDL_FreeSurface(surface);
                return false;
            }

            surfaceVec.emplace_back(UniqueSurface(surface));
        }
    }
    return true;
}