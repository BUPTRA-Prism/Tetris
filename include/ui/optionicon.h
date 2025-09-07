#pragma once

#include "animation/blinkanimation.h"
#include "core/context.h"

/**
 * @brief 选项图标类
 *
 * 用于菜单场景中显示和控制图标效果（带闪烁动画）
 */
class OptionIcon {
private:
    Context& m_ctx;                             // 全局上下文
    const std::vector<SDL_Point>& m_pos;        // 位置列表
    SDL_Texture* m_texture;                     // 图标纹理
    std::unique_ptr<BlinkAnimation> m_anim;     // 闪烁动画

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param texture 图标纹理
     * @param pos 图标对应的坐标列表
     * @param m_showFrameTarget 闪烁动画中显示状态的持续帧数
     * @param m_hideFrameTarget 闪烁动画中隐藏状态的持续帧数
     */
    OptionIcon(Context& ctx, SDL_Texture* texture, const std::vector<SDL_Point>& pos, int m_showFrameTarget, int m_hideFrameTarget);
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
     * @param posIdx 使用的位置索引（对应 m_pos）
     * @param isFlip 是否水平翻转渲染
     */
    void onRender(int posIdx, bool isFlip = false);
};