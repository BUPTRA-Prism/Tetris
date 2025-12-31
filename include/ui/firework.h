#pragma once

#include "animation/frameanimation.h"
#include "framework/context.h"
#include <memory>

class Firework {
private:
    Context& m_ctx;
    std::vector<SDL_Color> m_colors;
    SDL_Rect m_border;
    SDL_Point m_pos;

    std::vector<int> m_frameTargets;
    std::vector<SDL_Point> m_innerPosDelta;
    std::vector<SDL_Point> m_outerPosDelta;

    std::unique_ptr<FrameAnimation> m_innerAnim;
    std::unique_ptr<FrameAnimation> m_outerAnim;

public:
    Firework(Context& ctx, const std::vector<SDL_Color>& colors, SDL_Rect m_border);
    ~Firework() = default;

    void playAnim();
    void stopAnim();
    bool isAnimPlaying() const;
    
    void onUpdate();
    void onRender();
};