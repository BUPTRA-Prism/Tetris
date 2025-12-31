#pragma once

#include <SDL_mixer.h>

class AudioManager {
public:
    AudioManager() = default;
    ~AudioManager();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) = delete;
    AudioManager& operator=(AudioManager&&) = delete;

    void playMusic(Mix_Music* music, int loop = -1);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    bool isPlayingMusic();

    void playChunk(Mix_Chunk* chunk, int loop = 0);
    void pauseChunk();
    void resumeChunk();
    void stopChunk();
};