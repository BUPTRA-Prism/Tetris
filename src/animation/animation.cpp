#include "animation/animation.h"

Animation::Animation(int loopTarget)
    : m_playing(false)
    , m_loopTarget(loopTarget)
    , m_loopCnt(0) {}

void Animation::onUpdate() {
    if (!m_playing) {
        return;
    }

    if (m_loopTarget != -1 && m_loopCnt >= m_loopTarget) {
        m_playing = false;
        return;
    }

    if (update()) {
        if (m_loopTarget != -1) {
            ++m_loopCnt;
        }
        if (m_loopTarget == -1 || m_loopCnt < m_loopTarget) {
            reset();
        }
    }
}

void Animation::play() { m_playing = true; }

void Animation::pause() { m_playing = false; }

void Animation::stop() {
    m_playing = false;
    m_loopCnt = 0;
    reset();
}

bool Animation::isPlaying() const { 
    return m_playing; 
}