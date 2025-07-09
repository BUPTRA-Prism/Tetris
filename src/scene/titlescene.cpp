#include "scene/titlescene.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/util.h"

TitleScene::TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, TITLE_SCENE::BGCOLOR) {
    ResourceManager& rm = ctx.resourceManager;
    m_titleFrameTexture = rm.getImage(TITLE_FRAME_IMAGE_PATH);
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
}

void TitleScene::onEnter() {

}

void TitleScene::onExit() {
    
}

void TitleScene::onInput() {
    
}

void TitleScene::onUpdate() {
    
}

void TitleScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    renderTexture(rdr, m_titleFrameTexture);
    m_startText->onRender();
    m_yearText->onRender();
}