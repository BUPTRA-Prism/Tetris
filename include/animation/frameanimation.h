#pragma once

#include "animation/animation.h"
#include <vector>
#include <SDL.h>

class FrameAnimation : public Animation {
public:
    struct FrameData {
        int frameTarget;
        SDL_Texture* texture;
        SDL_Point posDelta;
    };

private:
    std::vector<FrameData> m_clip;
    int m_clipIdx;
    int m_frameCnt;

public:
    FrameAnimation(std::vector<FrameData>& clip, int loopTarget);
    ~FrameAnimation() = default;

    SDL_Texture* getCurrentTexture() const;
    SDL_Point getCurrentPosDelta() const;

private:
    bool update() override;
    void reset() override;
};