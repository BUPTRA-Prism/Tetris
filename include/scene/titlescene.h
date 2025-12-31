#pragma once

#include "scene/scene.h"
#include "ui/text.h"
#include "ui/firework.h"


class TitleScene : public Scene {
private:
    SDL_Texture* m_titleFrame;
    SDL_Texture* m_titleImg;

    std::unique_ptr<Text> m_titleText;
    std::unique_ptr<Firework> m_firework;

    Mix_Music* m_music;
    Mix_Chunk* m_nextSceneChunk;

    int m_fireworkCnt;
    int m_fireworkCreateFrameCnt;

public:
    TitleScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback);
    ~TitleScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};