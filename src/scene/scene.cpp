#include "scene/scene.h"

Scene::Scene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback, SDL_Color bgColor)
    : m_ctx(ctx)
    , m_loadSceneCallback(std::move(loadSceneCallback))
    , m_bgColor(bgColor) {}

void Scene::onRender() {
    renderBGColor();
    renderContent();
    SDL_RenderPresent(m_ctx.renderer);
}

void Scene::renderBGColor() {
    SDL_Renderer* rdr = m_ctx.renderer;
    SDL_SetRenderDrawColor(rdr, m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a);
    SDL_RenderClear(rdr);
}