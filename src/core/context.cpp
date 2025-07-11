#include "core/context.h"

Context::Context(ResourceManager& rm, AudioManager& am, SDL_Renderer* rdr)
    : resourceManager(rm)
    , audioManager(am)
    , renderer(rdr) {}