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
    
    // 载入高度设置框架
    m_heightFrameTexture = rm.getImage(HEIGHT_FRAME_IMAGE_PATH);
    m_optionIconTexture = createSolidTexture(
        rdr, 
        SETTING_SCENE::OPTION_ICON_COLOR, 
        SETTING_SCENE::OPTION_ICON_SIZE.x, 
        SETTING_SCENE::OPTION_ICON_SIZE.y
    );

    m_gameTypeText = std::make_unique<Text>(
        ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TEXT_POS
    );

    m_levelText = std::make_unique<Text>(
        ctx,
        SETTING_SCENE::LEVEL_TEXT_STR,
        SETTING_SCENE::LEVEL_TEXT_POS
    );
    m_levelOptionText.resize(MAX_LEVEL + 1);
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        m_levelOptionText[i] = std::make_unique<Text>(
            ctx,
            std::to_string(i),
            SETTING_SCENE::LEVEL_OPTION_TEXT_POS[i],
            SETTING_SCENE::OPTION_TEXT_COLOR
        );
    }

    m_heightText = std::make_unique<Text>(
        ctx,
        SETTING_SCENE::HEIGHT_TEXT_STR,
        SETTING_SCENE::HEIGHT_TEXT_POS
    );
    m_heightOptionText.resize(MAX_HEIGHT + 1);
    for (int i = 0; i <= MAX_HEIGHT; ++i) {
        m_heightOptionText[i] = std::make_unique<Text>(
            ctx,
            std::to_string(i),
            SETTING_SCENE::HEIGHT_OPTION_TEXT_POS[i],
            SETTING_SCENE::OPTION_TEXT_COLOR
        );
    }

    m_recordTitleText.resize(SETTING_SCENE::RECORD_TITLE_TEXT_STR.size());
    for (int i = 0; i < SETTING_SCENE::RECORD_TITLE_TEXT_STR.size(); ++i) {
        m_recordTitleText[i] = std::make_unique<Text>(
            ctx,
            SETTING_SCENE::RECORD_TITLE_TEXT_STR[i],
            SETTING_SCENE::RECORD_TITLE_TEXT_POS[i]
        );
    }
    m_recordOrderText.resize(SETTING_SCENE::RECORD_ORDER_TEXT_POS.size());
    for (int i = 0; i < SETTING_SCENE::RECORD_ORDER_TEXT_POS.size(); ++i) {
        m_recordOrderText[i] = std::make_unique<Text>(
            ctx,
            std::to_string(i + 1),
            SETTING_SCENE::RECORD_ORDER_TEXT_POS[i]
        );
    }

    m_levelOptionIcon = std::make_unique<OptionIcon>(
        ctx, 
        m_optionIconTexture.get(), 
        SETTING_SCENE::LEVEL_OPTION_ICON_POS, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
    m_heightOptionIcon = std::make_unique<OptionIcon>(
        ctx, 
        m_optionIconTexture.get(), 
        SETTING_SCENE::HEIGHT_OPTION_ICON_POS, 
        SETTING_SCENE::OPTION_ICON_SHOW_FRAME, 
        SETTING_SCENE::OPTION_ICON_HIDE_FRAME
    );
}

void SettingScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;
    
    std::string gameType = s.getGameType();
    m_gameTypeText->setStr(gameType);
    if (gameType == GAME_TYPE_A) {
        m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
        m_levelFrameTexture = rm.getImage(LEVEL_A_FRAME_IMAGE_PATH);
    } else if (gameType == GAME_TYPE_B) {
        m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
        m_levelFrameTexture = rm.getImage(LEVEL_B_FRAME_IMAGE_PATH);
        m_heightOptionIcon->playAnim();
    }

    m_levelOptionIcon->playAnim();
}

void SettingScene::onExit() {
    m_levelOptionIcon->stopAnim();
    m_heightOptionIcon->stopAnim();
}

void SettingScene::onUpdate() {
    m_levelOptionIcon->onUpdate();
    m_heightOptionIcon->onUpdate();

    InputManager& im = m_ctx.inputManager;

    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(GAME_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void SettingScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;
    
    renderTexture(rdr, m_settingFrameTexture);
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeText->onRender();

    m_levelOptionIcon->onRender(0);
    renderTexture(rdr, m_levelFrameTexture, SETTING_SCENE::LEVEL_FRAME_POS);
    m_levelText->onRender();
    for (auto& text: m_levelOptionText) {
        text->onRender();
    }

    if (s.getGameType() == GAME_TYPE_B) {
        m_heightOptionIcon->onRender(0);
        renderTexture(rdr, m_heightFrameTexture, SETTING_SCENE::HEIGHT_FRAME_POS);
        m_heightText->onRender();
        for (auto& text: m_heightOptionText) {
            text->onRender();
        }
    }

    for (auto& text: m_recordTitleText) {
        text->onRender();
    }
    for (auto& text: m_recordOrderText) {
        text->onRender();
    }
}