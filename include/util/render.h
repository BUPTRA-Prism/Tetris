#pragma once

#include "sdlresource.h"
#include <SDL.h>

void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Point dstPos = { 0, 0 }, SDL_Rect* srcRect = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);