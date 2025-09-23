#pragma once

#include "scene/scene.h"
#include "core/game.h"
#include "ui/layout.h"
#include "ui/text.h"

class GameScene : public Scene {
private:
    enum class Status {
        Generate,
        Move,
        Calculate,
        GameOver
    };

    SDL_Texture* m_gameFrameTexture;

    std::unique_ptr<VerticalLayout> m_tetrisTemplateLayout;
    std::unique_ptr<VerticalLayout> m_tetrisCountLayout;

    std::unique_ptr<Text> m_gameTypeTitle;
    std::unordered_map<TetrisMode, std::unique_ptr<Text>> m_tetrisCount;
    std::unique_ptr<Text> m_lineCount;
    std::unique_ptr<Text> m_topScoreTitle;
    std::unique_ptr<Text> m_topScore;
    std::unique_ptr<Text> m_scoreTitle;
    std::unique_ptr<Text> m_score;
    std::unique_ptr<Text> m_nextTetrisTitle;
    std::unique_ptr<Text> m_levelTitle;
    std::unique_ptr<Text> m_level;

    Mix_Music* m_music;

    Game m_game;

    int m_dasFrameTarget;
    int m_arrFrameTarget;
    int m_moveFrameCnt;
    int m_dropFrameTarget;
    int m_accelerateFrameTarget;
    int m_dropFrameCnt;
    int m_eraseFrameTarget;
    int m_eraseFrameCnt;
    int m_nextFrameTarget;
    int m_nextFrameCnt;

    Status m_curStatus;

public:
    GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};