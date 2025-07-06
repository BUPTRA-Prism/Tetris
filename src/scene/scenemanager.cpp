#include "conf/sceneconf.h"
#include "scene/scenemanager.h"
#include "scene/titlescene.h"
#include "scene/menuscene.h"
#include "scene/settingscene.h"
#include "scene/gamescene.h"
#include "scene/pausescene.h"
#include "scene/countscene.h"
#include <iostream>

SceneManager& SceneManager::getInstance(Context& ctx) {
    static SceneManager instance(ctx);
    return instance;
}

SceneManager::SceneManager(Context& ctx)
    : m_ctx(ctx)
    , m_curScene(nullptr) {
    auto loadSceneCallback = [this](const std::string& name) {
        this->loadScene(name);
    };
    registerScene(TITLE_SCENE::NAME, std::make_unique<TitleScene>(ctx, loadSceneCallback));
    registerScene(MENU_SCENE::NAME, std::make_unique<MenuScene>(ctx, loadSceneCallback));
    registerScene(SETTING_SCENE::NAME, std::make_unique<SettingScene>(ctx, loadSceneCallback));
    registerScene(GAME_SCENE::NAME, std::make_unique<GameScene>(ctx, loadSceneCallback));
    registerScene(PAUSE_SCENE::NAME, std::make_unique<PauseScene>(ctx, loadSceneCallback));
    registerScene(COUNT_SCENE::NAME, std::make_unique<CountScene>(ctx, loadSceneCallback));

    loadScene(TITLE_SCENE::NAME);
}

void SceneManager::onInput() {
    if (m_curScene) {
        m_curScene->onInput();
    }
}

void SceneManager::onUpdate() {
    if (m_curScene) {
        m_curScene->onUpdate();
    }
}

void SceneManager::onRender() {
    if (m_curScene) {
        m_curScene->onRender();
    }
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
    if (m_scenes.count(sceneName) != 0) {
        m_curScene = m_scenes.at(sceneName).get();
    }
    if (m_curScene) {
        m_curScene->onEnter();
    }
}