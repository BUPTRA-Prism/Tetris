#pragma once

#include "scene/scene.h"
#include "ui/layout.h"
#include "ui/optionicon.h"
#include "ui/text.h"

/**
 * @brief 设置场景类，用于调整游戏参数
 */
class SettingScene : public Scene {
private:
    // 选项枚举
    enum class SettingItem {
        level,  // 关卡选项
        height  // 高度选项
    };

    SettingItem m_curSettingItem;   // 目前正在设置的选项

    SDL_Texture* m_settingFrameTexture;     // 设置场景框架纹理
    SDL_Texture* m_typeFrameTexture;        // 游戏类型框架纹理
    SDL_Texture* m_levelFrameTexture;       // 关卡设置框架纹理
    SDL_Texture* m_heightFrameTexture;      // 高度设置框架纹理
    UniqueTexture m_optionIconTexture;      // 选项图标纹理

    std::unique_ptr<GridLayout> m_levelOptionIconLayout;    // 关卡选项图标布局
    std::unique_ptr<GridLayout> m_heightOptionIconLayout;   // 高度选项图标布局
    std::unique_ptr<GridLayout> m_recordLayout;             // 记录表布局

    std::unique_ptr<Text> m_gameTypeTitle;              // 游戏类型
    std::unique_ptr<Text> m_levelTitle;                 // 关卡标题
    std::vector<std::unique_ptr<Text>> m_levelOption;   // 关卡选项
    std::unique_ptr<Text> m_heightTitle;                // 高度标题
    std::vector<std::unique_ptr<Text>> m_heightOption;  // 高度选项
    std::vector<std::unique_ptr<Text>> m_recordTitle;   // 记录表头
    std::vector<std::unique_ptr<Text>> m_recordOrder;   // 记录名次
    std::vector<std::unique_ptr<Text>> m_recordName;    // 记录姓名
    std::vector<std::unique_ptr<Text>> m_recordScore;   // 记录分数
    std::vector<std::unique_ptr<Text>> m_recordLv;      // 记录关卡数
    
    std::unique_ptr<OptionIcon> m_levelOptionIcon;      // 关卡选项图标
    std::unique_ptr<OptionIcon> m_heightOptionIcon;     // 高度选项图标

    Mix_Chunk* m_optionChunk;   // 选项切换音效
    Mix_Chunk* m_sceneChunk;    // 切换场景音效

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

private:
    /**
     * @brief 初始化游戏类型相关组件
     */
    void initGameType();
    /**
     * @brief 初始化关卡选项相关组件
     */
    void initLevelOption();
    /**
     * @brief 初始化高度选项相关组件
     */
    void initHeightOption();
    /**
     * @brief 初始化记录表相关组件
     */
    void initRecord();
};