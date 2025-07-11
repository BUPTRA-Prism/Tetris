#pragma once

#include "manager/audiomanager.h"
#include "manager/resourcemanager.h"

struct Context {
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    SDL_Renderer* renderer;

    Context(ResourceManager& rm, AudioManager& am, SDL_Renderer* rdr);
};