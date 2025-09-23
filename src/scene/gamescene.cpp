#include "scene/gamescene.h"
#include "conf/sceneconf.h"
#include "util/util.h"

GameScene::GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) 
    , m_dasFrameTarget(TETRIS_DAS_FRAME)
    , m_arrFrameTarget(TETRIS_ARR_FRAME)
    , m_moveFrameCnt(0)
    , m_accelerateFrameTarget(TETRIS_ACCELERATE_FRAME)
    , m_dropFrameCnt(0)
    , m_eraseFrameTarget(TETRIS_ERASE_FRAME)
    , m_eraseFrameCnt(0)
    , m_nextFrameTarget(0)
    , m_nextFrameCnt(0) {
    ResourceManager& rm = ctx.resourceManager;

    m_gameFrameTexture = rm.getImage(GAME_FRAME_IMAGE_PATH);

    m_tetrisTemplateLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_TEMPLATE_CENTER_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );
    m_tetrisCountLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_COUNT_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );

    m_gameTypeTitle = std::make_unique<Text>(
        ctx,
        "",
        GAME_SCENE::GAME_TYPE_TITLE_POS
    );
    auto& count = m_game.getCount();
    for (auto it = count.begin(); it != count.end(); ++it) {
        m_tetrisCount.emplace(it->first, std::make_unique<Text>(
            ctx,
            "",
            m_tetrisCountLayout->getElementPos(static_cast<int>(it->first))
        ));
    }
    m_lineCount = std::make_unique<Text>(
        ctx,
        "",
        GAME_SCENE::LINE_COUNT_POS
    );
    m_topScoreTitle = std::make_unique<Text>(
        ctx,
        GAME_SCENE::TOP_TITLE_STR,
        GAME_SCENE::TOP_POS
    );
    m_topScore = std::make_unique<Text>(
        ctx,
        "",
        SDL_Point { GAME_SCENE::TOP_POS.x, GAME_SCENE::TOP_POS.y + GAME_SCENE::SCORE_SPACING }
    );
    m_scoreTitle = std::make_unique<Text>(
        ctx,
        GAME_SCENE::SCORE_TITLE_STR,
        GAME_SCENE::SCORE_POS
    );
    m_score = std::make_unique<Text>(
        ctx,
        "",
        SDL_Point { GAME_SCENE::SCORE_POS.x, GAME_SCENE::SCORE_POS.y + GAME_SCENE::SCORE_SPACING }
    );
    m_nextTetrisTitle = std::make_unique<Text>(
        ctx,
        GAME_SCENE::NEXT_TETRIS_TITLE_STR,
        GAME_SCENE::NEXT_TETRIS_TITLE_POS
    );
    m_levelTitle = std::make_unique<Text>(
        ctx,
        GAME_SCENE::LEVEL_TITLE_STR,
        GAME_SCENE::LEVEL_POS
    );
    m_level = std::make_unique<Text>(
        ctx,
        "",
        SDL_Point { GAME_SCENE::LEVEL_POS.x, GAME_SCENE::LEVEL_POS.y + GAME_SCENE::LEVEL_SPACING }
    );
}

void GameScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    m_gameTypeTitle->setStr(s.getGameType());
    m_game.resetGame(s.getLevel(), s.getHeight());

    m_music = rm.getMusic(s.getMusicPath());
    am.playMusic(m_music);
}

void GameScene::onExit() {
    AudioManager& am = m_ctx.audioManager;

    am.stopMusic();
}

void GameScene::onUpdate() {
    
}

void GameScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;

    renderTexture(rdr, m_gameFrameTexture);

    m_gameTypeTitle->onRender();
    m_lineCount->onRender();
    m_topScoreTitle->onRender();
    m_topScore->onRender();
    m_scoreTitle->onRender();
    m_score->onRender();
    m_nextTetrisTitle->onRender();
    m_levelTitle->onRender();
    m_level->onRender();
}