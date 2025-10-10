#include "ui/optionicon.h"
#include "util/render.h"

OptionIcon::OptionIcon(Context& ctx, SDL_Texture* texture, std::function<SDL_Point(int)> func, int m_showFrameTarget, int m_hideFrameTarget, SDL_RendererFlip flip)
    : m_ctx(ctx)
    , m_texture(texture)
    , m_func(func)
    , m_anim(std::make_unique<BlinkAnimation>(-1, m_showFrameTarget, m_hideFrameTarget))
    , m_flip(flip) {}

void OptionIcon::playAnim() { m_anim->play(); }

void OptionIcon::stopAnim() { m_anim->stop(); }

void OptionIcon::onUpdate() { m_anim->onUpdate(); }

void OptionIcon::onRender(int idx) {
    SDL_Renderer* rdr = m_ctx.renderer;
    SDL_Point pos = m_func(idx);

    // 只有在动画处于显示状态时才渲染
    if (m_anim->isShow()) {
        renderTexture(rdr, m_texture, pos, nullptr, m_flip);
    }
}