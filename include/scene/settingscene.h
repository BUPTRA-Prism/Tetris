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
        LevelSetting,  // 等级选项
        HeightSetting  // 高度选项
    };

    SettingItem m_curSettingItem;   // 目前正在设置的选项

    SDL_Texture* m_settingFrameTexture;     // 设置场景框架纹理
    SDL_Texture* m_typeFrameTexture;        // 游戏模式框架纹理
    SDL_Texture* m_levelFrameTexture;       // 等级设置框架纹理
    SDL_Texture* m_heightFrameTexture;      // 高度设置框架纹理
    UniqueTexture m_optionIconTexture;      // 选项图标纹理

    std::unique_ptr<GridLayout> m_levelOptionLayout;        // 等级选项布局
    std::unique_ptr<GridLayout> m_heightOptionLayout;       // 高度选项布局
    std::unique_ptr<VerticalLayout> m_recordOrderLayout;    // 排行榜排名布局
    std::unique_ptr<GridLayout> m_recordLayout;             // 排行榜布局

    std::unique_ptr<Text> m_gameTypeTitle;                  // 游戏模式
    std::unique_ptr<Text> m_levelTitle;                     // 等级标题
    std::vector<std::unique_ptr<Text>> m_levelOptionText;   // 等级选项
    std::unique_ptr<Text> m_heightTitle;                    // 高度标题
    std::vector<std::unique_ptr<Text>> m_heightOptionText;  // 高度选项
    std::vector<std::unique_ptr<Text>> m_recordTitle;       // 排行榜表头
    std::vector<std::unique_ptr<Text>> m_recordOrderText;   // 排行榜名次
    std::vector<std::unique_ptr<Text>> m_recordNameText;    // 排行榜姓名
    std::vector<std::unique_ptr<Text>> m_recordScoreText;   // 排行榜分数
    std::vector<std::unique_ptr<Text>> m_recordLvText;      // 排行榜等级
    
    std::unique_ptr<OptionIcon> m_levelOptionIcon;      // 等级选项图标
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
     * @brief 初始化场景框架
     */
    void setupFrame();
    /**
     * @brief 初始化游戏模式区域
     */
    void setupGameTypeRegion();
    /**
     * @brief 初始化等级选项区域
     */
    void setupLevelOptionRegion();
    /**
     * @brief 初始化高度选项区域
     */
    void setupHeightOptionRegion();
    /**
     * @brief 初始化排行榜区域
     */
    void setupRecordRegion();
    /**
     * @brief 初始化相关音频
     */
    void setupAudio();

    /**
     * @brief 激活场景框架
     */
    void enableFrame();
    /**
     * @brief 激活游戏模式区域
     */
    void enableGameTypeRegion();
    /**
     * @brief 激活等级选项区域
     */
    void enableLevelOptionRegion();
    /**
     * @brief 激活排行榜区域
     */
    void enableRecordRegion();

    /**
     * @brief 禁用选项区域
     */
    void disableOptionRegion();
    /**
     * @brief 禁用相关音频
     */
    void disableAudio();

    /**
     * @brief 更新选项图标动画
     */
    void updateOptionIconAnimation();
    /**
     * @brief 切换场景
     * @return 成功切换场景返回 true ，否则返回 false
     */
    bool updateSceneSwitch();
    /**
     * @brief 切换设置项
     * @return 成功切换设置项返回 true ，否则返回 false
     */
    bool updateSettingItemSwitch();
    /**
     * @brief 切换设置
     * @return 成功切换设置返回 true ，否则返回 false
     */
    bool updateSettingValue();
    /**
     * @brief 更新相关音频
     */
    void updateAudio();
    
    /**
     * @brief 渲染场景框架
     */
    void renderFrame();
    /**
     * @brief 渲染游戏模式区域
     */
    void renderGameTypeRegion();
    /**
     * @brief 渲染等级选项区域
     */
    void renderLevelOptionRegion();
    /**
     * @brief 渲染高度选项区域
     */
    void renderHeightOptionRegion();
    /**
     * @brief 渲染排行榜区域
     */
    void renderRecordRegion();
};