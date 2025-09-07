#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/util.h"

SettingScene::SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    // ResourceManager& rm = ctx.resourceManager;
    // SDL_Renderer* rdr = ctx.renderer;

    // m_settingFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
    // m_typeFrameTexture = nullptr;
    // m_levelFrameTexture = nullptr;
    // m_heightFrameTexture = rm.getImage(HEIGHT_FRAME_IMAGE_PATH);
    // m_optionIconTexture = createSolidTexture(
    //     rdr, 
    //     SETTING_SCENE::OPTION_COLOR, 
    //     SETTING_SCENE::OPTION_SIZE.x, 
    //     SETTING_SCENE::OPTION_SIZE.y
    // );

    // m_gameTypeText = std::make_unique<Text>(
    //     ctx,
    //     "",
    //     SETTING_SCENE::GAME_TYPE_TEXT_CONF.POS
    // );
    // m_levelText = std::make_unique<Text>(
    //     ctx,
    //     SETTING_SCENE::LEVEL_TITLE_TEXT_CONF.STR,
    //     SETTING_SCENE::LEVEL_TITLE_TEXT_CONF.POS
    // );
    // m_heightText = std::make_unique<Text>(
    //     ctx,
    //     SETTING_SCENE::HEIGHT_TITLE_TEXT_CONF.STR,
    //     SETTING_SCENE::HEIGHT_TITLE_TEXT_CONF.POS,
    //     SETTING_SCENE::HEIGHT_TITLE_TEXT_CONF.COLOR
    // );
    // m_levelText.resize(MAX_LEVEL + 1);
    // m_heightText.resize(MAX_HEIGHT + 1);
    // for (int i = 0; i <= MAX_LEVEL; ++i) {
    //     m_levelText[i] = std::make_unique<Text>(
    //         ctx,
    //         std::to_string(i),
    //         SETTING_SCENE::LEVEL_TEXT_POS[i],
    //         SETTING_SCENE::LEVEL_HEIGHT_COLOR
    //     );
    // }
    // for (int i = 0; i <= MAX_HEIGHT; ++i) {
    //     m_heightText[i] = std::make_unique<Text>(
    //         ctx,
    //         std::to_string(i),
    //         SETTING_SCENE::HEIGHT_TEXT_POS[i],
    //         SETTING_SCENE::LEVEL_HEIGHT_COLOR
    //     );
    // }

    // m_levelOption = std::make_unique<Option>(
    //     ctx, 
    //     m_optionTexture.get(), 
    //     SETTING_SCENE::LEVEL_OPTION_POS, 
    //     SETTING_SCENE::OPTION_SHOW_FRAME, 
    //     SETTING_SCENE::OPTION_HIDE_FRAME
    // );
    // m_heightOption = std::make_unique<Option>(
    //     ctx, 
    //     m_optionTexture.get(), 
    //     SETTING_SCENE::HEIGHT_OPTION_POS, 
    //     SETTING_SCENE::OPTION_SHOW_FRAME, 
    //     SETTING_SCENE::OPTION_HIDE_FRAME
    // );
}

void SettingScene::onEnter() {
    // ResourceManager& rm = m_ctx.resourceManager;
    // Settings& s = m_ctx.settings;
    // int gameTypeIdx = s.getGameTypeIdx();

    // switch (gameTypeIdx) {
    //     case 0: {
    //         m_typeFrameTexture = rm.getImage(TYPE_A_FRAME_IMAGE_PATH);
    //         m_levelFrameTexture = rm.getImage(LEVEL_A_FRAME_IMAGE_PATH);
    //         break;
    //     }
    //     case 1: {
    //         m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
    //         m_levelFrameTexture = rm.getImage(LEVEL_B_FRAME_IMAGE_PATH);
    //         break;
    //     }
    //     default: break;
    // }
    // m_gameTypeText->setStr(GAME_TYPE[s.getGameTypeIdx()]);
    // m_levelOption->playAnim();
}

void SettingScene::onExit() {
    // m_levelOption->stopAnim();
}

void SettingScene::onUpdate() {
    // m_levelOption->onUpdate();

    // InputManager& im = m_ctx.inputManager;

    // if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
    //     m_loadSceneCallback(GAME_SCENE::NAME);
    // } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
    //     m_loadSceneCallback(MENU_SCENE::NAME);
    // }
}

void SettingScene::renderContent() {
    // SDL_Renderer* rdr = m_ctx.renderer;
    // Settings& s = m_ctx.settings;
    
    // renderTexture(rdr, m_settingFrameTexture);
    // renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::TYPE_FRAME_POS);
    // m_gameTypeText->onRender();

    // m_levelOption->onRender(0);
    // renderTexture(rdr, m_levelFrameTexture, SETTING_SCENE::LEVEL_FRAME_POS);
    // m_levelTitleText->onRender();
    // for (auto& text: m_levelText) {
    //     text->onRender();
    // }

    // if (s.getGameTypeIdx() == 1) {
    //     renderTexture(rdr, m_heightFrameTexture, SETTING_SCENE::HEIGHT_FRAME_POS);
    //     m_heightTitleText->onRender();
    //     for (auto& text: m_heightText) {
    //         text->onRender();
    //     }
    // }
}