#include "scene/titlescene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/util.h"

TitleScene::TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, TITLE_SCENE::BGCOLOR) {
    ResourceManager& rm = ctx.resourceManager;
    m_titleFrameTexture = rm.getImage(TITLE_FRAME_IMAGE_PATH);
    m_copyrightTexture = rm.getImage(COYRIGHT_ICON_IMAGE_PATH);
    m_startText = std::make_unique<Text>(
        ctx,
        TITLE_SCENE::START_TEXT::STR, 
        TITLE_SCENE::START_TEXT::POS,
        TITLE_SCENE::START_TEXT::COLOR
    );
    m_yearText = std::make_unique<Text>(
        ctx,
        TITLE_SCENE::YEAR_TEXT::STR, 
        TITLE_SCENE::YEAR_TEXT::POS,
        TITLE_SCENE::YEAR_TEXT::COLOR
    );
    m_titleMusic = rm.getMusic(TITLE_MUSIC_PATH);
}

void TitleScene::onEnter() {
    m_ctx.audioManager.playMusic(m_titleMusic, 0);
}

void TitleScene::onExit() {
    m_ctx.audioManager.stopMusic();
}

void TitleScene::onUpdate() {
    auto& im = m_ctx.inputManager;
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void TitleScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    renderTexture(rdr, m_titleFrameTexture);
    SDL_SetTextureColorMod(
        m_copyrightTexture, 
        TITLE_SCENE::COPYRIGHT_ICON::COLOR.r,
        TITLE_SCENE::COPYRIGHT_ICON::COLOR.g,
        TITLE_SCENE::COPYRIGHT_ICON::COLOR.b
    );
    renderTexture(rdr, m_copyrightTexture, TITLE_SCENE::COPYRIGHT_ICON::POS);
    m_startText->onRender();
    m_yearText->onRender();
}