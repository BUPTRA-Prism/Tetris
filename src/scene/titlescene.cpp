#include "scene/titlescene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "util/util.h"

TitleScene::TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    ResourceManager& rm = ctx.resourceManager;

    //加载标题框与版权图标纹理
    m_titleFrameTexture = rm.getImage(TITLE_FRAME_IMAGE_PATH);
    m_copyrightTexture = rm.getImage(COYRIGHT_ICON_IMAGE_PATH);

    // 创建开始游戏文本
    m_startText = std::make_unique<Text>(
        ctx,
        TITLE_SCENE::START_TEXT_STR, 
        TITLE_SCENE::START_TEXT_POS
    );
    // 创建年份文本
    m_yearText = std::make_unique<Text>(
        ctx,
        TITLE_SCENE::YEAR_TEXT_STR, 
        TITLE_SCENE::YEAR_TEXT_POS
    );
    // 获取标题场景背景音乐
    m_titleMusic = rm.getMusic(TITLE_MUSIC_PATH);
}

void TitleScene::onEnter() {
    // 进入场景时，播放背景音乐
    m_ctx.audioManager.playMusic(m_titleMusic, 0);
}

void TitleScene::onExit() {
    // 退出场景时，停止背景音乐
    m_ctx.audioManager.stopMusic();
}

void TitleScene::onUpdate() {
    // 检测场景切换按键
    // 如果刚刚按下，调用回调切换到菜单场景
    InputManager& im = m_ctx.inputManager;
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(MENU_SCENE::NAME);
    }
}

void TitleScene::renderContent() {
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