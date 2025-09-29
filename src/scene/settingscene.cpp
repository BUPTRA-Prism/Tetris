#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/common.h"
#include "util/render.h"

SettingScene::SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_typeFrameTexture(nullptr)
    , m_levelFrameTexture(nullptr) {
    ResourceManager& rm = ctx.resourceManager;
    SDL_Renderer* rdr = ctx.renderer;

    // 载入设置框架
    m_settingFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
    
    // 创建选项图标（纯色块）
    m_optionIconTexture = createSolidTexture(
        rdr, 
        SETTING_SCENE::OPTION_ICON_COLOR, 
        SETTING_SCENE::OPTION_ICON_SIZE.x, 
        SETTING_SCENE::OPTION_ICON_SIZE.y
    );

    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);     // 载入切换选项音效
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);       // 载入切换场景音效

    // 构造各区域组件
    constructGameTypeUI();
    constructLevelOptionUI();
    constructHeightOptionUI();
    constructRecordUI();
}

void SettingScene::constructGameTypeUI() {
    // 创建游戏类型标题文本
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TITLE_POS
    );
}

void SettingScene::constructLevelOptionUI() {
    int levelOptionCol = (MAX_LEVEL + 1) / SETTING_SCENE::OPTION_ROW_NUM;

    // 创建关卡选项标题文本
    m_levelTitle = std::make_unique<Text>(
        m_ctx,
        SETTING_SCENE::LEVEL_TITLE_STR,
        SETTING_SCENE::LEVEL_TITLE_POS
    );

    // 创建关卡选项图标布局
    m_levelOptionIconLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::LEVEL_OPTION_ICON_POS,
        SETTING_SCENE::OPTION_ICON_SPACING,
        SETTING_SCENE::OPTION_ICON_SPACING
    );

    // 创建关卡选项文本
    m_levelOptionText.reserve(MAX_LEVEL + 1);
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        SDL_Point pos = m_levelOptionIconLayout->getElementPos(i / levelOptionCol, i % levelOptionCol);
        m_levelOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i),
                SDL_Point{ pos.x + SETTING_SCENE::OPTION_MARGIN, pos.y + SETTING_SCENE::OPTION_MARGIN },
                SETTING_SCENE::OPTION_COLOR
            )
        );
    }

    // 创建关卡选项图标
    m_levelOptionIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_optionIconTexture.get(), 
        [layoutPtr = m_levelOptionIconLayout.get()](int row, int col) { 
            return layoutPtr->getElementPos(row, col); 
        }, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
}

void SettingScene::constructHeightOptionUI() {
    ResourceManager& rm = m_ctx.resourceManager;

    int heightOptionCol = (MAX_HEIGHT + 1) / SETTING_SCENE::OPTION_ROW_NUM;

    // 载入高度设置框架
    m_heightFrameTexture = rm.getImage(HEIGHT_FRAME_IMAGE_PATH);

    // 创建高度选项标题文本
    m_heightTitle = std::make_unique<Text>(
        m_ctx,
        SETTING_SCENE::HEIGHT_TITLE_STR,
        SETTING_SCENE::HEIGHT_TITLE_POS
    );

    // 创建高度选项图标布局
    m_heightOptionIconLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::HEIGHT_OPTION_ICON_POS,
        SETTING_SCENE::OPTION_ICON_SPACING,
        SETTING_SCENE::OPTION_ICON_SPACING
    );

    // 创建高度选项文本
    m_heightOptionText.reserve(MAX_HEIGHT + 1);
    for (int i = 0; i <= MAX_HEIGHT; ++i) {
        SDL_Point pos = m_heightOptionIconLayout->getElementPos(i / heightOptionCol, i % heightOptionCol);
        m_heightOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i),
                SDL_Point{ pos.x + SETTING_SCENE::OPTION_MARGIN, pos.y + SETTING_SCENE::OPTION_MARGIN },
                SETTING_SCENE::OPTION_COLOR
            )
        );
    }

    // 创建高度选项文本
    m_heightOptionIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_optionIconTexture.get(), 
        [layoutPtr = m_heightOptionIconLayout.get()](int row, int col) { 
            return layoutPtr->getElementPos(row, col); 
        }, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
}

void SettingScene::constructRecordUI() {
    // 创建记录表布局
    m_recordOrderLayout = std::make_unique<VerticalLayout>(
        SETTING_SCENE::RECORD_ORDER_POS,
        SETTING_SCENE::RECORD_ROW_SPACING
    );
    // 创建记录表布局
    m_recordLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::RECORD_POS,
        SETTING_SCENE::RECORD_ROW_SPACING,
        SETTING_SCENE::RECORD_COL_SPACING
    );

    // 创建记录表头文本
    m_recordTitle.reserve(SETTING_SCENE::RECORD_TITLE_STR.size());
    for (int i = 0; i < SETTING_SCENE::RECORD_TITLE_STR.size(); ++i) {
        m_recordTitle.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                SETTING_SCENE::RECORD_TITLE_STR[i],
                m_recordLayout->getElementPos(0, i)
            )
        );
    }
    // 创建记录表内容文本，包括排名、姓名、分数、关卡数
    m_recordOrderText.reserve(RECORD_COUNT);
    m_recordNameText.reserve(RECORD_COUNT);
    m_recordScoreText.reserve(RECORD_COUNT);
    m_recordLvText.reserve(RECORD_COUNT);
    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordOrderText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i + 1),
                m_recordOrderLayout->getElementPos(i)
            )
        );
        m_recordNameText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 0)
            )
        );
        m_recordScoreText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 1)
            )
        );
        m_recordLvText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 2)
            )
        );
    }
}

void SettingScene::onEnter() {
    // 初始设置选项为关卡
    m_curSettingItem = SettingItem::LevelSetting;

    initGameTypeUI();
    initLevelOptionUI();
    initRecordUI();
}

void SettingScene::initGameTypeUI() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    std::string gameType = s.getGameType();
    m_gameTypeTitle->setStr(gameType);
    if (gameType == GAME_TYPE_A) {
        m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
    }
}

void SettingScene::initLevelOptionUI() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    std::string gameType = s.getGameType();
    if (gameType == GAME_TYPE_A) {
        m_levelFrameTexture = rm.getImage(LEVEL_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_levelFrameTexture = rm.getImage(LEVEL_B_FRAME_IMAGE_PATH);
    }
    // 关卡选项图标启动动画
    m_levelOptionIcon->playAnim();
}

void SettingScene::initRecordUI() {
    Settings& s = m_ctx.settings;

    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordNameText[i]->setStr(s.getRecordName(i));

        std::string scoreStr = std::to_string(s.getRecordScore(i));
        padLeft(scoreStr, SETTING_SCENE::RECORD_SCORE_MAX_LEN, '0');
        m_recordScoreText[i]->setStr(scoreStr);

        std::string lvStr = std::to_string(s.getRecordLv(i));
        padLeft(lvStr, SETTING_SCENE::RECORD_LV_MAX_LEN, '0');
        m_recordLvText[i]->setStr(lvStr);
    }
}

void SettingScene::onExit() {
    // 播放切换场景音效
    m_ctx.audioManager.playChunk(m_sceneChunk);

    // 选项图标停止动画
    m_levelOptionIcon->stopAnim();
    m_heightOptionIcon->stopAnim();
}

void SettingScene::onUpdate() {
    // 选项图标动画更新
    m_levelOptionIcon->onUpdate();
    m_heightOptionIcon->onUpdate();

    bool levelChanged = false;
    bool heightChanged = false;
    AudioManager& am = m_ctx.audioManager;
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    // 场景切换
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(GAME_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    } else if (im.isKeyJustPressed(SWITCH_SETTING_KEY)) {
        // 切换设置项，仅在B模式能切换
        // 仅目前所处设置项选项图标启动动画，其他设置项选项停止动画
        if (s.getGameType() == GAME_TYPE_B) {
            if (m_curSettingItem == SettingItem::LevelSetting) {
                m_curSettingItem = SettingItem::HeightSetting;
                m_levelOptionIcon->stopAnim();
                m_heightOptionIcon->playAnim();
            } else {
                m_curSettingItem = SettingItem::LevelSetting;
                m_levelOptionIcon->playAnim();
                m_heightOptionIcon->stopAnim();
            }

            // 播放切换选项音效
            am.playChunk(m_optionChunk);
        }
    } else {
        // 选项设置
        int levelOptionCol = (MAX_LEVEL + 1) / SETTING_SCENE::OPTION_ROW_NUM;
        int heightOptionCol = (MAX_HEIGHT + 1) / SETTING_SCENE::OPTION_ROW_NUM;
        // 左右键
        if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
            if (m_curSettingItem == SettingItem::LevelSetting) {
                levelChanged = s.setLevel(-1);
            } else {
                heightChanged = s.setHeight(-1);
            }
        } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
            if (m_curSettingItem == SettingItem::LevelSetting) {
                levelChanged = s.setLevel(1);
            } else {
                heightChanged = s.setHeight(1);
            }
        }
        // 上下键
        if (im.isKeyJustPressed(UP_KEY) && !im.isKeyPressed(DOWN_KEY)) {
            if (m_curSettingItem == SettingItem::LevelSetting) {
                levelChanged = s.setLevel(-levelOptionCol);
            } else {
                heightChanged = s.setHeight(-heightOptionCol);
            }
        } else if (im.isKeyJustPressed(DOWN_KEY) && !im.isKeyPressed(UP_KEY)) {
            if (m_curSettingItem == SettingItem::LevelSetting) {
                levelChanged = s.setLevel(levelOptionCol);
            } else {
                heightChanged = s.setHeight(heightOptionCol);
            }
        }
        // 如果有设置项变更，播放选项切换音效
        if (levelChanged || heightChanged) {
            am.playChunk(m_optionChunk);
        }
    }
}

void SettingScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;
    
    // 渲染游戏类型相关组件
    renderTexture(rdr, m_settingFrameTexture);
    renderGameTypeUI();

    // 渲染关卡选项相关组件
    renderLevelOptionUI();

    // 渲染高度选项相关组件
    if (s.getGameType() == GAME_TYPE_B) {
        renderHeightOptionUI();
    }

    // 渲染记录表
    renderRecordUI();
}

void SettingScene::renderGameTypeUI() {
    SDL_Renderer* rdr = m_ctx.renderer;
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeTitle->onRender();
}

void SettingScene::renderLevelOptionUI() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;

    int levelOptionCol = (MAX_LEVEL + 1) / SETTING_SCENE::OPTION_ROW_NUM;
    int level = s.getLevel();
    m_levelOptionIcon->onRender(level / levelOptionCol, level % levelOptionCol);
    renderTexture(rdr, m_levelFrameTexture, SETTING_SCENE::LEVEL_FRAME_POS);
    m_levelTitle->onRender();
    for (auto& text: m_levelOptionText) {
        text->onRender();
    }
}

void SettingScene::renderHeightOptionUI() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;

    int heightOptionCol = (MAX_HEIGHT + 1) / SETTING_SCENE::OPTION_ROW_NUM;
    int height = s.getHeight();
    m_heightOptionIcon->onRender(height / heightOptionCol, height % heightOptionCol);
    renderTexture(rdr, m_heightFrameTexture, SETTING_SCENE::HEIGHT_FRAME_POS);
    m_heightTitle->onRender();
    for (auto& text: m_heightOptionText) {
        text->onRender();
    }
}

void SettingScene::renderRecordUI() {
    for (auto& text: m_recordTitle) {
        text->onRender();
    }
    for (auto& text: m_recordOrderText) {
        text->onRender();
    }
    for (auto& text: m_recordNameText) {
        text->onRender();
    }
    for (auto& text: m_recordScoreText) {
        text->onRender();
    }
    for (auto& text: m_recordLvText) {
        text->onRender();
    }
}