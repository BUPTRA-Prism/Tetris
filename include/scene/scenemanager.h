#pragma once

#include "scene/scene.h"
#include <memory>
#include <string>
#include <unordered_map>

class SceneManager {
private:
    Context& m_ctx;
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* m_curScene;

public:
    static SceneManager& getInstance(Context& ctx);

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    void onUpdate();
    void onRender();

private:
    SceneManager(Context& ctx);
    ~SceneManager() = default;

    void registerScene(const std::string& sceneName, std::unique_ptr<Scene> scene);
    void loadScene(const std::string& sceneName);
};