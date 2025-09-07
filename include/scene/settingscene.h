#pragma once

#include "scene/scene.h"
#include "ui/optionicon.h"
#include "ui/text.h"

/**
 * @brief 设置场景类，用于调整游戏参数
 */
class SettingScene : public Scene {
private:
    SDL_Texture* m_settingFrameTexture;     // 设置场景框架纹理
    SDL_Texture* m_typeFrameTexture;        // 游戏类型框架纹理
    SDL_Texture* m_levelFrameTexture;       // 关卡设置框架纹理
    SDL_Texture* m_heightFrameTexture;      // 高度设置框架纹理
    UniqueTexture m_optionIconTexture;      // 选项图标纹理

    std::unique_ptr<Text> m_gameTypeText;                       // 游戏类型文本
    std::unique_ptr<Text> m_levelText;                          // 关卡标题文本
    std::unique_ptr<Text> m_heightText;                         // 高度标题文本
    std::vector<std::unique_ptr<Text>> m_levelOptionText;       // 关卡选项文本
    std::vector<std::unique_ptr<Text>> m_heightOptionText;      // 高度选项文本
    
    std::unique_ptr<OptionIcon> m_levelOptionIcon;      // 关卡选项图标
    std::unique_ptr<OptionIcon> m_heightOptionIcon;     // 高度选项图标

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调函数
     */
    SettingScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~SettingScene() = default;      // 析构函数

    /**
     * @brief 进入场景
     */
    void onEnter() override;
    /**
     * @brief 退出场景
     */
    void onExit() override;
    /**
     * @brief 每帧更新
     */
    void onUpdate() override;
    /**
     * @brief 渲染设置场景具体内容
     */
    void renderContent() override;
};