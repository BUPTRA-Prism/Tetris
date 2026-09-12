/**
 * @file animation.cpp
 * @brief 动画基类实现
 */
#include "core/animation/animation.h"

/**
 * @brief 构造动画
 * @param totalLoop 总循环次数（0 为无限）
 */
Animation::Animation(unsigned int totalLoop)
    : m_state(State::Stopped)
    , m_totalLoop(totalLoop)
    , m_completedLoop(0) {}

/**
 * @brief 更新一帧，推进循环状态
 *
 * 仅播放中推进：当一轮循环完成时累加计数（非无限循环），
 * 达到总次数后停止，并重置动画
 */
void Animation::OnUpdate() {
    if (m_state != State::Playing) {
        return;
    }

    if (AdvanceFrame()) {
        if (m_totalLoop != 0) {
            ++m_completedLoop;
            if (m_completedLoop >= m_totalLoop) {
                Stop();
            }
        }
    }
}

/** @brief 开始播放并重置动画 */
void Animation::Play() {
    m_state = State::Playing;
    m_completedLoop = 0;
    Reset();
}

/** @brief 暂停播放（仅当播放中） */
void Animation::Pause() {
    if (m_state == State::Playing) {
        m_state = State::Paused;
    }
}

/** @brief 恢复播放（仅当暂停中） */
void Animation::Resume() {
    if (m_state == State::Paused) {
        m_state = State::Playing;
    }
}

/** @brief 停止播放并重置循环计数 */
void Animation::Stop() {
    m_state = State::Stopped;
    m_completedLoop = 0;
    Reset();
}

/**
 * @brief 判断是否已停止
 * @return 停止返回 true
 */
bool Animation::IsStopped() const noexcept {
    return m_state == State::Stopped;
}