/**
 * @file render.cpp
 * @brief 渲染辅助函数实现
 */
#include "mysdl/render.h"
#include <string>
#include <SDL2/SDL_ttf.h>
#include <iostream>

/**
 * @brief 将纹理按参数绘制到渲染器
 *
 * 仅在颜色/透明度偏离默认值时进行调制，并在绘制后恢复默认值，
 * 避免纹理调制状态泄漏到后续绘制
 */
void MySDL::RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, const RenderParams& params) {
    if (renderer && texture) {
        SDL_Rect dst = {params.pos.x, params.pos.y, rect.w, rect.h};

        bool needChangeColor = params.color.r != 255 || params.color.g != 255 || params.color.b != 255;
        bool needChangeAlpha = params.color.a != 255;
        
        if (needChangeColor) {
            SDL_SetTextureColorMod(texture, params.color.r, params.color.g, params.color.b);
        }
        if (needChangeAlpha) {
            SDL_SetTextureAlphaMod(texture, params.color.a);
        }
        
        SDL_RenderCopyEx(renderer, texture, &rect, &dst, 0.0, nullptr, params.flip);

        if (needChangeColor) {
            SDL_SetTextureColorMod(texture, 255, 255, 255);
        }
        if (needChangeAlpha) {
            SDL_SetTextureAlphaMod(texture, 255);
        }
    }
}

/**
 * @brief 将字符串渲染为纹理
 * @return 生成的纹理，失败或输入非法时返回空指针
 */
MySDL::UniqueTexture MySDL::Str2Texture(SDL_Renderer* renderer, TTF_Font* font, std::string_view str) {
    if (renderer && font && !str.empty()) {
        MySDL::UniqueSurface surface(TTF_RenderText_Solid(font, std::string(str).c_str(), SDL_Color{ 255, 255, 255, 255 }));
        if (!surface) {
            std::cerr << "TTF_RenderText_Solid failed: " << TTF_GetError() << std::endl;
            return nullptr;
        }

        MySDL::UniqueTexture texture(SDL_CreateTextureFromSurface(renderer, surface.get()));
        if (!texture) {
            std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        }
        return texture;
    }

    return nullptr;
}