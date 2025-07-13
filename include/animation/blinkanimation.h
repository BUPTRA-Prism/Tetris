#pragma once

#include "animation/animation.h"

class BlinkAnimation : public Animation {
private:
    int m_showFrameTarget;
    int m_hideFrameTarget;
    int m_frameCnt;
    bool m_show;

public:
    BlinkAnimation(int loopTarget, int showGrameTarget, int hideFrameTarget);
    ~BlinkAnimation() = default;

    bool isShow() const;

private:
    bool update() override;
    void reset() override;
};