#include "scene/scene.h"

Scene::Scene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback, SDL_Color bgColor)
    : m_ctx(ctx)
    , m_core(core)
    , m_loadSceneCallback(std::move(loadSceneCallback))
    , m_bgColor(bgColor) {}

SDL_Color Scene::getBGColor() const {
    return m_bgColor;
}