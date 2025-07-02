#include "manager/resourcemanager.h"
#include <SDL_Image.h>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() : m_loaded(false) {}

void ResourceManager::loadResource() {

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

bool ResourceManager::isLoaded() const { return m_loaded; }