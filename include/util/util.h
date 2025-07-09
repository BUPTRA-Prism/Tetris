#pragma once

#include <SDL.h>

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Point dstPos = { 0, 0 }, SDL_Rect* srcRect = nullptr);