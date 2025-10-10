#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/common.h"
#include "util/render.h"

SettingScene::SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    // 初始化场景框架
    setupFrame();

    // 初始化各区域
    setupGameTypeRegion();
    setupLevelOptionRegion();
    setupHeightOptionRegion();
    setupRecordRegion();
    
    // 初始化相关音频
    setupAudio();
}

void SettingScene::onEnter() {
    // 激活场景框架
    enableFrame();

    // 激活各区域
    enableGameTypeRegion();
    enableLevelOptionRegion();
    enableRecordRegion();
}

void SettingScene::onExit() {
    // 禁用选项区域
    disableOptionRegion();
    // 禁用相关音频
    disableAudio();
}

void SettingScene::onUpdate() {
    // 选项图标动画更新
    updateOptionIconAnimation();

    // 场景切换
    if (updateSceneSwitch()) {
        return ;
    }

    // 切换设置项
    bool settingItemChanged = updateSettingItemSwitch();
    // 切换设置
    bool settingValueChanged = updateSettingValue();


    // 如果切换设置成功，更新音频
    if (settingItemChanged || settingValueChanged) {
        updateAudio();
    }
}

void SettingScene::renderContent() {
    Settings& s = m_ctx.settings;
    
    // 渲染场景框架
    renderFrame();
    
    // 渲染游戏模式区域
    renderGameTypeRegion();

    // 渲染等级选项区域
    renderLevelOptionRegion();

    // 当游戏模式为B模式，渲染高度选项区域
    if (s.getGameType() == GAME_TYPE_B) {
        renderHeightOptionRegion();
    }

    // 渲染排行榜区域
    renderRecordRegion();
}

void SettingScene::setupFrame() {
    ResourceManager& rm = m_ctx.resourceManager;
    SDL_Renderer* rdr = m_ctx.renderer;

    // 载入设置框架
    m_settingFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
    
    // 创建选项图标（纯色块）
    m_optionIconTexture = createSolidTexture(
        rdr, 
        SETTING_SCENE::OPTION_ICON_COLOR, 
        SETTING_SCENE::OPTION_ICON_SIZE, 
        SETTING_SCENE::OPTION_ICON_SIZE
    );
}

void SettingScene::setupGameTypeRegion() {
    // 游戏模式框架初始化为nullptr（要在激活时赋值）
    m_typeFrameTexture = nullptr;

    // 创建游戏模式标题文本
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TITLE_POS
    );
}

void SettingScene::setupLevelOptionRegion() {
    // 等级选项框架初始化为nullptr（要在激活时赋值）
    m_levelFrameTexture = nullptr;

    int levelOptionCol = (MAX_INIT_LEVEL + 1) / SETTING_SCENE::OPTION_ROW_NUM;

    // 创建等级选项标题文本
    m_levelTitle = std::make_unique<Text>(
        m_ctx,
        SETTING_SCENE::LEVEL_TITLE_STR,
        SETTING_SCENE::LEVEL_TITLE_POS
    );

    // 创建等级选项布局
    m_levelOptionLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::LEVEL_OPTION_POS,
        SETTING_SCENE::OPTION_SPACING,
        SETTING_SCENE::OPTION_SPACING
    );

    // 创建等级选项文本
    m_levelOptionText.reserve(MAX_INIT_LEVEL + 1);
    for (int i = 0; i <= MAX_INIT_LEVEL; ++i) {
        m_levelOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i),
                m_levelOptionLayout->getElementPos(i / levelOptionCol, i % levelOptionCol),
                SETTING_SCENE::OPTION_COLOR
            )
        );
    }

    // 创建等级选项图标
    m_levelOptionIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_optionIconTexture.get(), 
        [layoutPtr = m_levelOptionLayout.get(), levelOptionCol](int idx) {
            SDL_Point optionPos = layoutPtr->getElementPos(idx / levelOptionCol, idx % levelOptionCol);
            return SDL_Point{
                optionPos.x + SETTING_SCENE::OPTION_ICON_OFFSET, 
                optionPos.y + SETTING_SCENE::OPTION_ICON_OFFSET
            }; 
        }, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
}

void SettingScene::setupHeightOptionRegion() {
    ResourceManager& rm = m_ctx.resourceManager;

    int heightOptionCol = (MAX_INIT_HEIGHT + 1) / SETTING_SCENE::OPTION_ROW_NUM;

    // 载入高度设置框架
    m_heightFrameTexture = rm.getImage(HEIGHT_FRAME_IMAGE_PATH);

    // 创建高度选项标题文本
    m_heightTitle = std::make_unique<Text>(
        m_ctx,
        SETTING_SCENE::HEIGHT_TITLE_STR,
        SETTING_SCENE::HEIGHT_TITLE_POS
    );

    // 创建高度选项图标布局
    m_heightOptionLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::HEIGHT_OPTION_POS,
        SETTING_SCENE::OPTION_SPACING,
        SETTING_SCENE::OPTION_SPACING
    );

    // 创建高度选项文本
    m_heightOptionText.reserve(MAX_INIT_HEIGHT + 1);
    for (int i = 0; i <= MAX_INIT_HEIGHT; ++i) {
        m_heightOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i),
                m_heightOptionLayout->getElementPos(i / heightOptionCol, i % heightOptionCol),
                SETTING_SCENE::OPTION_COLOR
            )
        );
    }

    // 创建高度选项图标
    m_heightOptionIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_optionIconTexture.get(), 
        [layoutPtr = m_heightOptionLayout.get(), heightOptionCol](int idx) { 
            SDL_Point optionPos = layoutPtr->getElementPos(idx / heightOptionCol, idx % heightOptionCol);
            return SDL_Point{
                optionPos.x + SETTING_SCENE::OPTION_ICON_OFFSET, 
                optionPos.y + SETTING_SCENE::OPTION_ICON_OFFSET
            };
        }, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
}

void SettingScene::setupRecordRegion() {
    // 创建排行榜名次布局
    m_recordOrderLayout = std::make_unique<VerticalLayout>(
        SETTING_SCENE::RECORD_ORDER_POS,
        SETTING_SCENE::RECORD_ROW_SPACING
    );
    // 创建排行榜布局
    m_recordLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::RECORD_POS,
        SETTING_SCENE::RECORD_ROW_SPACING,
        SETTING_SCENE::RECORD_COL_SPACING
    );

    // 创建排行榜表头文本
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
    // 创建排行榜内容文本，包括名次、姓名、分数、等级
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

void SettingScene::setupAudio() {
    ResourceManager& rm = m_ctx.resourceManager;

    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);     // 载入切换选项音效
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);       // 载入切换场景音效
}

void SettingScene::enableFrame() {
    // 初始设置选项为等级
    m_curSettingItem = SettingItem::LevelSetting;
}

void SettingScene::enableGameTypeRegion() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    std::string gameType = s.getGameType();
    // 游戏模式标题文本赋值
    m_gameTypeTitle->setStr(gameType);
    // 游戏模式框架根据具体类型赋值
    if (gameType == GAME_TYPE_A) {
        m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
    }
}

void SettingScene::enableLevelOptionRegion() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    std::string gameType = s.getGameType();
    // 等级选项框架根据具体类型赋值
    if (gameType == GAME_TYPE_A) {
        m_levelFrameTexture = rm.getImage(LEVEL_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_levelFrameTexture = rm.getImage(LEVEL_B_FRAME_IMAGE_PATH);
    }
    // 等级选项图标启动动画
    m_levelOptionIcon->playAnim();
}

void SettingScene::enableRecordRegion() {
    Settings& s = m_ctx.settings;

    // 排行榜各属性对应文本赋值
    for (int i = 0; i < RECORD_COUNT; ++i) {
        Record record = s.getRecordInfo(i);

        m_recordNameText[i]->setStr(record.name);

        std::string scoreStr = std::to_string(record.score);
        padLeft(scoreStr, RECORD_SCORE_MAX_LEN, '0');
        m_recordScoreText[i]->setStr(scoreStr);

        std::string lvStr = std::to_string(record.lv);
        padLeft(lvStr, RECORD_LV_MAX_LEN, '0');
        m_recordLvText[i]->setStr(lvStr);
    }
}

void SettingScene::disableOptionRegion() {
    // 选项图标停止动画
    m_levelOptionIcon->stopAnim();
    m_heightOptionIcon->stopAnim();
}

void SettingScene::disableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 播放切换场景音效
    am.playChunk(m_sceneChunk);
}

void SettingScene::updateOptionIconAnimation() {
    // 选项图标动画更新
    m_levelOptionIcon->onUpdate();
    m_heightOptionIcon->onUpdate();
}

bool SettingScene::updateSceneSwitch() {
    InputManager& im = m_ctx.inputManager;

    bool sceneChanged = false;
    // 场景切换
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(GAME_SCENE::NAME);
        sceneChanged = true;
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
        sceneChanged = true;
    }

    return sceneChanged;
}

bool SettingScene::updateSettingItemSwitch() {
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    // 切换设置项，仅在B模式能切换
    if (s.getGameType() == GAME_TYPE_B && im.isKeyJustPressed(SWITCH_SETTING_KEY)) {
        // 仅目前所处设置项选项图标启动动画，其他设置项选项停止动画
        switch (m_curSettingItem) {
            case SettingItem::LevelSetting: {
                m_curSettingItem = SettingItem::HeightSetting;
                m_levelOptionIcon->stopAnim();
                m_heightOptionIcon->playAnim();
                break;
            }
            case SettingItem::HeightSetting: {
                m_curSettingItem = SettingItem::LevelSetting;
                m_levelOptionIcon->playAnim();
                m_heightOptionIcon->stopAnim();
                break;
            }
            default: break;
        }
        return true;
    }

    return false;
}

bool SettingScene::updateSettingValue() {
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    // 选项设置
    int levelOptionCol = (MAX_INIT_LEVEL + 1) / SETTING_SCENE::OPTION_ROW_NUM;
    int heightOptionCol = (MAX_INIT_HEIGHT + 1) / SETTING_SCENE::OPTION_ROW_NUM;

    bool settingValueChanged = false;
    // lambda：根据当前设置项和增量改变值
    auto changeSettingValue = [&](int delta) -> bool {
        switch (m_curSettingItem) {
            case SettingItem::LevelSetting:  return s.setInitLevel(delta);
            case SettingItem::HeightSetting: return s.setInitHeight(delta);
            default: return false;
        }
    };
    // 左右键
    if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
        settingValueChanged |= changeSettingValue(-1);
    } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
        settingValueChanged |= changeSettingValue(1);
    }
    // 上下键
    int upDownDelta = m_curSettingItem == SettingItem::LevelSetting ? levelOptionCol : heightOptionCol;
    if (im.isKeyJustPressed(UP_KEY) && !im.isKeyPressed(DOWN_KEY)) {
        settingValueChanged |= changeSettingValue(-upDownDelta);
    } else if (im.isKeyJustPressed(DOWN_KEY) && !im.isKeyPressed(UP_KEY)) {
        settingValueChanged |= changeSettingValue(upDownDelta);
    }

    return settingValueChanged;
}

void SettingScene::updateAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 播放选项切换音效
    am.playChunk(m_optionChunk);
}

void SettingScene::renderFrame() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染场景框架
    renderTexture(rdr, m_settingFrameTexture);
}

void SettingScene::renderGameTypeRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染游戏模式框架与标题
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeTitle->onRender();
}

void SettingScene::renderLevelOptionRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;

    int level = s.getInitLevel();
    // 渲染等级选项图标
    m_levelOptionIcon->onRender(level);
    // 渲染等级选项框架
    renderTexture(rdr, m_levelFrameTexture, SETTING_SCENE::LEVEL_FRAME_POS);
    // 渲染等级选项标题与文本
    m_levelTitle->onRender();
    for (auto& text: m_levelOptionText) {
        text->onRender();
    }
}

void SettingScene::renderHeightOptionRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;

    int height = s.getInitHeight();
    // 渲染高度选项图标
    m_heightOptionIcon->onRender(height);
    // 渲染高度选项框架
    renderTexture(rdr, m_heightFrameTexture, SETTING_SCENE::HEIGHT_FRAME_POS);
    // 渲染高度选项标题与文本
    m_heightTitle->onRender();
    for (auto& text: m_heightOptionText) {
        text->onRender();
    }
}

void SettingScene::renderRecordRegion() {
    // 渲染排行榜各文本
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