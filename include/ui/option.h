#pragma once

#include "animation/blinkanimation.h"
#include "core/context.h"

class Option {
private:
    Context& m_ctx;
    const std::vector<SDL_Point>& m_pos;
    SDL_Texture* m_texture;
    std::unique_ptr<BlinkAnimation> m_anim;

public:
    Option(Context& ctx, SDL_Texture* texture, const std::vector<SDL_Point>& pos, int m_showFrameTarget, int m_hideFrameTarget);
    ~Option() = default;

    void playAnim();
    void stopAnim();
    void onUpdate();
    void onRender(int posIdx, bool isFlip);
};