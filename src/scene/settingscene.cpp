#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/util.h"

SettingScene::SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, SETTING_SCENE::BGCOLOR) {
    ResourceManager& rm = ctx.resourceManager;

    m_settingFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
    m_typeFrameTexture = nullptr;

    m_gameTypeText = std::make_unique<Text>(
        ctx,
        SETTING_SCENE::GAME_TYPE_TEXT_CONF.STR,
        SETTING_SCENE::GAME_TYPE_TEXT_CONF.POS,
        SETTING_SCENE::GAME_TYPE_TEXT_CONF.COLOR
    );
}

void SettingScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_ctx.settings;

    switch (s.getGameType()) {
        case 0: {
            m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
            m_gameTypeText->setStr(SETTING_SCENE::GAME_TYPE_A_STR);
            break;
        }
        case 1: {
            m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
            m_gameTypeText->setStr(SETTING_SCENE::GAME_TYPE_B_STR);
            break;
        }
        default: break;
    }
}

void SettingScene::onExit() {
    
}

void SettingScene::onUpdate() {
    InputManager& im = m_ctx.inputManager;

    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(GAME_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void SettingScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    
    renderTexture(rdr, m_settingFrameTexture);
    if (m_typeFrameTexture) {
        renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::TYPE_FRAME_POS);
    }

    m_gameTypeText->onRender();
}