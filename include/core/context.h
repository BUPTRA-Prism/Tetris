#pragma once

#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "manager/resourcemanager.h"
#include "core/settings.h"

struct Context {
    ResourceManager& resourceManager;
    AudioManager& audioManager;
    InputManager& inputManager;
    Settings& settings;
    SDL_Renderer* renderer;

    Context(ResourceManager& rm, AudioManager& am, InputManager& im, Settings& s, SDL_Renderer* rdr);
};