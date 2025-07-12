#pragma once

#include "scene/scene.h"
#include "ui/text.h"

class MenuScene : public Scene {
private:
    SDL_Texture* m_menuFrameTexture;

    std::unique_ptr<Text> m_gameTypeTitleText;
    std::vector<std::unique_ptr<Text>> m_gameTypeText;
    std::unique_ptr<Text> m_musicTypeTitleText;
    std::vector<std::unique_ptr<Text>> m_musicTypeText;

    Mix_Music* m_music;
    Mix_Chunk* m_optionChunk;

public:
    MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~MenuScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};