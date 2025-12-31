#include "animation/frameanimation.h"

FrameAnimation::FrameAnimation(std::vector<FrameData>& clip, int loopTarget)
    : Animation(loopTarget)
    , m_clip(clip)
    , m_clipIdx(0)
    , m_frameCnt(0) {}

SDL_Texture* FrameAnimation::getCurrentTexture() const {
    return m_clip[m_clipIdx].texture;
}

SDL_Point FrameAnimation::getCurrentPosDelta() const {
    return m_clip[m_clipIdx].posDelta;
}

bool FrameAnimation::update() {
    if (m_frameCnt == m_clip[m_clipIdx].frameTarget) {
        if (m_clipIdx == m_clip.size() - 1) {
            return true;
        } else {
            ++m_clipIdx;
            m_frameCnt = 0;
        }
    } else {
        ++m_frameCnt;
    }
    
    return false;
}

void FrameAnimation::reset() {
    m_clipIdx = 0;
    m_frameCnt = 0;
}