#pragma once

#include "scene/scene.h"
#include "ui/optionicon.h"
#include "ui/text.h"

/**
 * @brief 游戏菜单场景
 */
class MenuScene : public Scene {
private:
    SDL_Texture* m_menuFrameTexture;    // 菜单框架纹理
    SDL_Texture* m_optionIconTexture;   // 选项图标纹理

    std::unique_ptr<Text> m_gameTypeText;                       // 游戏模式标题文本
    std::vector<std::unique_ptr<Text>> m_gameTypeOptionText;    // 游戏模式选项文本列表
    std::unique_ptr<Text> m_musicTypeText;                      // 音乐模式标题文本
    std::vector<std::unique_ptr<Text>> m_musicTypeOptionText;   // 音乐模式选项文本列表

    std::array<std::unique_ptr<OptionIcon>, 2> m_gameTypeOptionIcon;    // 游戏模式选项图标
    std::array<std::unique_ptr<OptionIcon>, 2> m_musicTypeOptionIcon;   // 音乐模式选项图标

    Mix_Music* m_music;         // 背景音乐
    Mix_Chunk* m_optionChunk;   // 选项切换音效

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调函数
     */
    MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~MenuScene() = default;     // 析构函数

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
     * @brief 渲染菜单场景具体内容
     */
    void renderContent() override;
};