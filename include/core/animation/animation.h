/**
 * @file animation.h
 * @brief 动画基类，封装播放状态机与循环计数
 */
#pragma once

/**
 * @brief 动画基类，管理播放状态与循环计数
 *
 * 循环语义与 AudioManager 保持一致：0 表示无限循环，1 表示单次播放
 */
class Animation {
private:
    /**
     * @brief 动画播放状态
     */
    enum class State {
        Stopped, ///< 已停止
        Playing, ///< 播放中
        Paused   ///< 已暂停
    };

    State m_state;              ///< 当前状态
    unsigned int m_totalLoop;   ///< 总循环次数（0 为无限）
    unsigned int m_completedLoop; ///< 已完成循环次数

public:
    /**
     * @brief 构造动画
     * @param totalLoop 总循环次数，0 表示无限循环
     */
    explicit Animation(unsigned int totalLoop = 0);
    virtual ~Animation() = default;

    /** @brief 更新一帧，推进循环状态 */
    void OnUpdate();
    /** @brief 开始播放并重置循环计数 */
    void Play();
    /** @brief 暂停播放 */
    void Pause();
    /** @brief 恢复播放 */
    void Resume();
    /** @brief 停止播放并重置循环计数 */
    void Stop();

    /**
     * @brief 判断是否已停止
     * @return 停止返回 true
     */
    bool IsStopped() const;

protected:
    /**
     * @brief 判断当前循环是否完成
     * @return 完成返回 true
     */
    virtual bool IsCycleComplete() = 0;
    /** @brief 重置当前循环到初始状态 */
    virtual void ResetCycle() = 0;
};