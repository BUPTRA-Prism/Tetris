#pragma once

#include "scene/scene.h"
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @brief 场景管理器，管理游戏中所有场景的切换、更新与渲染
 *
 * 使用单例模式，保证全局唯一实例。
 */
class SceneManager {
private:
    Context& m_ctx;                                                     // 全局上下文引用
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;   // 场景映射表
    Scene* m_curScene;                                                  // 当前场景

public:
    /**
     * @brief 获取场景管理器单例
     * @param ctx 全局上下文
     * @return SceneManager& 全局唯一实例
     */
    static SceneManager& getInstance(Context& ctx);

    // 禁用拷贝与移动
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    /**
     * @brief 每帧更新当前场景
     */
    void onUpdate();
    /**
     * @brief 渲染当前场景
     */
    void onRender();

private:
    /**
     * @brief 私有构造函数，初始化场景管理器
     * @param ctx 全局上下文
     */
    SceneManager(Context& ctx);
    ~SceneManager() = default;      // 私有析构函数

    /**
     * @brief 注册场景
     * @param sceneName 场景名称
     * @param scene 场景对象
     */
    void registerScene(const std::string& sceneName, std::unique_ptr<Scene> scene);
    /**
     * @brief 加载指定场景
     * @param sceneName 场景名称
     */
    void loadScene(const std::string& sceneName);
};