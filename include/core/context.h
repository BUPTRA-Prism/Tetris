#pragma once

#include "manager/resourcemanager.h"

struct Context {
    ResourceManager& resourceManager;
    SDL_Renderer* renderer;

    Context(ResourceManager& rm, SDL_Renderer* rdr);
};