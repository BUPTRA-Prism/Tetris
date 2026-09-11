/**
 * @file scene.cpp
 * @brief 场景基类实现
 */
#include "scene/scene.h"
#include <utility>

/**
 * @brief 构造场景
 */
Scene::Scene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback, SDL_Color bgColor)
    : m_ctx(ctx)
    , m_loadSceneCallback(std::move(loadSceneCallback))
    , m_bgColor(bgColor) {}

/**
 * @brief 获取背景色
 * @return 背景色
 */
SDL_Color Scene::GetBGColor() const noexcept {
    return m_bgColor;
}