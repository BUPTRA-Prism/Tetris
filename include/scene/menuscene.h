/**
 * @file menuscene.h
 * @brief 菜单场景，提供游戏类型与音乐选择
 */
#pragma once

#include "scene/scene.h"
#include "core/graphics/image.h"
#include "entity/optiongroup.h"
#include <functional>
#include <memory>
#include <string_view>

/**
 * @brief 菜单场景，管理游戏类型与音乐两个选项组
 */
class MenuScene : public Scene {
private:
    std::unique_ptr<Image> m_menuImg;                 ///< 菜单背景图片
    std::unique_ptr<OptionGroup> m_gameTypeOptionGroup; ///< 游戏类型选项组
    std::unique_ptr<OptionGroup> m_musicOptionGroup;   ///< 音乐选项组

public:
    /**
     * @brief 构造菜单场景
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调
     */
    MenuScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback);
    ~MenuScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void RenderContent() override;
};