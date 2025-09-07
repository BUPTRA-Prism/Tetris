#pragma once

#include "core/context.h"
#include <functional>

/**
 * @brief 游戏场景基类，所有具体场景都继承自该类
 *
 * 提供背景渲染和场景切换回调功能
 */
class Scene {
protected:
    Context& m_ctx;                                                 // 游戏全局上下文
    std::function<void(const std::string&)> m_loadSceneCallback;    // 场景切换回调函数

    SDL_Color m_bgColor;    // 场景背景颜色

public:
    /**
     * @brief 构造函数
     * @param ctx 上下文引用
     * @param loadSceneCallback 场景切换回调函数
     * @param m_bgColor 场景背景颜色（默认黑色）
     */
    Scene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback, SDL_Color m_bgColor = {0, 0, 0, 255});
    ~Scene() = default;     // 析构函数

    /**
     * @brief 进入场景
     */
    virtual void onEnter() = 0;
    /**
     * @brief 退出场景
     */
    virtual void onExit() = 0;
    /**
     * @brief 每帧更新
     */
    virtual void onUpdate() = 0;
    /**
     * @brief 渲染场景
     */
    void onRender();
    /**
     * @brief 渲染场景背景颜色
     */
    void renderBGColor();
    /**
     * @brief 渲染具体场景内容
     */
    virtual void renderContent() = 0;
};