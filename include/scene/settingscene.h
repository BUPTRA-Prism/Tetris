#pragma once

#include "scene/scene.h"
#include "ui/text.h"

class SettingScene : public Scene {
private:
    SDL_Texture* m_settingFrameTexture;
    SDL_Texture* m_typeFrameTexture;

    std::unique_ptr<Text> m_gameTypeText; 

public:
    SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~SettingScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};