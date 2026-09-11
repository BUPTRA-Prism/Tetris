/**
 * @file optionicon.cpp
 * @brief 选项图标实现
 */
#include "entity/optionicon.h"
#include "config/ui.h"

/**
 * @brief 构造选项图标，创建图片与闪烁动画
 */
OptionIcon::OptionIcon(ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view path)
    : m_img(std::make_unique<Image>(resourceMgr, renderer, path))
    , m_anim(std::make_unique<BlinkAnimation>(Config::UICommon::OPTION_ICON_HIDE_TOTAL_FRAME, Config::UICommon::OPTION_ICON_SHOW_TOTAL_FRAME)) {}

/**
 * @brief 更新动画并同步图片可见性
 *
 * 动画停止时图标常显，播放中按闪烁阶段控制显隐
 */
void OptionIcon::OnUpdate() {
    m_anim->OnUpdate();
    m_img->SetActive(m_anim->IsStopped() ? true : m_anim->IsShow());
}

/** @brief 渲染图标 */
void OptionIcon::OnRender(const MySDL::RenderParams& params) {
    m_img->OnRender(params);
}

/** @brief 播放图标动画 */
void OptionIcon::PlayAnim() {
    m_anim->Play();
}

/** @brief 停止图标动画 */
void OptionIcon::StopAnim() {
    m_anim->Stop();
}