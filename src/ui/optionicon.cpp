#include "ui/optionicon.h"
#include "util/util.h"

OptionIcon::OptionIcon(Context& ctx, SDL_Texture* texture, const std::vector<SDL_Point>& pos, int m_showFrameTarget, int m_hideFrameTarget)
    : m_ctx(ctx)
    , m_texture(texture)
    , m_pos(pos)
    , m_anim(std::make_unique<BlinkAnimation>(-1, m_showFrameTarget, m_hideFrameTarget)) {}

void OptionIcon::playAnim() { m_anim->play(); }

void OptionIcon::stopAnim() { m_anim->stop(); }

void OptionIcon::onUpdate() { m_anim->onUpdate(); }

void OptionIcon::onRender(int posIdx, bool isFlip) {
    SDL_Renderer* rdr = m_ctx.renderer;
    SDL_Point pos = m_pos[posIdx];

    // 只有在动画处于显示状态时才渲染
    if (m_anim->isShow()) {
        if (isFlip) {
            renderTexture(rdr, m_texture, pos, nullptr, SDL_FLIP_HORIZONTAL);
        } else {
            renderTexture(rdr, m_texture, pos);
        }
    }
}