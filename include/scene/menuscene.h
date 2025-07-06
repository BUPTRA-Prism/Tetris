#pragma once

#include "scene/scene.h"

class MenuScene : public Scene {
private:

public:
    MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~MenuScene() = default;

    void onEnter() override;
    void onExit() override;
    void onInput() override;
    void onUpdate() override;
    void renderContent() override;
};