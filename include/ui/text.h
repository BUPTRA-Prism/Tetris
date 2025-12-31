#pragma once

#include "framework/context.h"

class Text {
private:
    Context& m_ctx;
    std::string m_str;
    SDL_Point m_pos;
    SDL_Color m_color;

public:
    Text(Context& ctx, const std::string& str, SDL_Point pos, SDL_Color color = {255, 255, 255, 255});
    ~Text() = default;

    void setStr(const std::string& str);
    void setPos(SDL_Point pos);
    void setColor(SDL_Color color);

    void onRender();
};