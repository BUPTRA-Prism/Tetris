#include "ui/text.h"
#include "conf/resourceconf.h"
#include "conf/uiconf.h"
#include "util/render.h"

Text::Text(Context& ctx, const std::string& str, SDL_Point pos, SDL_Color color)
    : m_ctx(ctx)
    , m_str(str)
    , m_pos(pos)
    , m_color(color) {}

void Text::setStr(const std::string& str) { m_str = str; }

void Text::setPos(SDL_Point pos) { m_pos = pos; }

void Text::setColor(SDL_Color color) { m_color = color; }

void Text::onRender() {
    ResourceManager& rm = m_ctx.resourceManager;

    SDL_Texture* digitFont = rm.getFont(DIGIT_FONT_PATH);
    SDL_Texture* letterFont = rm.getFont(LETTER_FONT_PATH);

    SDL_SetTextureColorMod(digitFont, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureColorMod(letterFont, m_color.r, m_color.g, m_color.b);

    SDL_Renderer* rdr = m_ctx.renderer;
    for (int i = 0; i < m_str.length(); ++i) {
        SDL_Point dstPos = { m_pos.x + i * FONT::SPACING, m_pos.y };
        
        if (m_str[i] >= '0' && m_str[i] <= '9') {
            SDL_Rect srcRect = { (m_str[i] - '0') * FONT::SIZE, 0, FONT::SIZE, FONT::SIZE };
            renderTexture(rdr, digitFont, dstPos, &srcRect);
        } else if (m_str[i] >= 'A' && m_str[i] <= 'Z') {
            SDL_Rect srcRect = { (m_str[i] - 'A') * FONT::SIZE, 0, FONT::SIZE, FONT::SIZE };
            renderTexture(rdr, letterFont, dstPos, &srcRect);
        }
    }
}