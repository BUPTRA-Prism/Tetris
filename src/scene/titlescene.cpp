#include "scene/titlescene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/render.h"

TitleScene::TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    // 初始化场景框架
    setupFrame();
    // 初始化相关音频
    setupAudio();
}

void TitleScene::onEnter() {
    // 激活音频
    enableAudio();
}

void TitleScene::onExit() {
    // 禁用音频
    disableAudio();
}

void TitleScene::onUpdate() {
    // 场景切换
    updateSceneSwitch();
}

void TitleScene::renderContent() {
    // 渲染场景框架
    renderFrame();
}

void TitleScene::setupFrame() {
    ResourceManager& rm = m_ctx.resourceManager;

    //加载标题框与版权图标纹理
    m_titleFrameTexture = rm.getImage(TITLE_FRAME_IMAGE_PATH);
    m_copyrightTexture = rm.getImage(COYRIGHT_ICON_IMAGE_PATH);

    // 创建开始游戏文本
    m_startText = std::make_unique<Text>(
        m_ctx,
        TITLE_SCENE::START_TEXT_STR, 
        TITLE_SCENE::START_TEXT_POS
    );
    // 创建年份文本
    m_yearText = std::make_unique<Text>(
        m_ctx,
        TITLE_SCENE::YEAR_TEXT_STR, 
        TITLE_SCENE::YEAR_TEXT_POS
    );
}

void TitleScene::setupAudio() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 获取标题场景背景音乐
    m_titleMusic = rm.getMusic(TITLE_MUSIC_PATH);
    // 获取切换场景音效
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);
}

void TitleScene::enableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 进入场景时，播放背景音乐
    am.playMusic(m_titleMusic, 0);
}

void TitleScene::disableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 退出场景时，停止背景音乐
    am.stopMusic();
    // 退出场景时，播放切换场景音效
    am.playChunk(m_sceneChunk);
}

void TitleScene::updateSceneSwitch() {
    InputManager& im = m_ctx.inputManager;

    // 场景切换
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void TitleScene::renderFrame() {
    SDL_Renderer* rdr = m_ctx.renderer;
    // 绘制标题框
    renderTexture(rdr, m_titleFrameTexture);

    // 设置版权图标纹理颜色并绘制
    SDL_SetTextureColorMod(
        m_copyrightTexture, 
        TITLE_SCENE::COPYRIGHT_ICON_COLOR.r,
        TITLE_SCENE::COPYRIGHT_ICON_COLOR.g,
        TITLE_SCENE::COPYRIGHT_ICON_COLOR.b
    );
    renderTexture(rdr, m_copyrightTexture, TITLE_SCENE::COPYRIGHT_ICON_POS);
    
    // 渲染文本
    m_startText->onRender();
    m_yearText->onRender();
}