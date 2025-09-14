#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/util.h"

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

    // 初始化各区域组件
    initGameType();
    initLevelOption();
    initHeightOption();
    initRecord();
}

void SettingScene::initGameType() {
    // 创建游戏类型标题文本
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TITLE_POS
    );
}

void SettingScene::initLevelOption() {
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
    m_levelOption.reserve(MAX_LEVEL + 1);
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        SDL_Point pos = m_levelOptionIconLayout->getElementPos(i / levelOptionCol, i % levelOptionCol);
        m_levelOption.emplace_back(
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

void SettingScene::initHeightOption() {
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
    m_heightOption.reserve(MAX_HEIGHT + 1);
    for (int i = 0; i <= MAX_HEIGHT; ++i) {
        SDL_Point pos = m_heightOptionIconLayout->getElementPos(i / heightOptionCol, i % heightOptionCol);
        m_heightOption.emplace_back(
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

void SettingScene::initRecord() {
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
                m_recordLayout->getElementPos(0, i + 1)
            )
        );
    }
    // 创建记录表内容文本，包括排名、姓名、分数、关卡数
    m_recordOrder.reserve(RECORD_COUNT);
    m_recordName.reserve(RECORD_COUNT);
    m_recordScore.reserve(RECORD_COUNT);
    m_recordLv.reserve(RECORD_COUNT);
    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordOrder.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::string(5, ' ') + std::to_string(i + 1),
                m_recordLayout->getElementPos(i + 1, 0)
            )
        );
        m_recordName.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 1)
            )
        );
        m_recordScore.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 2)
            )
        );
        m_recordLv.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 3)
            )
        );
    }
}

void SettingScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;
    
    // 获取游戏类型
    std::string gameType = s.getGameType();
    m_gameTypeTitle->setStr(gameType);

    // 根据游戏类型载入游戏类型框架和关卡选项框架纹理
    if (gameType == GAME_TYPE_A) {
        m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
        m_levelFrameTexture = rm.getImage(LEVEL_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
        m_levelFrameTexture = rm.getImage(LEVEL_B_FRAME_IMAGE_PATH);
        // 如果是B模式，高度选项图标启动动画
        m_heightOptionIcon->playAnim();
    }
    // 关卡选项图标启动动画
    m_levelOptionIcon->playAnim();

    // 读取记录表内容
    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordName[i]->setStr(s.getRecordName(i));

        std::string scoreStr = std::to_string(s.getRecordScore(i));
        m_recordScore[i]->setStr(
            std::string(SETTING_SCENE::RECORD_SCORE_MAX_LEN - scoreStr.length(), '0') + scoreStr
        );

        std::string lvStr = std::to_string(s.getRecordLv(i));
        m_recordLv[i]->setStr(
            std::string(SETTING_SCENE::RECORD_LV_MAX_LEN - lvStr.length(), '0') + lvStr
        );
    }
}

void SettingScene::onExit() {
    // 选项图标停止动画
    m_levelOptionIcon->stopAnim();
    m_heightOptionIcon->stopAnim();
}

void SettingScene::onUpdate() {
    // 选项图标动画更新
    m_levelOptionIcon->onUpdate();
    m_heightOptionIcon->onUpdate();

    InputManager& im = m_ctx.inputManager;

    // 场景切换
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(GAME_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void SettingScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;
    
    // 渲染游戏类型相关组件
    renderTexture(rdr, m_settingFrameTexture);
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeTitle->onRender();

    // 渲染关卡选项相关组件
    m_levelOptionIcon->onRender(0, 0);
    renderTexture(rdr, m_levelFrameTexture, SETTING_SCENE::LEVEL_FRAME_POS);
    m_levelTitle->onRender();
    for (auto& text: m_levelOption) {
        text->onRender();
    }

    // 渲染高度选项相关组件
    if (s.getGameType() == GAME_TYPE_B) {
        m_heightOptionIcon->onRender(0, 0);
        renderTexture(rdr, m_heightFrameTexture, SETTING_SCENE::HEIGHT_FRAME_POS);
        m_heightTitle->onRender();
        for (auto& text: m_heightOption) {
            text->onRender();
        }
    }

    // 渲染记录表
    for (auto& text: m_recordTitle) {
        text->onRender();
    }
    for (auto& text: m_recordOrder) {
        text->onRender();
    }
    for (auto& text: m_recordName) {
        text->onRender();
    }
    for (auto& text: m_recordScore) {
        text->onRender();
    }
    for (auto& text: m_recordLv) {
        text->onRender();
    }
}