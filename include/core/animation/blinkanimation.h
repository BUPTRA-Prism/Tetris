/**
 * @file blinkanimation.h
 * @brief 闪烁动画，在显示与隐藏状态间周期性切换
 */
#pragma once

#include "core/animation/animation.h"

/**
 * @brief 闪烁动画，按帧在隐藏/显示间循环切换
 */
class BlinkAnimation : public Animation {
private:
    int m_hideTotalFrame; ///< 隐藏持续帧数
    int m_showTotalFrame; ///< 显示持续帧数
    int m_completedFrame; ///< 当前阶段已累计帧数
    bool m_show;          ///< 当前是否显示

public:
    /**
     * @brief 构造闪烁动画
     * @param hideTotalFrame 隐藏持续帧数
     * @param showTotalFrame 显示持续帧数
     * @param totalLoop 总循环次数（0 为无限）
     */
    BlinkAnimation(int hideTotalFrame, int showTotalFrame, unsigned int totalLoop = 0);
    ~BlinkAnimation() = default;

    /**
     * @brief 判断当前是否处于显示状态
     * @return 显示返回 true
     */
    bool IsShow() const;

private:
    bool IsCycleComplete() override;
    void ResetCycle() override;
};