#include "scene/titlescene.h"
#include "conf/resourceconf.h"
#include "conf/uiconf.h"
#include "conf/keyconf.h"
#include "util/render.h"

TitleScene::TitleScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, core, loadSceneCallback) {
    ResourceManager& rm = ctx.resourceManager;

    m_titleFrame = rm.getImage(TITLE_FRAME_PATH);
    m_titleImg = rm.getImage(TITLE_IMAGE_PATH);

    m_titleText = std::make_unique<Text>(
        ctx,
        TITLE_SCENE::TITLE_TEXT_STR,
        TITLE_SCENE::TITLE_TEXT_POS,
        TITLE_SCENE::TITLE_TEXT_COLOR
    );

    m_music = rm.getMusic(TITLE_MUSIC_PATH);
    m_nextSceneChunk = rm.getChunk(NEXT_SCENE_CHUNK_PATH);
}

void TitleScene::onEnter() {
    AudioManager& am = m_ctx.audioManager;

    m_fireworkCnt = 0;
    m_fireworkCreateFrameCnt = 0;

    am.playMusic(m_music, 0);
}

void TitleScene::onExit() {
    AudioManager& am = m_ctx.audioManager;

    if (m_firework) {
        m_firework->stopAnim();
    }

    am.stopMusic();
    am.playChunk(m_nextSceneChunk);
}

void TitleScene::onUpdate() {
    InputManager& im = m_ctx.inputManager;

    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(SETTING_SCENE::NAME);
    }

    if (m_firework) {
        if (m_firework->isAnimPlaying()) {
            m_firework->onUpdate();
        } else {
            m_firework.reset();
        }
    }

    if (m_fireworkCreateFrameCnt >= TITLE_SCENE::FIREWORK_CREATE_FRAME_TARGET) {
        if (m_fireworkCnt < TITLE_SCENE::FIREWORK_TARGET) {
            ++m_fireworkCnt;
            m_fireworkCreateFrameCnt = 0;
            m_firework = std::make_unique<Firework>(
                m_ctx,
                TITLE_SCENE::FIREWORK_ALT_COLORS,
                TITLE_SCENE::FIREWORK_BORDER
            );
            m_firework->playAnim();
        }
    } else {
        ++m_fireworkCreateFrameCnt;
    }
}

void TitleScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;

    if (m_firework) {
        m_firework->onRender();
    }

    renderTexture(rdr, m_titleFrame);

    m_titleText->onRender();
    renderTexture(rdr, m_titleImg, TITLE_SCENE::TITLE_IMAGE_POS);
}