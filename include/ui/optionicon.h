#pragma once

#include "animation/blinkanimation.h"
#include "core/context.h"
#include <functional>

/**
 * @brief 选项图标类
 *
 * 用于菜单场景中显示和控制图标效果（带闪烁动画）
 */
class OptionIcon {
private:
    Context& m_ctx;                             // 全局上下文
    std::function<SDL_Point(int, int)> m_func;  // 位置列表
    SDL_Texture* m_texture;                     // 图标纹理
    std::unique_ptr<BlinkAnimation> m_anim;     // 闪烁动画
    SDL_RendererFlip m_flip;                    // 图标翻转方式

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param texture 图标纹理
     * @param func 位置计算函数
     * @param showFrameTarget 闪烁动画中显示状态的持续帧数
     * @param hideFrameTarget 闪烁动画中隐藏状态的持续帧数
     * @param flip 图标翻转方式
     */
    OptionIcon(Context& ctx, SDL_Texture* texture, std::function<SDL_Point(int, int)> func, int showFrameTarget, int hideFrameTarget, SDL_RendererFlip flip = SDL_FLIP_NONE);
    ~OptionIcon() = default;    // 析构函数

    /**
     * @brief 播放动画
     */
    void playAnim();
    /**
     * @brief 停止播放动画
     */
    void stopAnim();
    /**
     * @brief 每帧更新动画状态
     */
    void onUpdate();
    /**
     * @brief 渲染图标
     * @param row 图标所处行数
     * @param col 图标所处列数
     * @param isFlip 是否水平翻转渲染
     */
    void onRender(int row, int col);
};