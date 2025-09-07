#include "scene/scene.h"

Scene::Scene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback, SDL_Color bgColor)
    : m_ctx(ctx)
    , m_loadSceneCallback(std::move(loadSceneCallback))
    , m_bgColor(bgColor) {}

void Scene::onRender() {
    renderBGColor();    // 渲染背景颜色
    renderContent();    // 渲染具体场景内容
    SDL_RenderPresent(m_ctx.renderer);  // 提交渲染到屏幕
}

void Scene::renderBGColor() {
    SDL_Renderer* rdr = m_ctx.renderer;
    // 设置绘制颜色
    SDL_SetRenderDrawColor(rdr, m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a);
    // 清空渲染器为背景颜色
    SDL_RenderClear(rdr);
}