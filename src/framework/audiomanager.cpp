#include "framework/audiomanager.h"

AudioManager::~AudioManager() {
    stopMusic();
    stopChunk();
}

void AudioManager::playMusic(Mix_Music* music, int loop) {
    if (music) {
        Mix_PlayMusic(music, loop);
    }
}

void AudioManager::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}

void AudioManager::resumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}

void AudioManager::stopMusic() {
    Mix_HaltMusic();
}

bool AudioManager::isPlayingMusic() {
    return Mix_PlayingMusic();
}

void AudioManager::playChunk(Mix_Chunk* chunk, int loop) {
    if (chunk) {
        Mix_PlayChannel(-1, chunk, loop);
    }
}

void AudioManager::pauseChunk() {
    Mix_Pause(-1);
}

void AudioManager::resumeChunk() {
    Mix_Resume(-1);
}

void AudioManager::stopChunk() {
    Mix_HaltChannel(-1);
}