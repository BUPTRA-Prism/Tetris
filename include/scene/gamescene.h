#pragma once

#include "scene/scene.h"
#include "ui/layout.h"
#include "ui/text.h"

class GameScene : public Scene {
private:
    SDL_Texture* m_gameFrameTexture;

    std::unique_ptr<VerticalLayout> m_tetrisTemplateLayout;
    std::unique_ptr<VerticalLayout> m_tetrisCountLayout;

    std::unique_ptr<Text> m_gameTypeTitle;
    std::vector<std::unique_ptr<Text>> m_tetrisCount;
    std::unique_ptr<Text> m_lineCount;
    std::unique_ptr<Text> m_topScoreTitle;
    std::unique_ptr<Text> m_topScore;
    std::unique_ptr<Text> m_scoreTitle;
    std::unique_ptr<Text> m_score;
    std::unique_ptr<Text> m_nextTetrisTitle;
    std::unique_ptr<Text> m_levelTitle;
    std::unique_ptr<Text> m_level;

    Mix_Music* m_music;

public:
    GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;

private:
    void initTetrisCount();
    void initScore();
};