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
    // lambda 回调，用于场景之间切换
    auto loadSceneCallback = [this](const std::string& name) {
        this->loadScene(name);
    };

    // 注册场景
    registerScene(TITLE_SCENE::NAME, std::make_unique<TitleScene>(ctx, loadSceneCallback));
    registerScene(MENU_SCENE::NAME, std::make_unique<MenuScene>(ctx, loadSceneCallback));
    registerScene(SETTING_SCENE::NAME, std::make_unique<SettingScene>(ctx, loadSceneCallback));
    registerScene(GAME_SCENE::NAME, std::make_unique<GameScene>(ctx, loadSceneCallback));
    registerScene(PAUSE_SCENE::NAME, std::make_unique<PauseScene>(ctx, loadSceneCallback));
    registerScene(COUNT_SCENE::NAME, std::make_unique<CountScene>(ctx, loadSceneCallback));

    // 加载初始场景
    loadScene(TITLE_SCENE::NAME);
}

void SceneManager::onUpdate() {
    if (m_curScene) {
        // 调用当前场景更新函数
        m_curScene->onUpdate();
    }
}

void SceneManager::onRender() {
    if (m_curScene) {
        // 调用当前场景渲染函数
        m_curScene->onRender();
    }
}

void SceneManager::registerScene(const std::string& sceneName, std::unique_ptr<Scene> scene) {
    // 防止重复注册
    if (m_scenes.count(sceneName) != 0) {
        std::cerr << "Duplicate Scene" << std::endl;
        return;
    }
    m_scenes.emplace(sceneName, std::move(scene));
}

void SceneManager::loadScene(const std::string& sceneName) {
    // 如果有当前场景，先退出
    if (m_curScene) {
        m_curScene->onExit();
    }

    // 查找并切换至新场景
    if (m_scenes.count(sceneName) != 0) {
        m_curScene = m_scenes.at(sceneName).get();
    }

    // 如果成功切换，调用新场景进入函数
    if (m_curScene) {
        m_curScene->onEnter();
    }
}