/**
 * @file scene.h
 * @brief 场景基类，定义场景生命周期接口
 */
#pragma once

#include <functional>
#include <string_view>
#include <SDL2/SDL.h>

class Context;

/**
 * @brief 场景基类，定义进入、退出、更新与渲染的抽象接口
 */
class Scene {
protected:
    Context& m_ctx;                                              ///< 全局上下文
    std::function<void(std::string_view)> m_loadSceneCallback;   ///< 场景切换回调
    SDL_Color m_bgColor;                                         ///< 背景色

public:
    /**
     * @brief 构造场景
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调
     * @param bgColor 背景色
     */
    Scene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback, SDL_Color bgColor = { 0, 0, 0, 255 });
    virtual ~Scene() = default;

    /**
     * @brief 获取背景色
     * @return 背景色
     */
    SDL_Color GetBGColor() const noexcept;

    /** @brief 场景进入时调用 */
    virtual void OnEnter() = 0;
    /** @brief 场景退出时调用 */
    virtual void OnExit() = 0;
    /** @brief 逐帧更新场景逻辑 */
    virtual void OnUpdate() = 0;
    /** @brief 渲染场景内容 */
    virtual void RenderContent() = 0;
};