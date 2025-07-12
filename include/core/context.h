#pragma once

#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "manager/resourcemanager.h"

struct Context {
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    InputManager& inputManager;
    SDL_Renderer* renderer;

    Context(ResourceManager& rm, AudioManager& am, InputManager& im, SDL_Renderer* rdr);
};