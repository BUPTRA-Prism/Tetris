#pragma once

#include "scene/scene.h"

class CountScene : public Scene {
private:

public:
    CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~CountScene() = default;

    void onEnter() override;
    void onExit() override;
    void onInput() override;
    void onUpdate() override;
    void renderContent() override;
};