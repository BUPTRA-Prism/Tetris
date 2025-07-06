#include "core/context.h"

Context::Context(ResourceManager& resourceManager, SDL_Renderer* renderer)
    : m_resourceManager(resourceManager)
    , m_renderer(renderer)
    {}