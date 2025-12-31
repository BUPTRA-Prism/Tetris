#include "scene/gamescene.h"
#include "conf/keyconf.h"
#include "conf/settingconf.h"
#include "conf/resourceconf.h"
#include "conf/uiconf.h"
#include "util/render.h"

GameScene::GameScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, core, loadSceneCallback)
    , m_gameFrame(nullptr)
    , m_scoreboard(nullptr) {
    m_scoreText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::SCORE_TEXT_STR, 
        SCOREBOARD::SCORE_TEXT_POS
    );
    m_lineText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::LINE_TEXT_STR, 
        SCOREBOARD::LINE_TEXT_POS
    );
    m_levelText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::LEVEL_TEXT_STR, 
        SDL_Point { 0, 0 }
    );

    m_nextText1 = std::make_unique<Text>(
        ctx, 
        GAME_SCENE::NEXT_TEXT_STR, 
        GAME_SCENE::NEXT_TEXT_1_POS,
        GAME_SCENE::NEXT_TEXT_COLOR
    );
    m_nextText2 = std::make_unique<Text>(
        ctx, 
        GAME_SCENE::NEXT_TEXT_STR, 
        GAME_SCENE::NEXT_TEXT_2_POS,
        GAME_SCENE::NEXT_TEXT_COLOR
    );
}

void GameScene::onEnter() {
    AudioManager& am = m_ctx.audioManager;
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_core.settings;

    std::string modeOption = MODE_OPTIONS[s.getModeIdx()];
    if (modeOption == SINGLE_PLAYER_MODE) {
        m_gameFrame = rm.getImage(VERSUS_GAME_FRAME_PATH);
        m_scoreboard = rm.getImage(SINGLE_BOARD_PATH);
        m_levelText->setPos(GAME_SCENE::VERSUS_LEVEL_TEXT_POS);
    } else if (modeOption == DOUBLE_PLAYER_MODE || modeOption == VERSUS_COMPUTER_MODE) {
        m_gameFrame = rm.getImage(VERSUS_GAME_FRAME_PATH);
        m_scoreboard = rm.getImage(VERSUS_BOARD_PATH);
        m_levelText->setPos(GAME_SCENE::VERSUS_LEVEL_TEXT_POS);
    } else {
        m_gameFrame = rm.getImage(COOP_GAME_FRAME_PATH);
        m_scoreboard = rm.getImage(COOP_BOARD_PATH);
        m_levelText->setPos(GAME_SCENE::COOP_LEVEL_TEXT_POS);
    }

    std::string musicOption = MUSIC_OPTIONS[s.getMusicIdx()];
    if (musicOption != SILENCE) {
        for (auto& c: musicOption) {
            c = std::tolower(c);
        }
    }
    am.playMusic(rm.getMusic(musicOption + ".ogg"));
}

void GameScene::onExit() {
   
}

void GameScene::onUpdate() {
    
}

void GameScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_core.settings;

    if (m_gameFrame) {
        renderTexture(rdr, m_gameFrame);
    }
    if (m_scoreboard) {
        renderTexture(rdr, m_scoreboard, SCOREBOARD::POS);
    }

    m_scoreText->onRender();
    m_lineText->onRender();
    m_levelText->onRender();

    m_nextText1->onRender();
    if (MODE_OPTIONS[s.getModeIdx()] != SINGLE_PLAYER_MODE) {
        m_nextText2->onRender();
    }

}