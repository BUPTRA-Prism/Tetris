#include "scene/gamescene.h"
#include "conf/keyconf.h"
#include "conf/sceneconf.h"
#include "util/common.h"
#include "util/render.h"

GameScene::GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) 
    , m_dasFrameTarget(TETRIS_DAS_FRAME)
    , m_arrFrameTarget(TETRIS_ARR_FRAME)
    , m_accelerateFrameTarget(TETRIS_ACCELERATE_FRAME)
    , m_eraseFrameTarget(TETRIS_ERASE_FRAME) {
    constructGameTypeUI();
    constructTetrisCountUI();
    constructLineCountUI();
    constructScoreUI();
    constructNextTetrisUI();
    constructLevelUI();

    ResourceManager& rm = m_ctx.resourceManager;
    SDL_Renderer* rdr = m_ctx.renderer;
    m_tetrisFieldLayout = std::make_unique<GridLayout>(
        GAME_SCENE::TETRIS_FIELD_POS,
        -GAME_SCENE::TETRIS_SPACING,
        GAME_SCENE::TETRIS_SPACING
    );

    m_resultText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::RESULT_TEXT_POS
    );

    m_tetrisBasicTexture = createSolidTexture(rdr, GAME_SCENE::TETRIS_BASIC_COLOR, GAME_SCENE::TETRIS_SIZE, GAME_SCENE::TETRIS_SIZE);
    m_tetrisModeBasicTexture = createSolidTexture(rdr, GAME_SCENE::TETRIS_BASIC_COLOR, GAME_SCENE::TETRIS_MODE_SIZE, GAME_SCENE::TETRIS_MODE_SIZE);
    m_tetrisSolidPatternTexture = rm.getImage(TETRIS_SOLID_PATTERN_IMAGE_PATH);
    m_tetrisHollowPatternTexture = rm.getImage(TETRIS_HOLLOW_PATTERN_IMAGE_PATH);
    m_tetrisModeSolidPatternTexture = rm.getImage(TETRIS_MODE_SOLID_PATTERN_IMAGE_PATH);
    m_tetrisModeHollowPatternTexture = rm.getImage(TETRIS_MODE_HOLLOW_PATTERN_IMAGE_PATH);
    m_resultOuterFrameTexture = rm.getImage(RESULT_OUTER_FRAME_IMAGE_PATH);
    m_resultInnerFrameTexture = rm.getImage(RESULT_INNER_FRAME_IMAGE_PATH);

    m_winMusic = rm.getMusic(WIN_MUSIC_PATH);
    m_loseMusic = rm.getMusic(LOSE_MUSIC_PATH);
    m_moveChunk = rm.getChunk(MOVE_CHUNK_PATH);
    m_rotateChunk = rm.getChunk(ROTATE_CHUNK_PATH);
    m_dropChunk = rm.getChunk(DROP_CHUNK_PATH);
    m_eraseChunk = rm.getChunk(ERASE_CHUNK_PATH);
    m_eraseFourChunk = rm.getChunk(ERASE_FOUR_CHUNK_PATH);
    m_upgradeChunk = rm.getChunk(UPGRADE_CHUNK_PATH);
}

void GameScene::constructGameTypeUI() {
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::GAME_TYPE_TITLE_POS
    );
}

void GameScene::constructTetrisCountUI() {
    m_tetrisModeLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_MODE_CENTER_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );
    m_tetrisCountLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_COUNT_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );

    for (auto it = TETRIS_MODE_STYLE.begin(); it != TETRIS_MODE_STYLE.end(); ++it) {
        m_tetrisCountText.emplace(it->first, std::make_unique<Text>(
            m_ctx,
            "",
            m_tetrisCountLayout->getElementPos(static_cast<int>(it->first)),
            GAME_SCENE::TETRIS_COUNT_COLOR
        ));
    }
}

void GameScene::constructLineCountUI() {
    m_lineCountText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::LINE_COUNT_POS
    );
}

void GameScene::constructScoreUI() {
    m_topScoreTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::TOP_TITLE_STR,
        GAME_SCENE::TOP_POS
    );
    m_topScoreText = std::make_unique<Text>(
        m_ctx,
        "",
        SDL_Point { GAME_SCENE::TOP_POS.x, GAME_SCENE::TOP_POS.y + GAME_SCENE::SCORE_SPACING }
    );
    m_scoreTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::SCORE_TITLE_STR,
        GAME_SCENE::SCORE_POS
    );
    m_scoreText = std::make_unique<Text>(
        m_ctx,
        "",
        SDL_Point { GAME_SCENE::SCORE_POS.x, GAME_SCENE::SCORE_POS.y + GAME_SCENE::SCORE_SPACING }
    );
}

void GameScene::constructNextTetrisUI() {
    m_nextTetrisTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::NEXT_TETRIS_TITLE_STR,
        GAME_SCENE::NEXT_TETRIS_TITLE_POS
    );
}

void GameScene::constructLevelUI() {
    m_levelTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::LEVEL_TITLE_STR,
        GAME_SCENE::LEVEL_TITLE_POS
    );
    m_levelText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::LEVEL_TEXT_POS
    );
}

void GameScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    m_game.resetGame(s.getLevel(), s.getHeight(), s.getGameType() == GAME_TYPE_B);
    m_generateDelayFrameTarget = 0;
    m_generateDelayFrameCount = 0;
    m_moveFrameCnt = 0;
    m_dropFrameCnt = 0;
    m_eraseFrameCnt = 0;
    m_nextFrameCnt = 0;
    m_curStatus = Status::Generate;
    m_preMoveDir = 0;
    m_curMoveDir = 0;
    m_justMove = false;
    m_accelerateLineCount = 0;
    m_eraseOrder = 0;
    m_resultMusicStarted = false;

    m_music = rm.getMusic(s.getMusicPath());
    am.playMusic(m_music);

    initGameTypeUI();
    initTetrisCountUI();
    initLineCountUI();
    initScoreUI();
    initLevelUI();
}

void GameScene::initGameTypeUI() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    std::string gameType = s.getGameType();
    if (gameType == GAME_TYPE_A) {
        m_gameFrameTexture = rm.getImage(GAME_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_gameFrameTexture = rm.getImage(GAME_B_FRAME_IMAGE_PATH);
    }
    
    m_gameTypeTitle->setStr(gameType);
}

void GameScene::initTetrisCountUI() {
    for (auto it = m_tetrisCountText.begin(); it != m_tetrisCountText.end(); ++it) {
        it->second->setStr(std::string(GAME_SCENE::TETRIS_COUNT_MAX_LEN, '0'));
    }
}

void GameScene::initLineCountUI() {
    m_lineCountText->setStr(GAME_SCENE::LINE_COUNT_STR + std::string(GAME_SCENE::LINE_COUNT_MAX_LEN, '0'));
}

void GameScene::initScoreUI() {
    Settings& s = m_ctx.settings;
    std::string topScoreStr = std::to_string(s.getRecordScore(0));
    padLeft(topScoreStr, GAME_SCENE::SCORE_MAX_LEN, '0');
    m_topScoreText->setStr(topScoreStr);

    m_scoreText->setStr(std::string(GAME_SCENE::SCORE_MAX_LEN, '0'));
}

void GameScene::initLevelUI() {
    m_levelText->setStr(std::string(GAME_SCENE::LEVEL_MAX_LEN, '0'));
}

void GameScene::onExit() {
    AudioManager& am = m_ctx.audioManager;

    am.stopMusic();
}

void GameScene::onUpdate() {
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    switch (m_curStatus) {
        case Status::Generate: {
            if (m_generateDelayFrameCount >= m_generateDelayFrameTarget) {
                bool generateSuccess = m_game.generate();

                TetrisMode curMode = m_game.getCurMode();
                std::string curModeCountStrStr = std::to_string(m_game.getTetrisCount(curMode));
                padLeft(curModeCountStrStr, GAME_SCENE::TETRIS_COUNT_MAX_LEN, '0');
                m_tetrisCountText[curMode]->setStr(curModeCountStrStr);
                
                m_curStatus = generateSuccess ? Status::Move : Status::Lose;
                if (!generateSuccess) {
                    am.stopMusic();
                }

                m_generateDelayFrameCount = 0;
            } else {
                ++m_generateDelayFrameCount;
            }
            
            break;
        }
        case Status::Move: {
            move();
            rotate();
            drop();
            break;
        }
        case Status::Check: {
            m_curStatus = Status::Calculate;
            int eraseLineCount = m_game.checkEraseLine();
            if (eraseLineCount != 0) {
                m_curStatus = Status::Erase;
                am.playChunk(eraseLineCount == 4 ? m_eraseFourChunk : m_eraseChunk);
            }
            break;
        }
        case Status::Erase: {
            ++m_eraseFrameCnt;
            if (m_eraseFrameCnt >= m_eraseFrameTarget) {
                if (m_game.eraseComplete(m_eraseOrder)) {
                    m_eraseOrder = 0;
                    m_curStatus = Status::Calculate;
                } else {
                    ++m_eraseOrder;
                }
                m_eraseFrameCnt = 0;
            }
            break;
        }
        case Status::Calculate: {
            m_game.calculate(m_accelerateLineCount);

            std::string lineCountStr = std::to_string(m_game.getLineCount());
            padLeft(lineCountStr, GAME_SCENE::LINE_COUNT_MAX_LEN, '0');
            m_lineCountText->setStr(GAME_SCENE::LINE_COUNT_STR + lineCountStr);

            std::string scoreStr = std::to_string(m_game.getScore());
            padLeft(scoreStr, GAME_SCENE::SCORE_MAX_LEN, '0');
            m_scoreText->setStr(scoreStr);

            int level = m_game.getLevel();
            std::string levelStr = std::to_string(level);
            padLeft(levelStr, GAME_SCENE::LEVEL_MAX_LEN, '0');
            m_levelText->setStr(levelStr);

            if (m_game.isUpgrade()) {
                am.playChunk(m_upgradeChunk);
            }

            m_curStatus = Status::Generate;
            std::string gameType = s.getGameType();
            if ((gameType == GAME_TYPE_A && level >= TETRIS_GRAVITY_FRAME.size()) || (gameType == GAME_TYPE_B && m_game.getLineCount() <= 0)) {
                m_curStatus = Status::Win;
            } 
            
            break;
        }
        case Status::Win: {
            resultUpdate(true);
            break;
        }
        case Status::Lose: {
            resultUpdate(false);
            break;
        }
        default: break;
    }
}

void GameScene::move() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    if (im.isKeyPressed(LEFT_KEY)) {
        --m_curMoveDir;
    }
    if (im.isKeyPressed(RIGHT_KEY)) {
        ++m_curMoveDir;
    }
    if (m_curMoveDir != 0) {
        if (m_curMoveDir != m_preMoveDir) {
            if (m_game.move(m_curMoveDir)) {
                am.playChunk(m_moveChunk);
            }
            m_justMove = true;
        } else {
            ++m_moveFrameCnt;
            int moveFrameTarget = m_justMove ? m_dasFrameTarget : m_arrFrameTarget;
            if (m_moveFrameCnt >= moveFrameTarget) {
                if (m_game.move(m_curMoveDir)) {
                    am.playChunk(m_moveChunk);
                }
                m_justMove = false;
                m_moveFrameCnt = 0;
            }
        }
    } else {
        m_moveFrameCnt = 0;
    }
    m_preMoveDir = m_curMoveDir;
    m_curMoveDir = 0;
}

void GameScene::rotate() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    int delta = 0;
    if (im.isKeyJustPressed(CW_ROTATE_KEY)) {
        delta = 1;
    } else if (im.isKeyJustPressed(CCW_ROTATE_KEY)) {
        delta = -1;
    }
    
    if (delta != 0 && m_game.rotate(delta)) {
        am.playChunk(m_rotateChunk);
    }
}

void GameScene::drop() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    ++m_dropFrameCnt;
    m_dropFrameTarget = TETRIS_GRAVITY_FRAME[m_game.getLevel()];
    bool isAccelerate = im.isKeyPressed(DOWN_KEY);
    int dropFrameTarget = isAccelerate ? m_accelerateFrameTarget : m_dropFrameTarget;
    if (m_dropFrameCnt >= dropFrameTarget) {
        if (!m_game.drop()) {
            int lowestRow = m_game.getTetrisLowestRow();
            m_generateDelayFrameTarget = (lowestRow - 1) / 4 * 2 + 10;

            am.playChunk(m_dropChunk);
            m_curStatus = Status::Check;
        } else {
            m_accelerateLineCount = isAccelerate ? (m_accelerateLineCount + 1) : 0;
        }
        m_dropFrameCnt = 0;
    }
}

void GameScene::resultUpdate(bool win) {
    AudioManager& am = m_ctx.audioManager;
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    if (!m_resultMusicStarted) {
        int score = m_game.getScore();
        int level = m_game.getLevel();
        int height = m_game.getHeight();
        if (s.getGameType() == GAME_TYPE_B && win) {
            score += 1000 * (level + height);
        }
        s.insertRecord(score, level);

        SDL_Color darkColor = GAME_SCENE::TETRIS_PATTERN_DARK_COLOR[m_game.getLevel() % GAME_SCENE::TETRIS_PATTERN_DARK_COLOR.size()];
        SDL_Color lightColor = GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR[m_game.getLevel() % GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR.size()];
        SDL_SetTextureColorMod(m_resultOuterFrameTexture, lightColor.r, lightColor.g, lightColor.b);
        m_resultText->setStr(win ? GAME_SCENE::WIN_TEXT_STR : GAME_SCENE::LOSE_TEXT_STR);
        m_resultText->setColor(darkColor);
        Mix_Music* music = win ? m_winMusic : m_loseMusic;

        am.playMusic(music, 0);
        m_resultMusicStarted = true;
    } else {
        if (!am.isPlayingMusic()) {
            if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
                m_loadSceneCallback(s.getNewRecordOrder() == RECORD_COUNT ? SETTING_SCENE::NAME : COUNT_SCENE::NAME);
            }
        }
    }
}

void GameScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;

    renderTexture(rdr, m_gameFrameTexture);

    m_gameTypeTitle->onRender();
    for (auto it = m_tetrisCountText.begin(); it != m_tetrisCountText.end(); ++it) {
        it->second->onRender();
    }
    m_lineCountText->onRender();
    m_topScoreTitle->onRender();
    m_topScoreText->onRender();
    m_scoreTitle->onRender();
    m_scoreText->onRender();
    m_nextTetrisTitle->onRender();
    m_levelTitle->onRender();
    m_levelText->onRender();

    for (auto it = TETRIS_MODE_STYLE.begin(); it != TETRIS_MODE_STYLE.end(); ++it) {
        TetrisMode mode = it->first;
        renderTetrisMode(m_tetrisModeLayout->getElementPos(static_cast<int>(mode)), mode, true);
    }

    renderTetrisMode(GAME_SCENE::NEXT_TETRIS_CENTER_POS, m_game.getNextMode(), false);

    for (int i = 0; i < TETRIS_FIELD_HEIGHT; ++i) {
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            if (m_game.getFieldStyle(i, j) != TetrisStyle::Blank) {
                renderSingleSquare(m_tetrisFieldLayout->getElementPos(i, j), m_game.getFieldStyle(i, j), false);
            }
        }
    }

    if (m_curStatus == Status::Win || m_curStatus == Status::Lose) {
        renderTexture(rdr, m_resultOuterFrameTexture, GAME_SCENE::RESULT_OUTER_FRAME_POS);
        renderTexture(rdr, m_resultInnerFrameTexture, GAME_SCENE::RESULT_INNER_FRAME_POS);
        m_resultText->onRender();
    }
}

void GameScene::renderSingleSquare(SDL_Point pos, TetrisStyle style, bool isCount) {
    SDL_Renderer* rdr = m_ctx.renderer;
    
    SDL_Texture* basicTexture = isCount ? m_tetrisModeBasicTexture.get() : m_tetrisBasicTexture.get();
    SDL_Texture* solidPatternTexture = isCount ? m_tetrisModeSolidPatternTexture : m_tetrisSolidPatternTexture;
    SDL_Texture* hollowPatternTexture = isCount ? m_tetrisModeHollowPatternTexture : m_tetrisHollowPatternTexture;

    renderTexture(rdr, basicTexture, pos);

    SDL_Color darkColor = GAME_SCENE::TETRIS_PATTERN_DARK_COLOR[m_game.getLevel() % GAME_SCENE::TETRIS_PATTERN_DARK_COLOR.size()];
    SDL_Color lightColor = GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR[m_game.getLevel() % GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR.size()];
    switch (style) {
        case TetrisStyle::SolidDark: {
            SDL_SetTextureColorMod(solidPatternTexture, darkColor.r, darkColor.g, darkColor.b);
            renderTexture(rdr, solidPatternTexture, pos);
            break;
        }
        case TetrisStyle::SolidLight: {
            SDL_SetTextureColorMod(solidPatternTexture, lightColor.r, lightColor.g, lightColor.b);
            renderTexture(rdr, solidPatternTexture, pos);
            break;
        }
        case TetrisStyle::HollowDark: {
            SDL_SetTextureColorMod(hollowPatternTexture, darkColor.r, darkColor.g, darkColor.b);
            renderTexture(rdr, hollowPatternTexture, pos);
            break;
        }
        default: break;
    }
}

void GameScene::renderTetrisMode(SDL_Point centerPos, TetrisMode mode, bool isCount) {
    int size = isCount ? GAME_SCENE::TETRIS_MODE_SIZE : GAME_SCENE::TETRIS_SIZE;
    int spacing = isCount ? GAME_SCENE::TETRIS_MODE_SPACING : GAME_SCENE::TETRIS_SPACING;
    SDL_Point anchorPos;
    switch (mode) {
        case TetrisMode::I: anchorPos = { centerPos.x - (spacing + size) / 2, centerPos.y - size / 2 }; break;
        case TetrisMode::O: anchorPos = { centerPos.x - (spacing + size) / 2, centerPos.y - (spacing + size) / 2 }; break;
        default: anchorPos = { centerPos.x - spacing - size / 2, centerPos.y - (spacing + size) / 2 }; break;
    }

    auto& modeInitShape = (TETRIS_MODE_ROTATE.at(mode))[0];
    for (auto& shape: modeInitShape) {
        SDL_Point shapePos = { 
            anchorPos.x + shape.second * spacing, 
            anchorPos.y - shape.first * spacing
        };
        renderSingleSquare(shapePos, TETRIS_MODE_STYLE.at(mode), isCount);
    }
}