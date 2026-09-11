/**
 * @file scenemanager.h
 * @brief 场景管理器，负责场景注册、切换与驱动
 */
#pragma once

#include "scene/scene.h"
#include <memory>
#include <string_view>
#include <unordered_map>

class Context;

/**
 * @brief 场景管理器，维护所有场景实例并驱动当前场景
 */
class SceneManager {
private:
    Context& m_ctx;                                                       ///< 全局上下文
    std::unordered_map<std::string_view, std::unique_ptr<Scene>> m_scenes; ///< 场景表
    Scene* m_curScene;                                                    ///< 当前场景

    /**
     * @brief 注册场景
     * @param name 场景名
     * @param scene 场景实例
     */
    void RegisterScene(std::string_view name, std::unique_ptr<Scene> scene);
    /**
     * @brief 加载指定场景
     * @param name 场景名
     */
    void LoadScene(std::string_view name);

public:
    /**
     * @brief 构造并注册所有场景，加载初始场景
     * @param ctx 全局上下文
     */
    explicit SceneManager(Context& ctx);
    ~SceneManager() = default;

    SceneManager(const SceneManager& manager) = delete;
    SceneManager& operator=(const SceneManager& manager) = delete;
    SceneManager(SceneManager&& manager) = delete;
    SceneManager& operator=(SceneManager&& manager) = delete;

    /** @brief 更新当前场景逻辑 */
    void OnUpdate();
    /** @brief 渲染当前场景（含清屏与提交） */
    void OnRender();
};