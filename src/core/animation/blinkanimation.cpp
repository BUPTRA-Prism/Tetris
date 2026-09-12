/**
 * @file blinkanimation.cpp
 * @brief 闪烁动画实现
 */
#include "core/animation/blinkanimation.h"

/**
 * @brief 构造闪烁动画
 */
BlinkAnimation::BlinkAnimation(int hideTotalFrame, int showTotalFrame, unsigned int totalLoop)
    : Animation(totalLoop)
    , m_hideTotalFrame(hideTotalFrame)
    , m_showTotalFrame(showTotalFrame)
    , m_completedFrame(0)
    , m_show(false) {}

/**
 * @brief 判断当前是否处于显示状态
 * @return 显示返回 true
 */
bool BlinkAnimation::IsShow() const noexcept {
    return m_show;
}

/**
 * @brief 推进隐藏/显示阶段的帧计数，阶段结束时切回并返回真表示一轮完成
 *
 * 每个隐藏阶段结束后进入显示阶段，显示阶段结束后进入隐藏阶段并返回 true
 */
bool BlinkAnimation::AdvanceFrame() {
    if (m_show) {
        if (m_completedFrame >= m_showTotalFrame) {
            m_show = false;
            m_completedFrame = 1;
            return true;
        }
        ++m_completedFrame;
    } else {
        if (m_completedFrame >= m_hideTotalFrame) {
            m_show = true;
            m_completedFrame = 1;
        } else {
            ++m_completedFrame;
        }
    }
    return false;
}

/** @brief 重置到动画初始状态 */
void BlinkAnimation::Reset() {
    m_completedFrame = 0;
    m_show = false;
}