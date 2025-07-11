#include "conf/basicconf.h"
#include "conf/resourceconf.h"
#include "ui/text.h"
#include "util/util.h"
#include <iostream>

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
    SDL_Texture* punctuationFont = rm.getFont(PUNCTUATION_FONT_PATH);
    SDL_SetTextureColorMod(digitFont, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureColorMod(letterFont, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureColorMod(punctuationFont, m_color.r, m_color.g, m_color.b);

    SDL_Renderer* rdr = m_ctx.renderer;
    for (int i = 0; i < m_str.length(); ++i) {
        SDL_Point dstPos = { m_pos.x + i * (FONT_SIZE + FONT_MARGIN), m_pos.y };
        if (m_str[i] >= '0' && m_str[i] <= '9') {
            SDL_Rect srcRect = { (m_str[i] - '0') * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
            renderTexture(rdr, digitFont, dstPos, &srcRect);
        } else if (m_str[i] >= 'A' && m_str[i] <= 'Z') {
            SDL_Rect srcRect = { (m_str[i] - 'A') * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
            renderTexture(rdr, letterFont, dstPos, &srcRect);
        } else {
            for (int j = 0; j < PUNCTUATION_LIST.length(); ++j) {
                if (m_str[i] == PUNCTUATION_LIST[j]) {
                    SDL_Rect srcRect = { j * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
                    renderTexture(rdr, punctuationFont, dstPos, &srcRect);
                }
            }
        }
        
    }
}