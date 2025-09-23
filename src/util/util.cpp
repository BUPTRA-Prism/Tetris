#include "util/util.h"

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Point dstPos, SDL_Rect* srcRect, SDL_RendererFlip flip) {
    if (texture) {
        SDL_Rect dstRect = { dstPos.x, dstPos.y, 0, 0 };

        // 如果没有指定区域，则使用纹理原始区域
        if (!srcRect) {
            SDL_QueryTexture(texture, nullptr, nullptr, &(dstRect.w), &(dstRect.h));
        } else {
            dstRect.w = srcRect->w;
            dstRect.h = srcRect->h;
        }

        // 渲染纹理到目标位置，并应用翻转
        SDL_RenderCopyEx(renderer, texture, srcRect, &dstRect, 0.0, nullptr, flip);
    }
}

UniqueTexture createSolidTexture(SDL_Renderer* renderer, SDL_Color color, int w, int h) {
    // 创建可作为渲染目标的纹理
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (!texture) {
        return nullptr;
    }

    // 设置渲染目标为新纹理
    SDL_SetRenderTarget(renderer, texture);

    // 设置绘制颜色并清空纹理为纯色
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);

    // 恢复渲染目标为默认窗口
    SDL_SetRenderTarget(renderer, nullptr);

    return UniqueTexture(texture);
}

int getRandomInt(int min, int max) {
    // 使用静态变量，只初始化一次
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis;
    
    // 每次调用时使用相同的生成器，但重新设置分布范围
    return dis(gen, std::uniform_int_distribution<>::param_type(min, max));
}