/**
 * @file audiomanager.h
 * @brief 音频管理器，隔离场景与 SDL_mixer 的直接调用
 */
#pragma once

#include <string_view>

class ResourceManager;

/**
 * @brief 音频管理器，封装音乐与音效的播放控制
 *
 * 循环语义与 Animation 保持一致：0 表示无限循环，1 表示单次播放，
 * SDL_mixer 内部循环参数的换算在此处完成
 */
class AudioManager {
public:
    AudioManager() = default;
    ~AudioManager() = default;

    AudioManager(const AudioManager& manager) = delete;
    AudioManager& operator=(const AudioManager& manager) = delete;
    AudioManager(AudioManager&& manager) = delete;
    AudioManager& operator=(AudioManager&& manager) = delete;

    /**
     * @brief 播放音乐
     * @param resourceMgr 资源管理器
     * @param path 音乐资源路径
     * @param loop 循环次数（0 为无限，1 为单次）
     */
    void PlayMusic(ResourceManager& resourceMgr, std::string_view path, unsigned int loop = 0);
    /** @brief 暂停音乐 */
    void PauseMusic();
    /** @brief 恢复音乐 */
    void ResumeMusic();
    /** @brief 停止音乐 */
    void StopMusic();

    /**
     * @brief 判断音乐是否正在播放
     * @return 播放中返回 true
     */
    bool IsMusicPlaying() const;

    /**
     * @brief 播放音效
     * @param resourceMgr 资源管理器
     * @param path 音效资源路径
     * @param loop 循环次数（1 为单次）
     */
    void PlayChunk(ResourceManager& resourceMgr, std::string_view path, unsigned int loop = 1);
    /** @brief 暂停音效 */
    void PauseChunk();
    /** @brief 恢复音效 */
    void ResumeChunk();
    /** @brief 停止音效 */
    void StopChunk();
};