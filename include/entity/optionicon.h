/**
 * @file optionicon.h
 * @brief 选项图标实体，组合图片与闪烁动画
 */
#pragma once

#include "mysdl/render.h"
#include "core/graphics/image.h"
#include "core/animation/blinkanimation.h"
#include <memory>
#include <string_view>

class ResourceManager;

/**
 * @brief 选项图标，持有图片并叠加闪烁动画控制显示
 */
class OptionIcon {
private:
    std::unique_ptr<Image> m_img;           ///< 图标图片
    std::unique_ptr<BlinkAnimation> m_anim; ///< 闪烁动画

public:
    /**
     * @brief 构造选项图标
     * @param resourceMgr 资源管理器
     * @param renderer 渲染器
     * @param path 图标资源路径
     */
    OptionIcon(const ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view path);
    ~OptionIcon() = default;

    /** @brief 更新动画并同步图片可见性 */
    void OnUpdate();
    /**
     * @brief 渲染图标
     * @param params 渲染参数
     */
    void OnRender(const MySDL::RenderParams& params);

    /** @brief 播放图标动画 */
    void PlayAnim();
    /** @brief 停止图标动画 */
    void StopAnim();
};