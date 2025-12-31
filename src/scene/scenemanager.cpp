#include "conf/uiconf.h"
#include "scene/scenemanager.h"
#include "scene/titlescene.h"
#include "scene/settingscene.h"
#include "scene/gamescene.h"
#include <iostream>

SceneManager::SceneManager(Context& ctx, Core& core)
    : m_ctx(ctx)
    , m_core(core)
    , m_curScene(nullptr) {
    auto loadSceneCallback = [this](const std::string& name) {
        this->loadScene(name);
    };

    registerScene(TITLE_SCENE::NAME, std::make_unique<TitleScene>(ctx, core, loadSceneCallback));
    registerScene(SETTING_SCENE::NAME, std::make_unique<SettingScene>(ctx, core, loadSceneCallback));
    registerScene(GAME_SCENE::NAME, std::make_unique<GameScene>(ctx, core, loadSceneCallback));

    loadScene(TITLE_SCENE::NAME);
}

void SceneManager::onUpdate() {
    if (m_curScene) {
        m_curScene->onUpdate();
    }
}

void SceneManager::onRender() {
    SDL_Renderer* rdr = m_ctx.renderer;

    SDL_Color bgColor = m_curScene ? m_curScene->getBGColor() : SDL_Color{ 0, 0, 0, 255 };
    SDL_SetRenderDrawColor(rdr, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderClear(rdr);

    if (m_curScene) {
        m_curScene->renderContent();
    }

    SDL_RenderPresent(rdr);
}

void SceneManager::registerScene(const std::string& sceneName, std::unique_ptr<Scene> scene) {
    if (m_scenes.count(sceneName) != 0) {
        std::cerr << "Duplicate Scene" << std::endl;
        return;
    }
    m_scenes.emplace(sceneName, std::move(scene));
}

void SceneManager::loadScene(const std::string& sceneName) {
    if (m_curScene) {
        m_curScene->onExit();
    }

    auto it = m_scenes.find(sceneName);
    m_curScene = it != m_scenes.end() ? it->second.get() : nullptr;

    if (m_curScene) {
        m_curScene->onEnter();
    }
}