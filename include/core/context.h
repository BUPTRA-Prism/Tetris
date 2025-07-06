#pragma once

#include "manager/resourcemanager.h"

struct Context {
    ResourceManager& m_resourceManager;
    SDL_Renderer* m_renderer;

    Context(ResourceManager& resourceManager, SDL_Renderer* renderer);
};