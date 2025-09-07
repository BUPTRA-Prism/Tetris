#include "animation/animation.h"

Animation::Animation(int loopTarget)
    : m_playing(false)
    , m_loopTarget(loopTarget)
    , m_loopCnt(0) {}

void Animation::onUpdate() {
    // 动画只有处于播放状态时，才执行更新操作
    if (!m_playing) {
        return;
    }

    // 如果不是无限循环的动画，且当前循环次数已经达到循环上限，说明动画已不处于播放状态
    if (m_loopTarget != -1 && m_loopCnt >= m_loopTarget) {
        m_playing = false;
        return;
    }

    // 动画更新
    if (update()) {
        // 如果已完成一轮循环，且动画不是无限循环，累加循环次数
        if (m_loopTarget != -1) {
            ++m_loopCnt;
        }
        // 动画复位
        reset();
    }
}

void Animation::play() { m_playing = true; }

void Animation::pause() { m_playing = false; }

void Animation::stop() {
    // 动画已不处于播放状态
    m_playing = false;
    // 循环次数清空
    m_loopCnt = 0;
    // 动画复位
    reset();
}