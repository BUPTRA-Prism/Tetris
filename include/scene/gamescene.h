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
        Check,
        Erase,
        Calculate,
        Win, 
        Lose
    };

    SDL_Texture* m_gameFrameTexture;

    std::unique_ptr<VerticalLayout> m_tetrisModeLayout;
    std::unique_ptr<VerticalLayout> m_tetrisCountLayout;
    std::unique_ptr<GridLayout> m_tetrisFieldLayout;

    std::unique_ptr<Text> m_gameTypeTitle;
    std::unordered_map<TetrisMode, std::unique_ptr<Text>> m_tetrisCountText;
    std::unique_ptr<Text> m_lineCountText;
    std::unique_ptr<Text> m_topScoreTitle;
    std::unique_ptr<Text> m_topScoreText;
    std::unique_ptr<Text> m_scoreTitle;
    std::unique_ptr<Text> m_scoreText;
    std::unique_ptr<Text> m_nextTetrisTitle;
    std::unique_ptr<Text> m_levelTitle;
    std::unique_ptr<Text> m_levelText;
    std::unique_ptr<Text> m_resultText;

    UniqueTexture m_tetrisBasicTexture;
    UniqueTexture m_tetrisModeBasicTexture;
    SDL_Texture* m_tetrisSolidPatternTexture;
    SDL_Texture* m_tetrisHollowPatternTexture;
    SDL_Texture* m_tetrisModeSolidPatternTexture;
    SDL_Texture* m_tetrisModeHollowPatternTexture;
    SDL_Texture* m_resultOuterFrameTexture;
    SDL_Texture* m_resultInnerFrameTexture;

    Mix_Music* m_music;
    Mix_Music* m_winMusic;
    Mix_Music* m_loseMusic;
    Mix_Chunk* m_moveChunk;
    Mix_Chunk* m_rotateChunk;
    Mix_Chunk* m_dropChunk;
    Mix_Chunk* m_eraseChunk;
    Mix_Chunk* m_eraseFourChunk;
    Mix_Chunk* m_upgradeChunk;

    Game m_game;

    int m_generateDelayFrameTarget;
    int m_generateDelayFrameCount;
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
    int m_preMoveDir;
    int m_curMoveDir;
    bool m_justMove;
    int m_accelerateLineCount;
    int m_eraseOrder;
    bool m_resultMusicStarted;

public:
    GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;

private:
    void constructGameTypeUI();
    void constructTetrisCountUI();
    void constructLineCountUI();
    void constructScoreUI();
    void constructNextTetrisUI();
    void constructLevelUI();

    void initGameTypeUI();
    void initTetrisCountUI();
    void initLineCountUI();
    void initScoreUI();
    void initLevelUI();

    void move();
    void rotate();
    void drop();
    void resultUpdate(bool win);

    void renderSingleSquare(SDL_Point pos, TetrisStyle style, bool isCount);
    void renderTetrisMode(SDL_Point centerPos, TetrisMode mode, bool isCount);
};