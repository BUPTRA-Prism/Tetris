#pragma once

#include "scene/scene.h"

class PauseScene : public Scene {
private:

public:
    PauseScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~PauseScene() = default;

    void onEnter() override;
    void onExit() override;
    void onInput() override;
    void onUpdate() override;
    void renderContent() override;
};