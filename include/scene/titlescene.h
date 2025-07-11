#pragma once

#include "scene/scene.h"
#include "ui/text.h"

class TitleScene : public Scene {
private:
    SDL_Texture* m_titleFrameTexture;
    SDL_Texture* m_copyrightTexture;
    std::unique_ptr<Text> m_startText;
    std::unique_ptr<Text> m_yearText;
    Mix_Music* m_titleMusic;

public:
    TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~TitleScene() = default;

    void onEnter() override;
    void onExit() override;
    void onInput() override;
    void onUpdate() override;
    void renderContent() override;
};