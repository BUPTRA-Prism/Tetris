#include "util/render.h"

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Point dstPos, SDL_Rect* srcRect, SDL_RendererFlip flip) {
    if (texture) {
        SDL_Rect dstRect = { dstPos.x, dstPos.y, 0, 0 };

        if (!srcRect) {
            SDL_QueryTexture(texture, nullptr, nullptr, &(dstRect.w), &(dstRect.h));
        } else {
            dstRect.w = srcRect->w;
            dstRect.h = srcRect->h;
        }

        SDL_RenderCopyEx(renderer, texture, srcRect, &dstRect, 0.0, nullptr, flip);
    }
}