#include "core/context.h"

Context::Context(ResourceManager& rm, AudioManager& am, InputManager& im, SDL_Renderer* rdr)
    : resourceManager(rm)
    , audioManager(am)
    , inputManager(im)
    , renderer(rdr) {}