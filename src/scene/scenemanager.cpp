/**
 * @file scenemanager.cpp
 * @brief 场景管理器实现
 */
#include "scene/scenemanager.h"
#include "config/ui.h"
#include "framework/context.h"
#include "scene/titlescene.h"
#include "scene/menuscene.h"
#include "scene/settingscene.h"
#include "scene/gamescene.h"
#include "scene/rankscene.h"
#include <utility>
#include <SDL2/SDL.h>
#include <iostream>

/**
 * @brief 构造并注册所有场景，随后加载标题场景
 */
SceneManager::SceneManager(Context& ctx)
    : m_ctx(ctx)
    , m_curScene(nullptr) {
    auto loadSceneCallback = [this](std::string_view name) {
        this->LoadScene(name);
    };

    RegisterScene(Config::TitleSceneUI::NAME, std::make_unique<TitleScene>(ctx, loadSceneCallback));
    RegisterScene(Config::MenuSceneUI::NAME, std::make_unique<MenuScene>(ctx, loadSceneCallback));
    RegisterScene(Config::SettingSceneUI::NAME, std::make_unique<SettingScene>(ctx, loadSceneCallback));
    RegisterScene(Config::GameSceneUI::NAME, std::make_unique<GameScene>(ctx, loadSceneCallback));
    RegisterScene(Config::RankSceneUI::NAME, std::make_unique<RankScene>(ctx, loadSceneCallback));

    LoadScene(Config::TitleSceneUI::NAME);
}

/**
 * @brief 更新当前场景逻辑
 */
void SceneManager::OnUpdate() {
    if (m_curScene) {
        m_curScene->OnUpdate();
    }
}

/**
 * @brief 渲染当前场景（清屏、绘制内容并提交）
 */
void SceneManager::OnRender() {
    SDL_Renderer* renderer = m_ctx.renderer;

    if (renderer) {
        SDL_Color bgColor = m_curScene ? m_curScene->GetBGColor() : SDL_Color{0, 0, 0, 255};
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        if (m_curScene) {
            m_curScene->RenderContent();
        }

        SDL_RenderPresent(renderer);
    }
}

/**
 * @brief 注册场景（重复注册将被忽略）
 */
void SceneManager::RegisterScene(std::string_view name, std::unique_ptr<Scene> scene) {
    if (m_scenes.count(name) != 0) {
        std::cerr << "Duplicate Scene" << std::endl;
        return;
    }
    m_scenes.emplace(name, std::move(scene));
}

/**
 * @brief 加载指定场景，先退出当前场景再进入新场景
 */
void SceneManager::LoadScene(std::string_view name) {
    if (m_curScene) {
        m_curScene->OnExit();
    }

    auto it = m_scenes.find(name);
    m_curScene = it != m_scenes.end() ? it->second.get() : nullptr;

    if (m_curScene) {
        m_curScene->OnEnter();
    }
}