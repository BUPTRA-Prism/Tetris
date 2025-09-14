#pragma once

#include "scene/scene.h"

class GameScene : public Scene {
private:
    SDL_Texture* m_gameFrameTexture;

    Mix_Music* m_music;

public:
    GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};