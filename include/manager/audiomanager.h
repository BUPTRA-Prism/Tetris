#pragma once

#include <SDL_mixer.h>

/**
 * @brief 音频管理器类，用于管理游戏中的音乐/音效播放
 *
 * 使用单例模式，保证全局唯一实例
 */
class AudioManager {
public:
    /**
     * @brief 获取音频管理器单例
     * @return AudioManager& 全局唯一实例
     */
    static AudioManager& getInstance();

    // 禁用拷贝与移动
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) = delete;
    AudioManager& operator=(AudioManager&&) = delete;

    /**
     * @brief 播放背景音乐
     * @param music 音乐资源指针
     * @param loop 循环次数，-1 表示无限循环，0 表示播放一次
     */
    void playMusic(Mix_Music* music, int loop = -1);
    /**
     * @brief 暂停当前播放的音乐
     */
    void pauseMusic();
    /**
     * @brief 恢复暂停的音乐
     */
    void resumeMusic();
    /**
     * @brief 停止音乐播放
     */
    void stopMusic();

    /**
     * @brief 播放音效
     * @param chunk 音效资源指针
     * @param loop 循环次数，默认 0 表示播放一次
     */
    void playChunk(Mix_Chunk* chunk, int loop = 0);
    /**
     * @brief 暂停当前播放的音效
     */
    void pauseChunk();
    /**
     * @brief 恢复暂停的音效
     */
    void resumeChunk();
    /**
     * @brief 停止音效播放
     */
    void stopChunk();

private:
    AudioManager() = default;   // 私有构造函数
    ~AudioManager() = default;  // 私有析构函数
};