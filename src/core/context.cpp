#include "core/context.h"

Context::Context(ResourceManager& rm, AudioManager& am, InputManager& im, Settings& s, SDL_Renderer* rdr)
    : resourceManager(rm)
    , audioManager(am)
    , inputManager(im)
    , settings(s)
    , renderer(rdr) {}