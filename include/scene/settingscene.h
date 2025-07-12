#pragma once

#include "scene/scene.h"

class SettingScene : public Scene {
private:

public:
    SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~SettingScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};