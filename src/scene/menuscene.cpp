#include "scene/menuscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/util.h"

MenuScene::MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, MENU_SCENE::BGCOLOR)
    , m_music(nullptr) {
    ResourceManager& rm = ctx.resourceManager;
    m_menuFrameTexture = rm.getImage(MENU_FRAME_IMAGE_PATH);
    m_gameTypeTitleText = std::make_unique<Text>(
        ctx,
        MENU_SCENE::GAME_TYPE_TITLE_TEXT_CONF.STR,
        MENU_SCENE::GAME_TYPE_TITLE_TEXT_CONF.POS,
        MENU_SCENE::GAME_TYPE_TITLE_TEXT_CONF.COLOR
    );
    m_musicTypeTitleText = std::make_unique<Text>(
        ctx,
        MENU_SCENE::MUSIC_TYPE_TITLE_TEXT_CONF.STR,
        MENU_SCENE::MUSIC_TYPE_TITLE_TEXT_CONF.POS,
        MENU_SCENE::MUSIC_TYPE_TITLE_TEXT_CONF.COLOR
    );
    int gameTypeCnt = MENU_SCENE::GAME_TYPE_TEXT_CONF.size();
    int musicTypeCnt = MENU_SCENE::MUSIC_TYPE_TEXT_CONF.size();
    m_gameTypeText.reserve(gameTypeCnt);
    m_musicTypeText.reserve(musicTypeCnt);
    for (int i = 0; i < gameTypeCnt; ++i) {
        m_gameTypeText.emplace_back(
            std::make_unique<Text>(
                ctx,
                MENU_SCENE::GAME_TYPE_TEXT_CONF[i].STR,
                MENU_SCENE::GAME_TYPE_TEXT_CONF[i].POS,
                MENU_SCENE::GAME_TYPE_TEXT_CONF[i].COLOR
            )
        );
    }
    for (int i = 0; i < musicTypeCnt; ++i) {
        m_musicTypeText.emplace_back(
            std::make_unique<Text>(
                ctx,
                MENU_SCENE::MUSIC_TYPE_TEXT_CONF[i].STR,
                MENU_SCENE::MUSIC_TYPE_TEXT_CONF[i].POS,
                MENU_SCENE::MUSIC_TYPE_TEXT_CONF[i].COLOR
            )
        );
    }
    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);
}

void MenuScene::onEnter() {
    auto& rm = m_ctx.resourceManager;
    auto& am = m_ctx.audioManager;
    auto& s = m_ctx.settings;
    m_music = rm.getMusic(s.getMusicType());
    if (m_music) {
        am.playMusic(m_music);
    } else {
        am.stopMusic();
    }
}

void MenuScene::onExit() {
    m_ctx.audioManager.stopMusic();
}

void MenuScene::onUpdate() {
    bool m_gameTypeChanged = false;
    bool m_musicTypeChanged = false;
    auto& im = m_ctx.inputManager;
    auto& s = m_ctx.settings;
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(SETTING_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(TITLE_SCENE::NAME);
    } else {
        if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
            m_gameTypeChanged = s.setGameType(-1);
        } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
            m_gameTypeChanged = s.setGameType(1);
        }
        if (im.isKeyJustPressed(UP_KEY) && !im.isKeyPressed(DOWN_KEY)) {
            m_musicTypeChanged = s.setMusicType(-1);
        } else if (im.isKeyJustPressed(DOWN_KEY) && !im.isKeyPressed(UP_KEY)) {
            m_musicTypeChanged = s.setMusicType(1);
        }
    }

    auto& rm = m_ctx.resourceManager;
    auto& am = m_ctx.audioManager;
    if (m_gameTypeChanged || m_musicTypeChanged) {
        am.playChunk(m_optionChunk);
    }
    if (m_musicTypeChanged) {
        m_music = rm.getMusic(s.getMusicType());
        if (m_music) {
            am.playMusic(m_music);
        } else {
            am.stopMusic();
        }
    }
}

void MenuScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    renderTexture(rdr, m_menuFrameTexture);
    m_gameTypeTitleText->onRender();
    m_musicTypeTitleText->onRender();
    for (auto& text: m_gameTypeText) {
        text->onRender();
    }
    for (auto& text: m_musicTypeText) {
        text->onRender();
    }
}