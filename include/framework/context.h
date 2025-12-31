#pragma once

#include "framework/audiomanager.h"
#include "framework/inputmanager.h"
#include "framework/resourcemanager.h"
#include "game/settings.h"

struct Context {
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    InputManager& inputManager;
    SDL_Renderer* renderer;

    Context(ResourceManager& rm, AudioManager& am, InputManager& im, SDL_Renderer* rdr);
};