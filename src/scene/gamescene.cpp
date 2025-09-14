#include "scene/gamescene.h"
#include "conf/sceneconf.h"
#include "util/util.h"

GameScene::GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    ResourceManager& rm = ctx.resourceManager;

    m_gameFrameTexture = rm.getImage(GAME_FRAME_IMAGE_PATH);
}

void GameScene::onEnter() {
    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    m_music = rm.getMusic(s.getMusicPath());
    am.playMusic(m_music);
}

void GameScene::onExit() {
    AudioManager& am = m_ctx.audioManager;

    am.stopMusic();
}

void GameScene::onUpdate() {
    
}

void GameScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;

    renderTexture(rdr, m_gameFrameTexture);
}