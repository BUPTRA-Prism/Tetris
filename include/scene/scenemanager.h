#pragma once

#include "scene/scene.h"

class SceneManager {
private:
    Context& m_ctx;
    Core& m_core;
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* m_curScene;

public:
    SceneManager(Context& ctx, Core& core);
    ~SceneManager() = default;

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    void onUpdate();
    void onRender();

private:
    void registerScene(const std::string& sceneName, std::unique_ptr<Scene> scene);
    void loadScene(const std::string& sceneName);
};