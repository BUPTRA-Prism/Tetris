#include "ui/option.h"
#include "util/util.h"

Option::Option(Context& ctx, SDL_Texture* texture, const std::vector<SDL_Point>& pos, int m_showFrameTarget, int m_hideFrameTarget)
    : m_ctx(ctx)
    , m_texture(texture)
    , m_pos(pos)
    , m_anim(std::make_unique<BlinkAnimation>(-1, m_showFrameTarget, m_hideFrameTarget)) {}

void Option::playAnim() { m_anim->play(); }

void Option::stopAnim() { m_anim->stop(); }

void Option::onUpdate() { m_anim->onUpdate(); }

void Option::onRender(int posIdx, bool isFlip) {
    SDL_Renderer* rdr = m_ctx.renderer;
    SDL_Point pos = m_pos[posIdx];
    if (m_anim->isShow()) {
        if (isFlip) {
            renderTexture(rdr, m_texture, pos, nullptr, SDL_FLIP_HORIZONTAL);
        } else {
            renderTexture(rdr, m_texture, pos);
        }
    }
}