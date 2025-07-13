#include "animation/blinkanimation.h"

BlinkAnimation::BlinkAnimation(int loopTarget, int showFrameTarget, int hideFrameTarget)
    : Animation(loopTarget)
    , m_showFrameTarget(showFrameTarget)
    , m_hideFrameTarget(hideFrameTarget)
    , m_frameCnt(0)
    , m_show(true) {}

bool BlinkAnimation::isShow() const { return m_show; }

bool BlinkAnimation::update() {
    if (!m_show && m_frameCnt >= m_hideFrameTarget) {
        return true;
    }
    
    if (m_show && m_frameCnt >= m_showFrameTarget) {
        m_frameCnt = 0;
        m_show = false;
    } else {
        ++m_frameCnt;
    }
    return false;
}

void BlinkAnimation::reset() {
    m_frameCnt = 0;
    m_show = true;
}