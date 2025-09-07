#include "animation/blinkanimation.h"

BlinkAnimation::BlinkAnimation(int loopTarget, int showFrameTarget, int hideFrameTarget)
    : Animation(loopTarget)
    , m_showFrameTarget(showFrameTarget)
    , m_hideFrameTarget(hideFrameTarget)
    , m_frameCnt(0)
    , m_show(true) {}

bool BlinkAnimation::isShow() const { return m_show; }

bool BlinkAnimation::update() {
    // 当前处于隐藏状态，并且隐藏持续时间已到，则认为完成一个完整的循环，返回 true
    if (!m_show && m_frameCnt >= m_hideFrameTarget) {
        return true;
    }
    
    // 当前处于显示状态，并且显示持续时间已到，则切换到隐藏状态，继续执行
    if (m_show && m_frameCnt >= m_showFrameTarget) {
        m_frameCnt = 0;
        m_show = false;
    } else {
        // 否则继续累计帧计数
        ++m_frameCnt;
    }
    // 此时循环尚未完成，返回 false
    return false;
}

void BlinkAnimation::reset() {
    // 帧计数清零
    m_frameCnt = 0;
    // 重置初始状态为显示
    m_show = true;
}