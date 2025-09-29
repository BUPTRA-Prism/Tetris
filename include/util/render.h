#pragma once

#include "sdlresource.h"
#include <SDL.h>

/**
 * @brief 在窗口指定位置渲染纹理
 * @param renderer SDL 渲染器
 * @param texture SDL 纹理
 * @param dstPos 目标位置左上角坐标，默认为窗口左上
 * @param srcRect 源纹理渲染区域，默认为 nullptr ，表示整个纹理区域
 * @param flip 纹理翻转方式，默认不翻转
*/
void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Point dstPos = { 0, 0 }, SDL_Rect* srcRect = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

/**
 * @brief 创建纯色块纹理
 * @param renderer SDL 渲染器
 * @param color 颜色
 * @param w 色块宽度
 * @param h 色块高度
 * @return UniqueTexture 管理 SDL_Texture 的智能指针，创建失败返回 nullptr
*/
UniqueTexture createSolidTexture(SDL_Renderer* renderer, SDL_Color color, int w, int h);