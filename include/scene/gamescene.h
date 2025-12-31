#pragma once

#include "scene/scene.h"
#include "ui/text.h"

class GameScene : public Scene {
private:
    SDL_Texture* m_gameFrame;
    SDL_Texture* m_scoreboard;

    std::unique_ptr<Text> m_scoreText;
    std::unique_ptr<Text> m_scoreNum1;
    std::unique_ptr<Text> m_scoreNum2;
    std::unique_ptr<Text> m_lineText;
    std::unique_ptr<Text> m_lineNum1;
    std::unique_ptr<Text> m_lineNum2;
    std::unique_ptr<Text> m_levelText;
    std::unique_ptr<Text> m_levelNum1;
    std::unique_ptr<Text> m_levelNum2;

    std::unique_ptr<Text> m_nextText1;
    std::unique_ptr<Text> m_nextText2;

public:
    GameScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};