/**
 * @file audiomanager.cpp
 * @brief 音频管理器实现
 */
#include "manager/audiomanager.h"
#include "manager/resourcemanager.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>

/**
 * @brief 播放音乐
 *
 * 本项目的循环语义（0 为无限，1 为单次）在此换算为 SDL_mixer 的惯例，
 * 即 loops = N - 1
 */
void AudioManager::PlayMusic(const ResourceManager& resourceMgr, std::string_view path, unsigned int loop) {
    Mix_Music* music = resourceMgr.GetMusic(path);
    if (!music) {
        std::cerr << "Failed to load music \"" << path << "\"" << std::endl;
        return;
    }
    Mix_PlayMusic(music, static_cast<int>(loop) - 1);
}

/** @brief 暂停音乐 */
void AudioManager::PauseMusic() {
    Mix_PauseMusic();
}

/** @brief 恢复音乐 */
void AudioManager::ResumeMusic() {
    Mix_ResumeMusic();
}

/** @brief 停止音乐 */
void AudioManager::StopMusic() {
    Mix_HaltMusic();
}

/**
 * @brief 判断音乐是否正在播放
 * @return 播放中返回 true
 */
bool AudioManager::IsMusicPlaying() const noexcept {
    return Mix_PlayingMusic() != 0;
}

/**
 * @brief 播放音效（循环语义同样换算为 SDL_mixer 惯例）
 */
void AudioManager::PlayChunk(const ResourceManager& resourceMgr, std::string_view path, unsigned int loop) {
    Mix_Chunk* chunk = resourceMgr.GetChunk(path);
    if (!chunk) {
        std::cerr << "Failed to load chunk \"" << path << "\"" << std::endl;
        return;
    }
    Mix_PlayChannel(-1, chunk, static_cast<int>(loop) - 1);
}

/** @brief 暂停全部音效 */
void AudioManager::PauseChunk() {
    Mix_Pause(-1);
}

/** @brief 恢复全部音效 */
void AudioManager::ResumeChunk() {
    Mix_Resume(-1);
}

/** @brief 停止全部音效 */
void AudioManager::StopChunk() {
    Mix_HaltChannel(-1);
}

/**
 * @brief 判断是否有音效正在播放
 * @return 播放中返回 true
 */
bool AudioManager::IsChunkPlaying() const noexcept {
    return Mix_Playing(-1) != 0;
}