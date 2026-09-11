/**
 * @file render.h
 * @brief 渲染辅助函数与渲染参数结构
 */
#pragma once

#include "mysdl/wrapper.h"
#include <string_view>
#include <SDL2/SDL.h>

namespace MySDL {
    /**
     * @brief 纹理渲染参数
     */
    struct RenderParams {
        SDL_Point pos = { 0, 0 };                 ///< 绘制位置
        SDL_Color color = { 255, 255, 255, 255 }; ///< 颜色调制（RGB）
        SDL_RendererFlip flip = SDL_FLIP_NONE;    ///< 水平/垂直翻转
    };

    /**
     * @brief 将纹理按参数绘制到渲染器
     * @param renderer 渲染器
     * @param texture 纹理
     * @param rect 源矩形
     * @param params 渲染参数
     */
    void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect, const RenderParams& params);

    /**
     * @brief 将字符串渲染为纹理
     * @param renderer 渲染器
     * @param font 字体
     * @param str 字符串内容
     * @return 生成的纹理，失败或输入非法时返回空指针
     */
    UniqueTexture Font2Texture(SDL_Renderer* renderer, TTF_Font* font, std::string_view str);
}