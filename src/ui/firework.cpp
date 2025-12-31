#include "ui/firework.h"
#include "conf/resourceconf.h"
#include "conf/uiconf.h"
#include "util/random.h"
#include "util/render.h"

Firework::Firework(Context& ctx, const std::vector<SDL_Color>& colors, SDL_Rect m_border)
    : m_ctx(ctx)
    , m_colors(colors)
    , m_border(m_border)
    , m_frameTargets(FIREWORK::FRAME_TARGETS)
    , m_innerPosDelta(FIREWORK::INNER_POS_DELTA)
    , m_outerPosDelta(FIREWORK::OUTER_POS_DELTA) {}

void Firework::playAnim() {
    ResourceManager& rm = m_ctx.resourceManager;

    m_pos = SDL_Point { 
        selectRandom(m_border.x, m_border.x + m_border.w), 
        selectRandom(m_border.y, m_border.y + m_border.h)
    };

    std::vector<int> colorIdxs = selectRandomList(m_colors.size(), 3);
    std::vector<SDL_Color> colors = { m_colors[colorIdxs[0]],
                                      m_colors[colorIdxs[1]],
                                      m_colors[colorIdxs[2]] };

    std::vector<SDL_Texture*> innerFirework = {
        rm.getImage(INNER_FIREWORK_1_PATH),
        rm.getImage(INNER_FIREWORK_2_PATH),
        rm.getImage(INNER_FIREWORK_3_PATH),
        rm.getImage(INNER_FIREWORK_4_PATH),
        rm.getImage(INNER_FIREWORK_5_PATH)
    };    
    std::vector<SDL_Texture*> outerFirework = {
        rm.getImage(OUTER_FIREWORK_1_PATH),
        rm.getImage(OUTER_FIREWORK_2_PATH),
        rm.getImage(OUTER_FIREWORK_3_PATH),
        rm.getImage(OUTER_FIREWORK_4_PATH),
        rm.getImage(OUTER_FIREWORK_5_PATH)
    };                                

    std::vector<FrameAnimation::FrameData> innerClip;
    std::vector<FrameAnimation::FrameData> outerClip;

    for (int i = 0; i < innerFirework.size(); ++i) {
        if (i != innerFirework.size() - 1) {
            SDL_SetTextureColorMod(innerFirework[i], colors[0].r, colors[0].g, colors[0].b);
        } else {
            SDL_SetTextureColorMod(innerFirework[i], colors[1].r, colors[1].g, colors[1].b);
        }
        
        innerClip.emplace_back(
            FrameAnimation::FrameData {
                m_frameTargets[i], 
                innerFirework[i], 
                m_innerPosDelta[i]
            }
        );
    }

    for (int i = 0; i < outerFirework.size(); ++i) {
        if (i != outerFirework.size() - 1) {
            SDL_SetTextureColorMod(outerFirework[i], colors[1].r, colors[1].g, colors[1].b);
        } else {
            SDL_SetTextureColorMod(outerFirework[i], colors[2].r, colors[2].g, colors[2].b);
        }

        outerClip.emplace_back(
            FrameAnimation::FrameData {
                m_frameTargets[i], 
                outerFirework[i], 
                m_outerPosDelta[i]
            }
        );
    }

    m_innerAnim = std::make_unique<FrameAnimation>(innerClip, 1);
    m_outerAnim = std::make_unique<FrameAnimation>(outerClip, 1);

    m_innerAnim->play();
    m_outerAnim->play();
}

void Firework::stopAnim() {
    m_innerAnim->stop();
    m_outerAnim->stop();
}

bool Firework::isAnimPlaying() const {
    return m_innerAnim->isPlaying() && m_outerAnim->isPlaying();
}

void Firework::onUpdate() {
    m_innerAnim->onUpdate();
    m_outerAnim->onUpdate();
}

void Firework::onRender() { 
    SDL_Renderer* rdr = m_ctx.renderer;

    SDL_Texture* innerTexture = m_innerAnim->getCurrentTexture();
    SDL_Texture* outerTexture = m_outerAnim->getCurrentTexture();
    SDL_Point innerPosDelta = m_innerAnim->getCurrentPosDelta();
    SDL_Point outerPosDelta = m_outerAnim->getCurrentPosDelta();
    
    renderTexture(rdr, innerTexture, SDL_Point{m_pos.x + innerPosDelta.x, m_pos.y + innerPosDelta.y});
    renderTexture(rdr, outerTexture, SDL_Point{m_pos.x + outerPosDelta.x, m_pos.y + outerPosDelta.y});
}