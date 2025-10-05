#include "scene/gamescene.h"
#include "conf/keyconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/common.h"
#include "util/render.h"

GameScene::GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    // 初始化游戏模式区域
    setupGameTypeRegion();

    // 初始化方块计数区域
    setupTetrisCountRegion();
    // 初始化消除行区域
    setupLineCountRegion();
    // 初始化分数区域
    setupScoreRegion();
    // 初始化下一个方块区域
    setupNextTetrisRegion();
    // 初始化等级区域
    setupLevelRegion();
    // 初始化高度区域
    setupHeightRegion();

    // 初始化游戏场地
    setupField();
    // 初始化方块相关纹理
    setupTetrisTexture();
    // 初始化结束区域
    setupResultRegion();
    // 初始化暂停文本
    setupPauseText();

    // 初始化方块相关数据
    setupTetrisData();

    // 初始化相关音频
    setupAudio();
}

void GameScene::onEnter() {
    Settings& s = m_ctx.settings;

    // 激活方块相关数据
    enableTetrisData();

    // 激活游戏模式区域
    enableGameTypeRegion();

    // 激活方块计数区域
    enableTetrisCountRegion();
    // 激活消除行区域
    enableLineCountRegion();
    // 激活分数区域
    enableScoreRegion();
    // 激活等级区域
    enableLevelRegion();
    // 如果是B模式，激活高度区域
    if (s.getGameType() == GAME_TYPE_B) {
        enableHeightRegion();
    }

    // 激活相关音频
    enableAudio();
}

void GameScene::onExit() {
    // 禁用相关音频
    disableAudio();
}

void GameScene::onUpdate() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    // 按键暂停/恢复
    if (im.isKeyJustPressed(PAUSE_KEY)) {
        m_paused = !m_paused;
    }

    // 如果暂停
    if (m_paused) {
        // 暂停音频
        am.pauseMusic();
        am.pauseChunk();
    } else {
        // 恢复音频
        am.resumeMusic();
        am.resumeChunk();

        switch (m_curStatus) {
            case Status::Generate: {
                // 生成方块
                generate();

                break;
            }
            case Status::Move: {
                // 方块移动
                move();
                // 方块旋转
                rotate();
                // 方块下落
                drop();

                break;
            }
            case Status::Check: {
                // 场地检测
                check();

                break;
            }
            case Status::Erase: {
                // 消除
                erase();

                break;
            }
            case Status::Calculate: {
                // 分数计算
                calculate();
                
                break;
            }
            case Status::Win:
            case Status::Lose: {
                // 更新结束区域
                resultUpdate(m_curStatus == Status::Win);

                break;
            }
            default: break;
        }
    }
}

void GameScene::renderContent() {
    if (m_paused) {
        // 渲染暂停文本
        renderPauseText();
    } else {
        // 渲染游戏模式区域
        renderGameTypeRegion();
        // 渲染所有游戏数据区域
        renderTetrisGameDataRegions();
        // 渲染游戏场地
        renderField();
        
        // 如果游戏流程状态为成功/失败，渲染结束区域
        if (m_curStatus == Status::Win || m_curStatus == Status::Lose) {
            renderResultRegion();
        }
    }
}

void GameScene::setupGameTypeRegion() {
    // 初始化场景框架纹理为nullptr，激活时再赋值
    m_gameFrameTexture = nullptr;

    // 初始化游戏模式标题
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::GAME_TYPE_TITLE_POS
    );
}

void GameScene::setupTetrisCountRegion() {
    // 初始化方块类型布局和方块计数布局
    m_tetrisPreviewLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_MODE_CENTER_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );
    m_tetrisCountLayout = std::make_unique<VerticalLayout>(
        GAME_SCENE::TETRIS_COUNT_POS,
        GAME_SCENE::TETRIS_COUNT_SPACING
    );

    // 初始化方块计数文本
    for (auto it = TETRIS_MODE_STYLE.begin(); it != TETRIS_MODE_STYLE.end(); ++it) {
        m_tetrisCountText.emplace(it->first, std::make_unique<Text>(
            m_ctx,
            "",
            m_tetrisCountLayout->getElementPos(static_cast<int>(it->first)),
            GAME_SCENE::TETRIS_COUNT_COLOR
        ));
    }
}

void GameScene::setupLineCountRegion() {
    // 初始化消除行文本
    m_lineCountText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::LINE_COUNT_POS
    );
}

void GameScene::setupScoreRegion() {
    // 初始化最高分标题和文本
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
    // 初始化分数标题和文本
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

void GameScene::setupNextTetrisRegion() {
    // 初始化下一个方块标题
    m_nextTetrisTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::NEXT_TETRIS_TITLE_STR,
        GAME_SCENE::NEXT_TETRIS_TITLE_POS
    );
}

void GameScene::setupLevelRegion() {
    // 初始化等级标题和文本
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

void GameScene::setupHeightRegion() {
    // 初始化高度标题和文本
    m_heightTitle = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::HEIGHT_TITLE_STR,
        GAME_SCENE::HEIGHT_TITLE_POS
    );
    m_heightText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::HEIGHT_TEXT_POS
    );
}

void GameScene::setupField() {
    m_tetrisFieldLayout = std::make_unique<GridLayout>(
        GAME_SCENE::TETRIS_FIELD_POS,
        -GAME_SCENE::TETRIS_SPACING,
        GAME_SCENE::TETRIS_SPACING
    );
}

void GameScene::setupTetrisTexture() {
    ResourceManager& rm = m_ctx.resourceManager;
    SDL_Renderer* rdr = m_ctx.renderer;

    // 初始化方块基底纹理
    m_tetrisBasicTexture = createSolidTexture(rdr, GAME_SCENE::TETRIS_BASIC_COLOR, GAME_SCENE::TETRIS_SIZE, GAME_SCENE::TETRIS_SIZE);
    m_tetrisPreviewBasicTexture = createSolidTexture(rdr, GAME_SCENE::TETRIS_BASIC_COLOR, GAME_SCENE::TETRIS_PREVIEW_SIZE, GAME_SCENE::TETRIS_PREVIEW_SIZE);
    // 初始化方块实心花纹纹理
    m_tetrisSolidPatternTexture = rm.getImage(TETRIS_SOLID_PATTERN_IMAGE_PATH);
    m_tetrisHollowPatternTexture = rm.getImage(TETRIS_HOLLOW_PATTERN_IMAGE_PATH);
    // 初始化方块空心花纹纹理
    m_tetrisPreviewSolidPatternTexture = rm.getImage(TETRIS_MODE_SOLID_PATTERN_IMAGE_PATH);
    m_tetrisPreviewHollowPatternTexture = rm.getImage(TETRIS_MODE_HOLLOW_PATTERN_IMAGE_PATH);
}

void GameScene::setupResultRegion() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 初始化结束框架纹理
    m_resultOuterFrameTexture = rm.getImage(RESULT_OUTER_FRAME_IMAGE_PATH);
    m_resultInnerFrameTexture = rm.getImage(RESULT_INNER_FRAME_IMAGE_PATH);

    // 初始化结束文本
    m_resultText = std::make_unique<Text>(
        m_ctx,
        "",
        GAME_SCENE::RESULT_TEXT_POS
    );
}

void GameScene::setupPauseText() {
    // 初始化暂停文本
    m_pauseText = std::make_unique<Text>(
        m_ctx,
        GAME_SCENE::PAUSE_TEXT_STR,
        GAME_SCENE::PAUSE_TEXT_POS,
        GAME_SCENE::PAUSE_TEXT_COLOR
    );
}

void GameScene::setupTetrisData() {
    // 初始化DAS/ARR/加速下落帧阈值/消除帧阈值
    m_dasFrameTarget = TETRIS_DAS_FRAME;
    m_arrFrameTarget = TETRIS_ARR_FRAME;
    m_accelerateFrameTarget = TETRIS_ACCELERATE_FRAME;
    m_eraseFrameTarget = TETRIS_ERASE_FRAME;
}

void GameScene::setupAudio() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 初始化相关音频
    m_music = nullptr;
    m_winMusic = rm.getMusic(WIN_MUSIC_PATH);
    m_loseMusic = rm.getMusic(LOSE_MUSIC_PATH);
    m_moveChunk = rm.getChunk(MOVE_CHUNK_PATH);
    m_rotateChunk = rm.getChunk(ROTATE_CHUNK_PATH);
    m_dropChunk = rm.getChunk(DROP_CHUNK_PATH);
    m_eraseChunk = rm.getChunk(ERASE_CHUNK_PATH);
    m_eraseFourChunk = rm.getChunk(ERASE_FOUR_CHUNK_PATH);
    m_upgradeChunk = rm.getChunk(UPGRADE_CHUNK_PATH);
}

void GameScene::enableGameTypeRegion() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    // 激活游戏模式框架
    std::string gameType = s.getGameType();
    if (gameType == GAME_TYPE_A) {
        m_gameFrameTexture = rm.getImage(GAME_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_gameFrameTexture = rm.getImage(GAME_B_FRAME_IMAGE_PATH);
    }
    
    // 游戏模式标题赋值
    m_gameTypeTitle->setStr(gameType);
}

void GameScene::enableTetrisCountRegion() {
    // 方块计数文本赋值
    for (auto it = m_tetrisCountText.begin(); it != m_tetrisCountText.end(); ++it) {
        it->second->setStr(std::string(GAME_SCENE::TETRIS_COUNT_MAX_LEN, '0'));
    }
}

void GameScene::enableLineCountRegion() {
    // 消除行文本赋值
    std::string lineCountStr = std::to_string(m_game->getLineCount());
    padLeft(lineCountStr, GAME_SCENE::LINE_COUNT_MAX_LEN, '0');
    m_lineCountText->setStr(GAME_SCENE::LINE_COUNT_STR + lineCountStr);
}

void GameScene::enableScoreRegion() {
    Settings& s = m_ctx.settings;

    // 最高分文本赋值
    std::string topScoreStr = std::to_string(s.getRecordInfo(0).score);
    padLeft(topScoreStr, RECORD_SCORE_MAX_LEN, '0');
    m_topScoreText->setStr(topScoreStr);

    // 分数文本赋值
    m_scoreText->setStr(std::string(RECORD_SCORE_MAX_LEN, '0'));
}

void GameScene::enableLevelRegion() {
    // 等级文本赋值
    std::string levelStr = std::to_string(m_game->getLevel());
    padLeft(levelStr, RECORD_LV_MAX_LEN, '0');
    m_levelText->setStr(levelStr);
}

void GameScene::enableHeightRegion() {
    // 高度文本赋值
    m_heightText->setStr(std::to_string(dynamic_cast<GameB*>(m_game.get())->getHeight()));
}

void GameScene::enableTetrisData() {
    Settings& s = m_ctx.settings;

    // 根据游戏模式重置游戏
    if (s.getGameType() == GAME_TYPE_A) {
        auto gameA = std::make_unique<GameA>();
        gameA->resetGame(s.getInitLevel());
        gameA->specificReset();
        m_game = std::move(gameA);
    }
    if (s.getGameType() == GAME_TYPE_B) {
        auto gameB = std::make_unique<GameB>();
        gameB->resetGame(s.getInitLevel());
        gameB->specificReset(s.getInitHeight());
        m_game = std::move(gameB);
    }

    // 帧计数器归0，生成延迟帧阈值归0（游戏过程中动态更新）
    m_generateDelayFrameTarget = 0;
    m_generateDelayFrameCount = 0;
    m_moveFrameCnt = 0;
    m_dropFrameCnt = 0;
    m_eraseFrameCnt = 0;

    // 重置其他参数
    m_curStatus = Status::Generate;     // 游戏流程状态重置为生成方块
    m_preMoveDir = 0;                   // 方块前一帧移动方向归0
    m_curMoveDir = 0;                   // 方块当前帧移动方向归0
    m_justMove = false;                 // 方块并非刚开始移动
    m_accelerateLineCount = 0;          // 方块不间断加速下落行数归0
    m_eraseOrder = 0;                   // 方块消除步骤数归0
    m_resultMusicStarted = false;       // 结束音乐未开始
}

void GameScene::enableAudio() {
    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    // 播放背景音乐
    m_music = rm.getMusic(s.getMusicPath());
    am.playMusic(m_music);
}

void GameScene::disableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 停止背景音乐
    am.stopMusic();
}

void GameScene::generate() {
    AudioManager& am = m_ctx.audioManager;

    // 如果方块生成延迟帧计数器达到阈值
    if (m_generateDelayFrameCount >= m_generateDelayFrameTarget) {
        // 方块生成
        bool generateSuccess = m_game->generate();

        // 当前方块类型计数文本更新
        TetrisMode curMode = m_game->getCurMode();
        std::string curModeCountStr = std::to_string(m_game->getTetrisCount(curMode));
        padLeft(curModeCountStr, GAME_SCENE::TETRIS_COUNT_MAX_LEN, '0');
        m_tetrisCountText[curMode]->setStr(curModeCountStr);
        
        // 如果生成成功，状态转移至移动状态，生成失败转移至失败状态
        m_curStatus = generateSuccess ? Status::Move : Status::Lose;
        // 如果生成失败，背景音乐停止
        if (!generateSuccess) {
            am.stopMusic();
        }

        // 方块生成延迟帧计数器归0
        m_generateDelayFrameCount = 0;
    } else {
        // 方块生成延迟帧计数器累加
        ++m_generateDelayFrameCount;
    }
}

void GameScene::move() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    // 根据按键情况获取当前帧移动方向
    if (im.isKeyPressed(LEFT_KEY)) {
        --m_curMoveDir;
    }
    if (im.isKeyPressed(RIGHT_KEY)) {
        ++m_curMoveDir;
    }
    // 如果当前帧移动方向不为0
    if (m_curMoveDir != 0) {
        // 如果改变方向，进行方向移动，并将m_justMove置为true
        if (m_curMoveDir != m_preMoveDir) {
            if (m_game->move(m_curMoveDir)) {
                am.playChunk(m_moveChunk);
            }
            m_justMove = true;
        } else {
            // 否则，说明是长按，第一次移动帧阈值为DAS，非第一次为ARR
            int moveFrameTarget = m_justMove ? m_dasFrameTarget : m_arrFrameTarget;
            // 如果方块移动帧计数器达到阈值
            if (m_moveFrameCnt >= moveFrameTarget) {
                // 方块移动
                if (m_game->move(m_curMoveDir)) {
                    am.playChunk(m_moveChunk);
                }
                // m_justMove置为false，表示之后长按不是第一次移动延迟
                m_justMove = false;
                // 方块移动帧计数器归0
                m_moveFrameCnt = 0;
            } else {
                // 方块移动帧计数器累加
                ++m_moveFrameCnt;
            }
        }
    } else {
        m_moveFrameCnt = 0;
    }
    // 更新帧移动方向
    m_preMoveDir = m_curMoveDir;
    m_curMoveDir = 0;
}

void GameScene::rotate() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    // 根据按键获取旋转偏移量
    int delta = 0;
    if (im.isKeyJustPressed(CW_ROTATE_KEY) && !im.isKeyPressed(CCW_ROTATE_KEY)) {
        delta = 1;
    } else if (im.isKeyJustPressed(CCW_ROTATE_KEY) && !im.isKeyPressed(CW_ROTATE_KEY)) {
        delta = -1;
    }
    
    // 如果偏移量不为0，进行方块旋转
    if (delta != 0 && m_game->rotate(delta)) {
        am.playChunk(m_rotateChunk);
    }
}

void GameScene::drop() {
    InputManager& im = m_ctx.inputManager;
    AudioManager& am = m_ctx.audioManager;

    // 获取等级对应重力
    m_dropFrameTarget = TETRIS_GRAVITY_FRAME[m_game->getLevel()];
    // 根据按键判断是否加速下落，并获取真实方块下落帧阈值
    bool isAccelerate = im.isKeyPressed(DOWN_KEY);
    int dropFrameTarget = isAccelerate ? m_accelerateFrameTarget : m_dropFrameTarget;
    // 如果方块下落帧计数器达到阈值
    if (m_dropFrameCnt >= dropFrameTarget) {
        // 如果下落失败，说明触底或碰撞
        if (!m_game->drop()) {
            // 获取方块最低行
            int lowestRow = m_game->getTetrisLowestRow();
            m_generateDelayFrameTarget = (lowestRow - 1) / 4 * 2 + 10;

            // 播放触底音效
            am.playChunk(m_dropChunk);
            m_curStatus = Status::Check;
        } else {
            // 如果是加速状态，加速下落行+1，否则归0
            m_accelerateLineCount = isAccelerate ? (m_accelerateLineCount + 1) : 0;
        }
        // 方块下落帧计数器归0
        m_dropFrameCnt = 0;
    } else {
        // 方块下落帧计数器累加
        ++m_dropFrameCnt;
    }
}

void GameScene::check() {
    AudioManager& am = m_ctx.audioManager;

    // 转移状态初始化为分数计算
    m_curStatus = Status::Calculate;
    // 获取本次消除行数
    int eraseLineCount = m_game->checkEraseLine();
    // 如果本次消除行数不为0
    if (eraseLineCount != 0) {
        // 转移状态修改为消除
        m_curStatus = Status::Erase;
        // 根据本次消除行数播放不同音效
        am.playChunk(eraseLineCount == TETRIS_NUM ? m_eraseFourChunk : m_eraseChunk);
    }
}

void GameScene::erase() {
    // 如果消除帧计数器达到阈值
    if (m_eraseFrameCnt >= m_eraseFrameTarget) {
        // 如果消除步骤结束，步骤归0，并将状态转移至分数计算
        if (m_game->eraseComplete(m_eraseOrder)) {
            m_eraseOrder = 0;
            m_curStatus = Status::Calculate;
        } else {
            // 否则，消除步骤累加
            ++m_eraseOrder;
        }
        // 消除帧计数器归0
        m_eraseFrameCnt = 0;
    } else {
        // 消除帧计数器累加
        ++m_eraseFrameCnt;
    }
}

void GameScene::calculate() {
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    // 计算本次分数
    m_game->calculate(m_accelerateLineCount);
    m_accelerateLineCount = 0;

    // 更新消除行数
    std::string lineCountStr = std::to_string(m_game->getLineCount());
    padLeft(lineCountStr, GAME_SCENE::LINE_COUNT_MAX_LEN, '0');
    m_lineCountText->setStr(GAME_SCENE::LINE_COUNT_STR + lineCountStr);

    // 更新分数
    std::string scoreStr = std::to_string(m_game->getScore());
    padLeft(scoreStr, RECORD_SCORE_MAX_LEN, '0');
    m_scoreText->setStr(scoreStr);

    // 更新等级
    int level = m_game->getLevel();
    std::string levelStr = std::to_string(level);
    padLeft(levelStr, RECORD_LV_MAX_LEN, '0');
    m_levelText->setStr(levelStr);

    // 如果是A模式，并成功升级，播放升级音效
    if (s.getGameType() == GAME_TYPE_A && dynamic_cast<GameA*>(m_game.get())->isUpgrade()) {
        am.playChunk(m_upgradeChunk);
    }

    // 如果满足胜利条件，状态转移至胜利，否则转移至方块生成
    // 胜利条件：A模式 - 等级达到30级；B模式 - 消除行数归0
    m_curStatus = Status::Generate;
    std::string gameType = s.getGameType();
    if ((gameType == GAME_TYPE_A && level >= TETRIS_GRAVITY_FRAME.size()) || (gameType == GAME_TYPE_B && m_game->getLineCount() <= 0)) {
        m_curStatus = Status::Win;
    } 
}

void GameScene::resultUpdate(bool win) {
    AudioManager& am = m_ctx.audioManager;
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    // 如果结束音乐没有开始
    if (!m_resultMusicStarted) {
        // 计算新纪录信息，并尝试插入排行榜
        int score = m_game->getScore();
        int level = m_game->getLevel();
        if (s.getGameType() == GAME_TYPE_B && win) {
            // 如果是B模式且获胜，分数需额外增加1000 * (等级 + 高度)
            int height = dynamic_cast<GameB*>(m_game.get())->getHeight();
            score += 1000 * (level + height);
        }
        s.insertRecord(score, level);

        // 根据等级获取深色与浅色
        SDL_Color darkColor = GAME_SCENE::TETRIS_PATTERN_DARK_COLOR[m_game->getLevel() % GAME_SCENE::TETRIS_PATTERN_DARK_COLOR.size()];
        SDL_Color lightColor = GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR[m_game->getLevel() % GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR.size()];
        // 结束框架与文本染色
        SDL_SetTextureColorMod(m_resultOuterFrameTexture, lightColor.r, lightColor.g, lightColor.b);
        m_resultText->setColor(darkColor);

        // 根据是否胜利设置结束文本和音乐
        m_resultText->setStr(win ? GAME_SCENE::WIN_TEXT_STR : GAME_SCENE::LOSE_TEXT_STR);
        Mix_Music* music = win ? m_winMusic : m_loseMusic;

        // 播放音乐，并将m_resultMusicStarted设置为true
        am.playMusic(music, 0);
        m_resultMusicStarted = true;
    } else {
        // 如果结束音乐已开始，但目前没有播放音乐，说明音乐播放完了，检测按键切换场景
        if (!am.isPlayingMusic()) {
            if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
                m_loadSceneCallback(s.getNewRecordOrder() == RECORD_COUNT ? SETTING_SCENE::NAME : COUNT_SCENE::NAME);
            }
        }
    }
}

void GameScene::renderPauseText() {
    // 渲染暂停文本
    m_pauseText->onRender();
}

void GameScene::renderGameTypeRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染游戏模式框架和标题
    renderTexture(rdr, m_gameFrameTexture);
    m_gameTypeTitle->onRender();
}

void GameScene::renderTetrisGameDataRegions() {
    Settings& s = m_ctx.settings;

    // 渲染方块计数区域
    for (auto it = m_tetrisCountText.begin(); it != m_tetrisCountText.end(); ++it) {
        renderTetrisMode(m_tetrisPreviewLayout->getElementPos(static_cast<int>(it->first)), it->first, true);
        it->second->onRender();
    }

    // 渲染消除行区域
    m_lineCountText->onRender();

    // 渲染分数区域
    m_topScoreTitle->onRender();
    m_topScoreText->onRender();
    m_scoreTitle->onRender();
    m_scoreText->onRender();

    // 渲染下一个方块区域
    m_nextTetrisTitle->onRender();
    renderTetrisMode(GAME_SCENE::NEXT_TETRIS_CENTER_POS, m_game->getNextMode(), false);

    // 渲染等级区域
    m_levelTitle->onRender();
    m_levelText->onRender();
    // 如果是B模式，渲染高度区域
    if (s.getGameType() == GAME_TYPE_B) {
        m_heightTitle->onRender();
        m_heightText->onRender();
    }
}

void GameScene::renderField() {
    // 渲染游戏场地
    for (int i = 0; i < TETRIS_FIELD_HEIGHT; ++i) {
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            if (m_game->getFieldStyle(i, j) != TetrisStyle::Blank) {
                renderSingleSquare(m_tetrisFieldLayout->getElementPos(i, j), m_game->getFieldStyle(i, j), false);
            }
        }
    }
}

void GameScene::renderResultRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染结束框架和文本
    renderTexture(rdr, m_resultOuterFrameTexture, GAME_SCENE::RESULT_OUTER_FRAME_POS);
    renderTexture(rdr, m_resultInnerFrameTexture, GAME_SCENE::RESULT_INNER_FRAME_POS);
    m_resultText->onRender();
}

void GameScene::renderSingleSquare(SDL_Point pos, TetrisStyle style, bool isPreview) {
    SDL_Renderer* rdr = m_ctx.renderer;
    
    // 获取基底纹理和花纹纹理
    SDL_Texture* basicTexture = isPreview ? m_tetrisPreviewBasicTexture.get() : m_tetrisBasicTexture.get();
    SDL_Texture* solidPatternTexture = isPreview ? m_tetrisPreviewSolidPatternTexture : m_tetrisSolidPatternTexture;
    SDL_Texture* hollowPatternTexture = isPreview ? m_tetrisPreviewHollowPatternTexture : m_tetrisHollowPatternTexture;

    // 渲染基底纹理
    renderTexture(rdr, basicTexture, pos);

    // 根据关卡获取深色和浅色
    SDL_Color darkColor = GAME_SCENE::TETRIS_PATTERN_DARK_COLOR[m_game->getLevel() % GAME_SCENE::TETRIS_PATTERN_DARK_COLOR.size()];
    SDL_Color lightColor = GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR[m_game->getLevel() % GAME_SCENE::TETRIS_PATTERN_LIGHT_COLOR.size()];
    // 根据方块样式对对应花纹染色，并渲染
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

void GameScene::renderTetrisMode(SDL_Point centerPos, TetrisMode mode, bool isPreview) {
    // 根据是否为计数区域预览方块获取方块尺寸和间隔
    int size = isPreview ? GAME_SCENE::TETRIS_PREVIEW_SIZE : GAME_SCENE::TETRIS_SIZE;
    int spacing = isPreview ? GAME_SCENE::TETRIS_PREVIEW_SPACING : GAME_SCENE::TETRIS_SPACING;
    // 根据方块种类和中心点位置获取锚点位置
    SDL_Point anchorPos;
    switch (mode) {
        case TetrisMode::I: anchorPos = { centerPos.x - (spacing + size) / 2, centerPos.y - size / 2 }; break;
        case TetrisMode::O: anchorPos = { centerPos.x - (spacing + size) / 2, centerPos.y - (spacing + size) / 2 }; break;
        default: anchorPos = { centerPos.x - spacing - size / 2, centerPos.y - (spacing + size) / 2 }; break;
    }

    // 逐个方块渲染
    auto& modeInitShape = (TETRIS_MODE_ROTATE.at(mode))[0];
    for (auto& shape: modeInitShape) {
        SDL_Point shapePos = { 
            anchorPos.x + shape.second * spacing, 
            anchorPos.y - shape.first * spacing
        };
        renderSingleSquare(shapePos, TETRIS_MODE_STYLE.at(mode), isPreview);
    }
}