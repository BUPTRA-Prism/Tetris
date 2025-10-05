#pragma once

#include "animation/animation.h"

/**
 * @brief 闪烁动画
 * 
 * 通过在显示帧数与隐藏帧数之间循环切换，实现“闪烁”效果
 */
class BlinkAnimation : public Animation {
private:
    int m_showFrameTarget;  // 显示状态持续的帧数
    int m_hideFrameTarget;  // 隐藏状态持续的帧数
    int m_frameCnt;         // 当前状态已持续的帧数
    bool m_show;            // 当前是否处于显示状态

public:
    /**
     * @brief 构造函数
     * @param loopTarget     循环次数（-1 表示无限循环）
     * @param showFrameTarget 显示状态持续的帧数
     * @param hideFrameTarget 隐藏状态持续的帧数
     */
    BlinkAnimation(int loopTarget, int showFrameTarget, int hideFrameTarget);
    ~BlinkAnimation() = default;    // 析构函数

    /**
     * @brief 查询当前是否显示
     * @return 当前为显示状态返回 true ，隐藏状态返回 false  
     */
    bool isShow() const;

private:
    /**
     * @brief 动画更新
     * @return 完成一轮显示->隐藏的循环返回 true ，否则返回 false  
     */
    bool update() override;
    /**
     * @brief 动画复位  
     */
    void reset() override;
};