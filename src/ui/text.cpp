#include "conf/basicconf.h"
#include "conf/resourceconf.h"
#include "ui/text.h"
#include "util/render.h"
#include <iostream>

Text::Text(Context& ctx, const std::string& str, SDL_Point pos, SDL_Color color)
    : m_ctx(ctx)
    , m_str(str)
    , m_color(color) 
    , m_layout(std::make_unique<HorizontalLayout>(pos, FONT_SPACING)){
}

void Text::setStr(const std::string& str) { m_str = str; }

void Text::setPos(SDL_Point pos) { m_layout = std::make_unique<HorizontalLayout>(pos, FONT_SPACING); }

void Text::setColor(SDL_Color color) { m_color = color; }

void Text::onRender() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 获取字体纹理
    SDL_Texture* digitFont = rm.getFont(DIGIT_FONT_PATH);
    SDL_Texture* letterFont = rm.getFont(LETTER_FONT_PATH);
    SDL_Texture* punctuationFont = rm.getFont(PUNCTUATION_FONT_PATH);

    // 设置字体颜色
    SDL_SetTextureColorMod(digitFont, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureColorMod(letterFont, m_color.r, m_color.g, m_color.b);
    SDL_SetTextureColorMod(punctuationFont, m_color.r, m_color.g, m_color.b);

    // 遍历文本字符并渲染
    SDL_Renderer* rdr = m_ctx.renderer;
    for (int i = 0; i < m_str.length(); ++i) {
        // 获取每个字符位置
        //SDL_Point dstPos = { m_pos.x + i * (FONT_SIZE + FONT_SPACING), m_pos.y };
        SDL_Point dstPos = m_layout->getElementPos(i);
        
        if (m_str[i] >= '0' && m_str[i] <= '9') {
            // 渲染数字字符
            SDL_Rect srcRect = { (m_str[i] - '0') * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
            renderTexture(rdr, digitFont, m_layout->getElementPos(i), &srcRect);
        } else if (m_str[i] >= 'A' && m_str[i] <= 'Z') {
            // 渲染大写字母
            SDL_Rect srcRect = { (m_str[i] - 'A') * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
            renderTexture(rdr, letterFont, m_layout->getElementPos(i), &srcRect);
        } else {
            // 渲染标点符号
            for (int j = 0; j < PUNCTUATION_LIST.length(); ++j) {
                if (m_str[i] == PUNCTUATION_LIST[j]) {
                    SDL_Rect srcRect = { j * FONT_SIZE, 0, FONT_SIZE, FONT_SIZE };
                    renderTexture(rdr, punctuationFont, m_layout->getElementPos(i), &srcRect);
                }
            }
        }
        
    }
}

HorizontalLayout* Text::getLayout() const { return m_layout.get(); }