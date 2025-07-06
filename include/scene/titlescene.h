#pragma once

#include "scene/scene.h"

class TitleScene : public Scene {
private:

public:
    TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~TitleScene() = default;

    void onEnter() override;
    void onExit() override;
    void onInput() override;
    void onUpdate() override;
    void renderContent() override;
};