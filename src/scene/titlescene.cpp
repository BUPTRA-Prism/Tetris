/**
 * @file titlescene.cpp
 * @brief 标题场景实现
 */
#include "scene/titlescene.h"
#include "config/key.h"
#include "config/resource.h"
#include "config/ui.h"
#include "mysdl/render.h"
#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "framework/manager.h"
#include "framework/context.h"

/**
 * @brief 构造标题场景，创建标题、版权、提示与年份元素
 */
TitleScene::TitleScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    m_titleImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::TITLE_IMG);
    m_copyrightImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::COPYRIGHT_IMG);
    m_startText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::TitleSceneUI::START_TEXT_STR);
    m_yearText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::TitleSceneUI::YEAR_TEXT_STR);
}

/**
 * @brief 进入场景，播放标题音乐
 */
void TitleScene::OnEnter() {
    m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, Resource::Audio::TITLE_MUSIC, 1);
}

/**
 * @brief 退出场景，停止音乐
 */
void TitleScene::OnExit() {
    m_ctx.manager.audioMgr.StopMusic();
}

/**
 * @brief 更新：按下确认键后进入菜单场景
 */
void TitleScene::OnUpdate() {
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::NEXT_SCENE_KEY)) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LOAD_SCENE_CHUNK);
        m_loadSceneCallback(Config::MenuSceneUI::NAME);
    }
}

/**
 * @brief 渲染标题、版权、提示与年份
 */
void TitleScene::RenderContent() {
    m_titleImg->OnRender();
    m_copyrightImg->OnRender(MySDL::RenderParams{
        Config::TitleSceneUI::COPYRIGHT_IMG_POS, 
        Config::TitleSceneUI::COPYRIGHT_IMG_COLOR
    });
    m_startText->OnRender(MySDL::RenderParams{ Config::TitleSceneUI::START_TEXT_POS });
    m_yearText->OnRender(MySDL::RenderParams{ Config::TitleSceneUI::YEAR_TEXT_POS });
}