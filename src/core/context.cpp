#include "core/context.h"

Context::Context(ResourceManager& rm, SDL_Renderer* rdr)
    : resourceManager(rm)
    , renderer(rdr) {}